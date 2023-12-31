// LoadBalancer.h

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <map>
#include <vector>
#include <queue>
#include <set>

#include "WebServer.h"

class LoadBalancer
{
public:
    LoadBalancer();

    void generateWebServers(std::vector<std::string> &ipAddresses);
    std::vector<std::unique_ptr<WebServer>> getWebServers();
    void addRequestToServer(int serverId, const Request &request);
    void setNumServers(int numServers);
    void printWebServerDetails();
    std::vector<std::string> assignedIPs;
    void addRequest(const Request &request);

private:
    std::vector<std::unique_ptr<WebServer>> webServers;
    std::queue<Request> unassignedRequests;
    int numServers = 0;
    std::mutex loadBalancerMutex;
};

#endif // LOADBALANCER_H
