#pragma once

#include "envoy/common/optional.h"
#include "envoy/common/pure.h"

namespace Network {
namespace Address {

enum class Type { Ip, Pipe };

class Ip {
public:
  virtual ~Ip() {}

  virtual const std::string& addressAsString() const PURE;
  virtual const Optional<uint32_t>& port() const PURE;
};

class Pipe {};

class Instance;
typedef std::shared_ptr<const Instance> InstancePtr;

class Instance {
public:
  virtual ~Instance() {}

  virtual bool operator==(const Instance& rhs) const PURE;
  virtual const std::string& asString() const PURE;
  virtual int bind(int fd) const PURE;
  virtual int connect(int fd) const PURE;
  virtual const Ip* ip() const PURE;
  virtual int socket() const PURE;
  virtual Type type() const PURE;
};

} // Address
} // Network
