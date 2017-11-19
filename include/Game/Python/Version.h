//
// Created by Sam on 11/18/2017.
//

#ifndef WHISPERERENGINE_VERSION_H
#define WHISPERERENGINE_VERSION_H


#include <string>

class Version
{
public:
    int major, minor, revision, build;

    bool operator < (const Version& other);
    bool operator == (const Version& other);

    std::string toString();

    ~Version();
    explicit Version(std::string version);
};


#endif //WHISPERERENGINE_VERSION_H
