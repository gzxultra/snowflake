#ifndef REDIS_CONN_H
#define REDIS_CONN_H

#include <time.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <iostream>

#include "../../third_party/hiredis/hiredis.h"

using std::string;
using std::cout;


class RedisConn {
public:
    RedisConn(string host, int port);
    void connect();
    void disconnect();
    char* query(string key);

private:
    string host;
    uint16_t port;
    redisContext* redis_ctx_;
};

#endif
