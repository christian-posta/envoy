#include "listen_socket_impl.h"
#include "utility.h"

#include "envoy/common/exception.h"

#include "common/common/assert.h"
#include "common/network/address_impl.h"

namespace Network {

TcpListenSocket::TcpListenSocket(uint32_t port, bool bind_to_port) : port_(port) {
  // TODO: IPv6 support.
  Address::InstancePtr address(new Address::Ipv4Instance(port));
  fd_ = address->socket();
  RELEASE_ASSERT(fd_ != -1);

  int on = 1;
  int rc = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  RELEASE_ASSERT(rc != -1);

  if (bind_to_port) {
    rc = address->bind(fd_);
    if (rc == -1) {
      close();
      throw EnvoyException(fmt::format("cannot bind on port {}: {}", port, strerror(errno)));
    }
  }
}

UdsListenSocket::UdsListenSocket(const std::string& uds_path) {
  remove(uds_path.c_str());
  Address::InstancePtr address(new Address::UdsInstance(uds_path));
  fd_ = address->socket();
  RELEASE_ASSERT(fd_ != -1);

  int rc = address->bind(fd_);
  if (rc == -1) {
    close();
    throw EnvoyException(
        fmt::format("cannot bind unix domain socket path {}: {}", uds_path, strerror(errno)));
  }
}

} // Network
