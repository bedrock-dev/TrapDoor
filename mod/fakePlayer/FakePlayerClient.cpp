//
// Created by xhy on 2021/2/17.
//

#include "FakePlayerClient.h"
#include "TrapdoorMod.h"
#include "entity/Actor.h"
#include "language/I18nManager.h"
#include "tools/Message.h"
#include "tools/json.hpp"

namespace mod {

void FakePlayerClient::registerFakePlayerCommand(CommandManager &manager) {
  using namespace trapdoor;
  manager.registerCmd("fakeplayer", "command.fakeplayer.desc")
      ->then(ARG("conn", "command.fakeplayer.conn.desc", STR,
                 { this->connect(player, holder->getString()); }))
      ->then(ARG("c", "command.fakeplayer.c.desc", NONE,
                 { this->connect(player, ""); }))
      ->then(ARG("list", "command.fakeplayer.list.desc", NONE,
                 {
                   this->sendMessage(player, FakePlayerClient::buildMessage(
                                                 MessageType::PLAYER_LIST));
                 }))
      ->then(ARG("add", "command.fakeplayer.add.desc", STR,
                 {
                   this->sendMessage(player, FakePlayerClient::buildMessage(
                                                 MessageType::ADD_PLAYER,
                                                 holder->getString()));
                 }))
      ->then(ARG("rm", "command.fakeplayer.remove.desc", STR,
                 {
                   this->sendMessage(player, FakePlayerClient::buildMessage(
                                                 MessageType::REMOVE_PLAYER,
                                                 holder->getString()));
                 }))
      ->then(ARG("tp", "command.fakeplayer.tp.desc", STR,
                 { this->tpFakePlayer(player, holder->getString()); }));
}

//发送消息
bool FakePlayerClient::sendMessage(trapdoor::Actor *player,
                                   const std::string &msg) {
  //如果可以发送消息就发送，不能发送就gg
  if (!this->checkConn()) {
    trapdoor::error(player, trapdoor::LANG("fp.error.noConnect"));
    return false;
  }

  if (this->clientStatus != ClientStatus::READY) {
    trapdoor::error(player, trapdoor::LANG("fp.error.status"));
  }
  this->webSocket->send(msg);
  this->source = player;
  this->clientStatus = ClientStatus::WAITING_MESSAGE;
  return true;
}

//在单独的线程中来进行消息的收取
void FakePlayerClient::run() {
  this->pool->enqueue([&] {
    //如果socket 是处于开启状态就一直监听作为事件循环
    while (this->webSocket && this->webSocket->getReadyState() !=
                                  easywsclient::WebSocket::CLOSED) {
      this->webSocket->poll(50);
      this->webSocket->dispatch([&](const std::string &msg) {
        if (this->clientStatus == ClientStatus::WAITING_MESSAGE) {
          //改变状态来通知消息到了
          this->clientStatus = ClientStatus::NEED_CONSUME;
          this->message.set(msg);
        } else {
          //这里可能是有超时的消息，就不处理了，防止消息出现错乱
          //也就是丢弃超时的消息
        }
      });
    }
    this->disconnectCallBack();
  });
}

bool FakePlayerClient::consume() {
  bool status = true;
  auto msg = FakePlayerClient::parseResponse(this->message.get(), status);
  //处理服务端的回复消息
  if (source) {
    if (status) {
      trapdoor::info(this->source, "%s", msg.c_str());
    } else {
      trapdoor::error(this->source, "%s", msg.c_str());
    }
  } else {
    trapdoor::broadcastMsg(trapdoor::LANG("fp.error.noSource"), msg.c_str());
  }
  return true;
}

void FakePlayerClient::connect(trapdoor::Actor *player,
                               const std::string &url) {

  if (this->webSocket &&
      this->webSocket->getReadyState() == easywsclient::WebSocket::OPEN) {
    trapdoor::warning(player, trapdoor::LANG("fp.error.exist"));
    return;
  }
  if (this->webSocket) {
    this->webSocket->close();
  }
  delete this->webSocket;

  auto wsUrl = url;
  if (wsUrl.empty()) {
    auto mod = trapdoor::bdsMod->asInstance<TrapdoorMod>();
    wsUrl = mod->getConfigManager().getServerConfig().wsUrl;
  }

  this->webSocket = easywsclient::WebSocket::from_url(wsUrl);

  if (this->webSocket) {
    this->clientStatus = ClientStatus::READY;
    trapdoor::info(player, trapdoor::LANG("fp.info.connect"), wsUrl.c_str());
    this->run();
  } else {
    trapdoor::info(player, trapdoor::LANG("fp.error.connect"), wsUrl.c_str());
  }
}

//更新状态，查询和消费消息队列
void FakePlayerClient::tick() {
  //如果是等待消息的状态就增加计时器如果五秒内收不到消息就说明消息发送失败
  if (this->clientStatus == ClientStatus::WAITING_MESSAGE) {
    this->timer++;
    //超过100gt没有回复就说明连接炸了
    if (this->timer == 100) {
      this->message.set(trapdoor::LANG("fp.tick.timeout"));
      this->clientStatus = ClientStatus::READY;
      this->timer = 0;
      return;
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

FakePlayerClient::~FakePlayerClient() { disconnect(); }

//断开连接
void FakePlayerClient::disconnect() {
  if (webSocket)
    webSocket->close();
  delete webSocket;
  this->disconnectCallBack();
}

void FakePlayerClient::disconnectCallBack() {
  trapdoor::broadcastMsg(trapdoor::LANG("fp.info.disconnectCallBack"));
  this->clientStatus = ClientStatus::NOT_OPEN;
}

std::string FakePlayerClient::buildMessage(FakePlayerClient::MessageType type,
                                           const std::string &param) {
  switch (type) {
  case MessageType::PLAYER_LIST:
    return R"({
                   "type": "list"
                        })";
  case MessageType::ADD_PLAYER:
    return trapdoor::format(R"(
                {
                    "type": "add",
                    "data": {
                    "name": "%s",
                    "skin": "steve"
                        }
                    }
                )",
                            param.c_str());
  case MessageType::REMOVE_PLAYER:
    return trapdoor::format(R"(
                {
                    "type": "remove",
                    "data": {
                            "name": "%s"
                    }
                }
                )",
                            param.c_str());
  }
  return "{}";
}

std::string FakePlayerClient::parseResponse(const std::string &response,
                                            bool &status) {
  using json = nlohmann::json;
  try {
    json jsonMsg = json::parse(response);
    auto respType = jsonMsg["type"].get<std::string>();
    auto respData = jsonMsg["data"];
    if (respType == "list") {
      status = true;
      std::string strBuilder =
          trapdoor::LANG("fp.info.list"); //下面是所有的假人玩家
      this->fakePlayerList.clear();
      for (auto &i : respData["list"]) {
        strBuilder += "\n";
        strBuilder += i.get<std::string>();
        this->fakePlayerList.insert(i.get<std::string>());
      }
      return strBuilder;
    } else if (respType == "add" || respType == "remove") {
      const std::string type =
          respType == "add" ? trapdoor::LANG("fp.added")
                            : trapdoor::LANG("fp.remove"); // 添加" : "移除
      auto name = respData["name"].get<std::string>();
      auto success = respData["success"].get<bool>();
      if (success) {
        status = true;
        return trapdoor::format(trapdoor::LANG("fp.connect.success"),
                                type.c_str(),
                                name.c_str()); // 成功%s假人[%s]
      } else {
        status = false;
        auto reason = respData["reason"].get<std::string>();
        return trapdoor::format(trapdoor::LANG("fp.connect.fail"), type.c_str(),
                                name.c_str(),
                                reason.c_str()); //无法%s假人[%s],原因: %s
      }
    } else {
      status = false;
      return "unknown message";
    }
  } catch (std::exception &e) {
    status = false;
    return trapdoor::format("message error: %s", e.what());
  }
}

void FakePlayerClient::tpFakePlayer(trapdoor::Actor *player,
                                    const std::string &playerName) {

  if (this->fakePlayerList.count(playerName)) {
    const std::string tpCmd =
        "tp \"" + playerName + "\"  \"" + player->getNameTag() + "\"";
    CommandManager::runVanillaCommand(tpCmd);
    trapdoor::info(this->source, trapdoor::LANG("fp.tp.success"),
                   player->getNameTag().c_str()); //假人已被tp到[%s]所在位置
  } else {
    trapdoor::info(
        this->source,
        trapdoor::LANG("fp.tp.fail")); //找不到假人，请尝试执行fakeplayer
                                       // list指令后再试
  }
}
bool FakePlayerClient::checkConn() {
  return this->webSocket &&
         this->webSocket->getReadyState() == easywsclient::WebSocket::OPEN;
}
} // namespace mod
