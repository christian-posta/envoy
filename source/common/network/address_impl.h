#pragma once

#include "envoy/network/address.h"

namespace Network {
namespace Address {

/**
 *
 */
class Ipv4Instance : public Instance {
public:
  Ipv4Instance(const sockaddr_in* address);
  Ipv4Instance(const std::string& address);
  Ipv4Instance(const std::string& address, uint32_t port);
  Ipv4Instance(uint32_t port);

  // Network::Address::Instance
  bool operator==(const Instance& rhs) const override;
  const std::string& asString() const override;
  int bind(int fd) const override;
  int connect(int fd) const override;
  const Ip* ip() const override;
  int socket() const override;
  Type type() const override;
};

class UdsInstance : public Instance {
public:
  UdsInstance(const std::string& uds_path);

  // Network::Address::Instance
  bool operator==(const Instance& rhs) const override;
  const std::string& asString() const override;
  int bind(int fd) const override;
  int connect(int fd) const override;
  const Ip* ip() const override;
  int socket() const override;
  Type type() const override;
};

} // Address
} // Network
