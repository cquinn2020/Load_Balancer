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

std::string generateRandomIPAdress();
bool GetUserInput(int &numServers, int &maxRequestsPerServer, int &runTimeInCycles);

int main()
{
    srand(time(NULL));

    int numServers;
    int maxRequestsPerServer;
    int runTimeInCycles;

    if (!GetUserInput(numServers, maxRequestsPerServer, runTimeInCycles))
    {
        return 1;
    }

    std::cout << "Number of servers: " << numServers << "\n";
    std::cout << "Maximum requests per server: " << maxRequestsPerServer << "\n";
    std::cout << "Runtime in cycles: " << runTimeInCycles << "\n";
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