//
// Created by Sam on 2/25/2018.
//

#include "../../include/Network/HTTPRequest.h"
#include <curl/curl.h>
#include <iostream>
#include <sstream>


std::string HTTPRequest::API_KEY = "86E46A5E8C8A6D7DAEADFF7875D94D2B";
std::string HTTPRequest::APP_ID = "480";

std::string HTTPRequest::makeGETRequest(std::string url)
{
    CURL *curl;
    CURLcode result;
    std::string readBuffer;

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        result = curl_easy_perform(curl);

        if(result != CURLE_OK)
        {
            std::cerr << (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result)) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

std::string HTTPRequest::sendAuthenticationRequest(std::string token)
{
    std::ostringstream URL;
    URL << "https://api.steampowered.com/ISteamUserAuth/AuthenticateUserTicket/v1/?" <<
        "key=" << API_KEY <<
        "&appid=" << APP_ID <<
        "&ticket=" << token;

    return makeGETRequest(URL.str());
}

size_t HTTPRequest::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}