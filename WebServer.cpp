// WebServer.cpp

#include "WebServer.h"

WebServer::WebServer(std::string ipAddress)
{
    this->ipAddress = ipAddress;
    this->isProcessingRequest = false;
    this->request = Request("", "", 0);
}

std::string WebServer::getIpAddress() const
{
    return ipAddress;
}

bool WebServer::getIsProcessing() const
{
    return isProcessingRequest;
}

void WebServer::processRequests(std::atomic<bool> &simulationRunning)
{
    while (simulationRunning)
    {
        std::unique_lock<std::mutex> lock(this->webServerMutex);
        if (!isProcessingRequest && hasRequest)
        {
            isProcessingRequest = true;

            // Get the processing time of the next request
            float processingTime = request.getProcessingTime();
            lock.unlock();

            // "Process" the request by sleeping for its duration
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(processingTime * 1000)));

            // Output a message that the request has been processed
            std::cout << "Request from " << request.getRequestIp() << " processed by Web Server with ip address: " << ipAddress << "\n";

            // Lock again to safely set isProcessingRequest
            lock.lock();
            isProcessingRequest = false;
            hasRequest = false;
        }
        else
        {
            // If the queue is empty, yield this thread's time slice
            std::this_thread::yield();
        }
    }
}

bool WebServer::getHasRequest() const
{
    return hasRequest;
}