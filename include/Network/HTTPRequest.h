//
// Created by Sam on 2/25/2018.
//

#ifndef WHISPERERENGINE_HTTPREQUEST_H
#define WHISPERERENGINE_HTTPREQUEST_H


#include <string>

class HTTPRequest
{
public:
    static std::string makeGETRequest(std::string url);
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
};


#endif //WHISPERERENGINE_HTTPREQUEST_H
