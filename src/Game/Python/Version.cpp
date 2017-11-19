//
// Created by Sam on 11/18/2017.
//

#include "../../../include/Game/Python/Version.h"

#include <stdexcept>

bool Version::operator < (const Version &other)
{
    if (major < other.major)
        return true;
    if (minor < other.minor)
        return true;
    if (revision < other.revision)
        return true;
    if (build < other.build)
        return true;
    return false;
}

bool Version::operator == (const Version &other)
{
    return major == other.major
           && minor == other.minor
           && revision == other.revision
           && build == other.build;
}

Version::Version(std::string version)
        : major(0), minor(0), revision(0), build(0)
{
    if(0 > version.length() > 4)
    {
        throw std::runtime_error("Invalid python version - " + version);
    }

    std::sscanf(version.c_str(), "%d.%d.%d.%d", &major, &minor, &revision, &build); // NOLINT
}

Version::~Version()
= default;
