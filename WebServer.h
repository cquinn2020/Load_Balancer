// WebServer.h

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <queue>
#include "Request.h"

class WebServer
{
public:
    void addToQueue(const Request &request);
    Request processNextRequest();
    int getQueueSize() const;

    int maxRequestsPerServer = 0;
    std::queue<Request> requestQueue;

private:
};

#endif // WEBSERVER_H
