#include "LoadBalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer() {}

void LoadBalancer::generateWebServers(std::vector<std::string> &ipAddresses, int maxRequestsPerServer)
{
    this->assignedIPs = ipAddresses;
    this->maxRequestsPerServer = maxRequestsPerServer;

    for (int i = 0; i < ipAddresses.size(); i++)
    {
        WebServer webServer;
        webServer.maxRequestsPerServer = maxRequestsPerServer;
        webServers[i] = webServer;
    }
}

WebServer &LoadBalancer::getWebServer(int serverId)
{
    // Add implementation here.
}

void LoadBalancer::addRequestToServer(int serverId, const Request &request)
{
    // Add implementation here.
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
        std::cout << "IP Address: " << assignedIPs[i] << "\n";
        std::cout << "Max requests: " << maxRequestsPerServer << "\n";
        std::cout << "Current queue size: " << webServers[i].getQueueSize() << "\n";
        std::cout << "\n";
    }
}

void LoadBalancer::addRequest(const Request &request)
{
    this->unassignedRequests.push(request);
}