// Request.cpp

#include "Request.h"

Request::Request(const std::string &requestIp, const std::string &destinationIp, float processingTime)
    : requestIp(requestIp), destinationIp(destinationIp), processingTime(processingTime) {}

std::string Request::getRequestIp() const
{
    return requestIp;
}

std::string Request::getDestinationIp() const
{
    return destinationIp;
}

int Request::getProcessingTime() const
{
    return processingTime;
}
