//
// Created by Sam on 11/18/2017.
//

#include "../../../include/Game/Python/Version.h"

#include <stdexcept>

bool Version::operator < (const Version &other)
{
    if (_major < other._major)
        return true;
    if (_minor < other._minor)
        return true;
    if (_revision < other._revision)
        return true;
    if (_build < other._build)
        return true;
    return false;
}

bool Version::operator == (const Version &other)
{
    return _major == other._major
           && _minor == other._minor
           && _revision == other._revision
           && _build == other._build;
}

Version::Version(std::string version)
        : _major(0), _minor(0), _revision(0), _build(0)
{
    if(0 > version.length() > 4)
    {
        throw std::runtime_error("Invalid python version - " + version);
    }

    std::sscanf(version.c_str(), "%d.%d.%d.%d", &_major, &_minor, &_revision, &_build); // NOLINT
}

std::string Version::toString()
{
    return std::to_string(_major) + "." +
            std::to_string(_minor) + '.' +
            std::to_string(_revision);
}

Version::~Version()
= default;
