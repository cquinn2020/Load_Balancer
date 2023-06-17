// Request.h

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

class Request
{
public:
    Request() : requestIp(""), destinationIp(""), processingTime(0) {} // add default constructor

    Request(const std::string &requestIp, const std::string &destinationIp, float processingTime);

    std::string getRequestIp() const;
    std::string getDestinationIp() const;
    float getProcessingTime() const;
    void printRequest() const;

private:
    std::string requestIp;
    std::string destinationIp;
    float processingTime;
};

#endif // REQUEST_H
