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

private:
    std::queue<Request> requestQueue;
};

#endif // WEBSERVER_H
