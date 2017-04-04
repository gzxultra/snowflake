#include <time.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <iostream>
#include "redis_conn.h"
#include "../../third_party/hiredis/hiredis.h"

using std::string;
using std::cout;


RedisConn::RedisConn(string host, int port)
{
    this->host = host;
    this->port = port;
}

void RedisConn::connect()
{
    timeval timeout = {3, 50000};
    redis_ctx_ = redisConnectWithTimeout(host.c_str(), port, timeout);
    if (redis_ctx_ == NULL || redis_ctx_->err)
    {
        if (redis_ctx_ != NULL)
        {
            printf("connection error %s\n", redis_ctx_->errstr);
            redisFree(redis_ctx_);
        }
        else
        {
            printf("connect exception, redis context initiation error.\n");
        }
        redis_ctx_ = NULL;
    }
    else
    {
        printf("redis server connected!\n");
    }
}

void RedisConn::disconnect()
{}

char* RedisConn::query(string key)
{
    redisReply* reply = (redisReply*)redisCommand(redis_ctx_, "GET %s", key.c_str());
    return reply->str;
}

