//
// Created by xhy on 2021/2/17.
//

#ifndef MOD_FAKEPLAYERCLIENT_H
#define MOD_FAKEPLAYERCLIENT_H
#ifdef _WIN32
#pragma comment(lib, "ws2_32")

#include <WinSock2.h>

#endif

#include "CommandManager.h"
#include "ThreadPool.h"
#include "easywsclient.hpp"
#include <atomic>
#include <cassert>
#include <cstdio>
#include <mutex>
#include <queue>
#include <set>
#include <string>

namespace mod {

template <typename T> class SimpleThreadSafeVal {
private:
  T val;
  std::mutex m;

public:
  void set(const T &v) {
    std::lock_guard<std::mutex> l(m);
    this->val = v;
  }

  T get() {
    std::lock_guard<std::mutex> l(m);
    return val;
  }
};

//和falePlayer进行通信的客户端
class FakePlayerClient {
  enum class ClientStatus { NOT_OPEN, READY, WAITING_MESSAGE, NEED_CONSUME };
  enum class MessageType { PLAYER_LIST, ADD_PLAYER, REMOVE_PLAYER };

private:
  static std::string buildMessage(MessageType type,
                                  const std::string &param = "");

  std::string parseResponse(const std::string &response, bool &status);

  easywsclient::WebSocket *webSocket = nullptr;
  ThreadPool *pool = nullptr;
  std::atomic<ClientStatus> clientStatus{ClientStatus::NOT_OPEN};
  SimpleThreadSafeVal<std::string> message;
  size_t timer = 0;
  trapdoor::Actor *source = nullptr;
  std::set<std::string> fakePlayerList;

  //发送消息
  bool sendMessage(trapdoor::Actor *player, const std::string &msg);

  //后台运行
  void run();

  bool consume();

  void disconnectCallBack();

  inline void setSource(trapdoor::Actor *player) { this->source = player; }

public:
  void registerFakePlayerCommand(trapdoor::CommandManager &manager);

  explicit FakePlayerClient(ThreadPool *threadPool) : pool(threadPool) {}

  void connect(trapdoor::Actor *player, const std::string &url);

  void disconnect();

  void tick();

  void tpFakePlayer(trapdoor::Actor *player, const std::string &playerName);

  bool checkConn();

  ~FakePlayerClient();
};

} // namespace mod
#endif // MOD_FAKEPLAYERCLIENT_H
