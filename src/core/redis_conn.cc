#include <time.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <../../hiredis/hiredis.h>

using std::string;
using std::cout;


class RedisConn {
public:
    RedisConn(string host, int port)
    {
        this->host = host;
        this->port = port;
    }

    void connect()
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

    void disconnect()
    {}

    char* query(string key)
    {
        redisReply* reply = (redisReply*)redisCommand(redis_ctx_, "GET %s", key.c_str());
        return reply->str;
    }

private:
    string host;
    uint16_t port;
    redisContext* redis_ctx_;
};

int main()
{
    RedisConn conn = RedisConn("mango", 6379);
    conn.connect();
    cout << conn.query("slot:splash_ad:deliveries");
    return 0;
}

