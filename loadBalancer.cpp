// LoadBalancer.cpp

#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(int numServers)
{
    generateWebServers(numServers);
}

void LoadBalancer::generateWebServers(int numServers)
{
    // Add implementation here.
}

WebServer &LoadBalancer::getWebServer(int serverId)
{
    // Add implementation here.
}

void LoadBalancer::addRequestToServer(int serverId, const Request &request)
{
    // Add implementation here.
}
