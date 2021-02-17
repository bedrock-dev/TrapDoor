//
// Created by xhy on 2021/2/17.
//

#include "FakePlayerClient.h"
#include "entity/Actor.h"
#include "tools/Message.h"
#include "language/I18nManager.h"

namespace mod {


    void FakePlayerClient::registerFakePlayerCommand(CommandManager &manager) {
        using namespace trapdoor;
        manager.registerCmd("fakeplayer", "command.fakeplayer.desc")
                ->then(ARG("conn", "command.fakeplayer.conn.desc", STR, {
                    this->connect(player, holder->getString());
                }))
                ->then(ARG("add", "command.fakeplayer.add.desc", STR, {
                    this->sendMessage(holder->getString());
                }))
                ->then(ARG("rm", "command.fakeplayer.remove.desc", STR, {
                    this->sendMessage(holder->getString());
                }));
    }


    //发送消息
    bool FakePlayerClient::sendMessage(trapdoor::Actor *player, const std::string &msg) {
        //如果可以发送消息就发送，不能发送就gg
        if (!webSocket || webSocket->getReadyState() == easywsclient::WebSocket::CLOSED) {
            trapdoor::error(player, trapdoor::LANG("fp.error.noConnect"));
            return false;
        }
        if (this->clientStatus != ClientStatus::READY) {
            trapdoor::error(player, trapdoor::LANG("fp.error.status"));
        }
        printf("send %s", msg.c_str());
        this->webSocket->send(msg);
        this->clientStatus = ClientStatus::WAITING_MESSAGE;
        return true;
    }

    //在单独的线程中来进行消息的收取
    void FakePlayerClient::run() {
        this->pool->enqueue([&] {
            //如果socket 是处于开启状态就一直监听作为事件循环
            while (this->webSocket && this->webSocket->getReadyState() != easywsclient::WebSocket::CLOSED) {
                this->webSocket->poll();
                this->webSocket->dispatch([&](const std::string &msg) {
                    printf("receive from ws: %s\n", msg.c_str());
                    if (this->clientStatus == ClientStatus::WAITING_MESSAGE) {
                        //改变状态来通知消息到了
                        this->clientStatus = ClientStatus::NEED_CONSUME;
                        this->message = msg;
                    }

                    //这里可能是有超时的消息，就不处理了，防止消息出现错乱
                    //也就是丢弃超时的消息
                });
            }
            this->disconnectCallBack();
        });
    }


    bool FakePlayerClient::consume() {
        //处理服务端的回复消息
        trapdoor::broadcastMsg("receive msg: %s", this->message.c_str());
        return true;
    }

    void FakePlayerClient::connect(trapdoor::Actor *player, const std::string &url) {
        this->webSocket = easywsclient::WebSocket::from_url(url);
        if (this->webSocket) {
            this->clientStatus = ClientStatus::READY;
            trapdoor::info(player, "has connected: %s", url.c_str());
            this->run();
        } else {
            trapdoor::info(player, "cannot connect: %s,please check the url", url.c_str());
        }
    }

    //更新状态，查询消息队列
    void FakePlayerClient::tick() {
        //如果是等待消息的状态就增加计时器如果五秒内收不到消息就说明消息发送失败
        if (this->clientStatus == ClientStatus::WAITING_MESSAGE) {
            this->timer++;
            //超过100gt没有回复就说明连接炸了
            if (this->timer == 100) {
                this->timer = 0;
                this->clientStatus = ClientStatus::READY;
            }
        }

        //如果有消息需要消费就消费消息
        if (this->clientStatus == ClientStatus::NEED_CONSUME) {
            this->consume();
            //重置状态和计时器
            this->clientStatus = ClientStatus::READY;
            this->timer = 0;
        }
    }

    FakePlayerClient::~FakePlayerClient() {
        disconnect();
    }

    //断开连接
    void FakePlayerClient::disconnect() {
        if (webSocket)webSocket->close();
        delete webSocket;
        this->disconnectCallBack();
    }

    void FakePlayerClient::disconnectCallBack() {
        trapdoor::broadcastMsg("client or server has closed the connection");
        this->clientStatus = ClientStatus::NOT_OPEN;
    }
}

