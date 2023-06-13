// Request.h

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request
{
public:
    Request(const std::string &requestIp, const std::string &destinationIp, float processingTime);

    std::string getRequestIp() const;
    std::string getDestinationIp() const;
    int getProcessingTime() const;

private:
    std::string requestIp;
    std::string destinationIp;
    float processingTime;
};

#endif // REQUEST_H
