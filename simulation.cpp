#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <limits>
#include <cassert>
#include <random>
#include <map>
#include <cstdlib>
#include <ctime>

#include "LoadBalancer.h"
#include "Request.h"
#include "WebServer.h"

float TIME_PER_CYCLE = 0.024f;
LoadBalancer loadBalancer;

std::string generateRandomIPAdress();
bool GetUserInput(int &numServers, int &maxRequestsPerServer, int &runTimeInCycles);
float generateProcessingTime(int totalClockCycles, float timePerCycle);
std::vector<std::string> generateIPAddresses(int numServers);
void generateRequests(int numServers, LoadBalancer &loadBalancer, int numClockCycles);

int main()
{
    srand(time(NULL));

    int numServers;
    int maxRequestsPerServer;
    int numClockCycles;

    if (!GetUserInput(numServers, maxRequestsPerServer, numClockCycles))
    {
        return 1;
    }

    std::cout << "Number of servers: " << numServers << "\n";
    std::cout << "Maximum requests per server: " << maxRequestsPerServer << "\n";
    std::cout << "Runtime in cycles: " << numClockCycles << "\n";

    std::vector<std::string> webServerIPs = generateIPAddresses(numServers);

    loadBalancer.setNumServers(numServers);
    loadBalancer.generateWebServers(webServerIPs, maxRequestsPerServer);

    std::cout << "Web server details:\n";
    loadBalancer.printWebServerDetails();
    std::cout << "Web server details end.\n\n"
              << std::endl;

    // int totalTime = numClockCycles * TIME_PER_CYCLE;
    // int numRequest = numServers * 100;

    std::cout << "Generating requests...\n";
    generateRequests(numServers, loadBalancer, numClockCycles);
    std::cout << "Requests generated.\n\n";
}

std::string generateRandomIPAdress()
{
    std::string ip = "";
    for (int i = 0; i < 4; i++)
    {
        ip += std::to_string(rand() % 255);
        if (i != 3)
        {
            ip += ".";
        }
    }
    return ip;
}

bool GetUserInput(int &numServers, int &maxRequestsPerServer, int &runTimeInCycles)
{
    std::cout << "Enter the number of servers: ";
    std::cin >> numServers;
    if (std::cin.fail() || numServers <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Number of servers must be a positive integer.\n";
        return false;
    }

    std::cout << "Enter the maximum requests per server: ";
    std::cin >> maxRequestsPerServer;
    if (std::cin.fail() || maxRequestsPerServer <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Maximum requests per server must be a positive integer.\n";
        return false;
    }

    std::cout << "Enter the runtime in cycles: ";
    std::cin >> runTimeInCycles;
    if (std::cin.fail() || runTimeInCycles <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Runtime in cycles must be a positive integer.\n";
        return false;
    }

    return true;
}

float generateProcessingTime(int totalClockCycles, float timePerCycle)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(totalClockCycles * 0.00005, totalClockCycles * 0.03);
    return distr(gen) * timePerCycle;
}

std::vector<std::string> generateIPAddresses(int numServers)
{
    std::vector<std::string> ipAddresses;
    for (int i = 0; i < numServers; i++)
    {
        ipAddresses.push_back(generateRandomIPAdress());
    }
    return ipAddresses;
}

void generateRequests(int numServers, LoadBalancer &loadBalancer, int numClockCycles)
{
    int totalRequests = numServers * 100;
    for (int i = 0; i < totalRequests; i++)
    {
        std::string ipAddress = generateRandomIPAdress();
        std::string webServerIP = loadBalancer.assignedIPs[i % numServers];
        float processingTime = generateProcessingTime(numClockCycles, TIME_PER_CYCLE);
        Request request(ipAddress, webServerIP, processingTime);
        request.printRequest();
        loadBalancer.addRequest(request);
    }
}