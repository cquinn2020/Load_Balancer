#include "LoadBalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer() {}

void LoadBalancer::generateWebServers(std::vector<std::string> &ipAddresses)
{
    this->assignedIPs = ipAddresses;

    for (int i = 0; i < numServers; i++)
    {
        webServers.push_back(std::make_unique<WebServer>(ipAddresses[i]));
    }
}

std::vector<std::unique_ptr<WebServer>> LoadBalancer::getWebServers()
{
    return webServers;
}

void LoadBalancer::addRequestToServer(int serverId, const Request &request)
{
    // obtauin a lock and add the request to the server's queue
    std::lock_guard<std::mutex> lock(loadBalancerMutex);
}

void LoadBalancer::setNumServers(int numServers)
{
    this->numServers = numServers;
}

void LoadBalancer::printWebServerDetails()
{
    for (int i = 0; i < numServers; i++)
    {
        std::cout << "Server " << i << ":\n";
        std::cout << "IP: " << webServers[i]->getIpAddress() << "\n";
        std::cout << "Is processing request: " << webServers[i]->getIsProcessing() << "\n";

        std::cout << "\n";
    }
}

void LoadBalancer::addRequest(const Request &request)
{
    std::lock_guard<std::mutex> lock(loadBalancerMutex);
    this->unassignedRequests.push(request);
}