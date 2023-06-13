// WebServer.cpp

#include "WebServer.h"

void WebServer::addToQueue(const Request &request)
{
    // Add implementation here.
}

Request WebServer::processNextRequest()
{
    // Add implementation here.
}

int WebServer::getQueueSize() const
{
    return requestQueue.size();
}