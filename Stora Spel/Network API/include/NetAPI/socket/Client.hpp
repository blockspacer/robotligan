#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <NetAPI/common.hpp>
#include <NetAPI/packet.hpp>
#include <NetAPI/socket/tcpclient.hpp>
namespace NetAPI {
namespace Socket {
class EXPORT Client {
 public:
  Client() { client_ = new NetAPI::Socket::TcpClient; }
  ~Client() { delete client_; }
  int Connect(const char* addr, short port);
  int Send(NetAPI::Common::Packet& p);
  NetAPI::Common::Packet Receive(const short timeout = 50);
  unsigned short& GetID() { return ID_; }
  void Disconnect() { client_->Disconnect(); }
  bool IsConnected() { return client_->IsConnected(); }
  TcpClient* GetRaw() { return client_; }

 private:
  ClientData clientdata_; // But why?
  unsigned short ID_ = 0;
  NetAPI::Socket::TcpClient* client_ = nullptr;
};
}  // namespace Socket
}  // namespace NetAPI
#endif  // !CLIENT_HPP_