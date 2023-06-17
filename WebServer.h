// WebServer.h

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <queue>
#include <mutex>
#include <thread>

#include "Request.h"

class WebServer
{
public:
    // write a default constructor that initializes ipAddress to an empty string

    WebServer(std::string ipAddress);
    void processRequests(std::atomic<bool> &simulationRunning);
    Request getRequest();
    void setRequest(Request &request);
    std::string getIpAddress() const;
    bool getIsProcessing() const;
    bool getHasRequest() const;

private:
    std::mutex webServerMutex;
    Request request;
    bool isProcessingRequest = false;
    std::string ipAddress;
    bool hasRequest = false;
};

#endif // WEBSERVER_H
