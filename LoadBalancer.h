// LoadBalancer.h

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <map>
#include "WebServer.h"

class LoadBalancer
{
public:
    LoadBalancer(int numServers);

    void generateWebServers(int numServers);
    WebServer &getWebServer(int serverId);
    void addRequestToServer(int serverId, const Request &request);

private:
    std::map<int, WebServer> webServers;
};

#endif // LOADBALANCER_H
