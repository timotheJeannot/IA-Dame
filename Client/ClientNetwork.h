//
// Created by ubuntu on 01/12/2020.
//

#ifndef TEST_GF_CLIENTNETWORK_H
#define TEST_GF_CLIENTNETWORK_H

#include <atomic>
#include <mutex>
#include <string>

#include <gf/Packet.h>
#include <gf/Queue.h>
#include <gf/TcpSocket.h>


class ClientNetwork {
  public:
    ClientNetwork();

    bool isConnecting();
    bool isConnected();
    void connect(const std::string& hostname, const std::string& port);
    //void disconnect();

    template<typename T>
    void send(const T& data) {
      gf::Packet packet;
      packet.is(data);
      m_socket.sendPacket(packet);
    }

  public:
    gf::Queue<gf::Packet> queue;

  private:
    void run(std::string hostname, std::string port);

  private:
    gf::TcpSocket m_socket;
    std::mutex m_mutex;
    std::atomic_bool m_connecting;
  };





#endif //TEST_GF_CLIENTNETWORK_H
