#include <iostream>

#include "client.h"

// Constructor with "initialization list"
GreeterClient::GreeterClient(std::shared_ptr<Channel> channel)
  : stub_(Greeter::NewStub(channel)) {}

std::string GreeterClient::SayHello(const std::string& user) {
  // Data we are sending to the server.
  HelloRequest request;
  request.set_name(user);

  // Container for the data we expect from the server.
  HelloReply reply;

  // Context for the client. It could be used to convey extra information to
  // the server and/or tweak certain RPC behaviors.
  ClientContext context;

  // The actual RPC.
  Status status = stub_->SayHello(&context, request, &reply);

  // Act upon its status.
  if (status.ok()) {
    return reply.message();
  } else {
    return "RPC failed";
  }
}

