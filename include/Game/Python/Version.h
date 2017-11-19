//
// Created by Sam on 11/18/2017.
//

#ifndef WHISPERERENGINE_VERSION_H
#define WHISPERERENGINE_VERSION_H


#include <string>

class Version
{
public:
    bool operator < (const Version& other);

    bool operator == (const Version& other);
    std::string toString();

    explicit Version(std::string version);
    ~Version();

private:
    int m_major, m_minor, m_revision, m_build;
};


#endif //WHISPERERENGINE_VERSION_H
