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
#include <mutex>
#include <thread>

#include "LoadBalancer.h"
#include "Request.h"
#include "WebServer.h"

// Global variables
float TIME_PER_CYCLE = 0.024f;
LoadBalancer loadBalancer;
std::mutex loadBalancerMutex;
std::atomic<bool> simulationRunning(true);
std::atomic<bool> simulationFinished(false);

std::string generateRandomIPAdress();
bool GetUserInput(int &numServers, int &runTimeInCycles);
float generateProcessingTime(int totalClockCycles, float timePerCycle);
std::vector<std::string> generateIPAddresses(int numServers);
void generateRequest(LoadBalancer &loadBalancer, int numClockCycles);
void generateAndSendRequests(LoadBalancer &loadBalancer, int numClockCycles, int numServers, const std::atomic<bool> &simulationRunning);

int main()
{
    srand(time(NULL));

    int numServers;
    int numClockCycles;

    if (!GetUserInput(numServers, numClockCycles))
    {
        return 1;
    }

    std::cout << "Number of servers: " << numServers << "\n";
    std::cout << "Runtime in cycles: " << numClockCycles << "\n";

    std::vector<std::string> webServerIPs = generateIPAddresses(numServers);

    // create the load balancer for the simulation
    loadBalancer.setNumServers(numServers);
    loadBalancer.generateWebServers(webServerIPs);

    std::cout << "Web server details:\n";
    loadBalancer.printWebServerDetails();
    std::cout << "Web server details end.\n\n"
              << std::endl;

    std::cout << "Generating requests...\n";
    int i = 0;
    while (i < numServers * 100)
    {
        generateRequest(loadBalancer, numClockCycles);
    }
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

bool GetUserInput(int &numServers, int &runTimeInCycles)
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

    std::cout << "Enter the runtime in clock cycles: ";
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

void generateRequest(LoadBalancer &loadBalancer, int numClockCycles)
{

    std::string ipAddress = generateRandomIPAdress();
    float processingTime = generateProcessingTime(numClockCycles, TIME_PER_CYCLE);
    Request request(ipAddress, "", processingTime);
    request.printRequest();
    loadBalancer.addRequest(request);
}

void generateAndSendRequests(LoadBalancer &loadBalancer, int numClockCycles, int numServers, const std::atomic<bool> &simulationRunning)
{
    while (simulationRunning)
    {
        int pause = rand() % 100000;

        std::this_thread::sleep_for(std::chrono::milliseconds(pause));

        std::string ipAddress = generateRandomIPAdress();
        std::string webServerIP = loadBalancer.assignedIPs[rand() % numServers];
        float processingTime = generateProcessingTime(numClockCycles, TIME_PER_CYCLE);

        Request request(ipAddress, webServerIP, processingTime);

        {
            std::lock_guard<std::mutex> lock(loadBalancerMutex);
            loadBalancer.addRequest(request);
        }
    }
}
