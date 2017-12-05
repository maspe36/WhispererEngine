//
// Created by Sam on 11/18/2017.
//

#include "../../../include/Game/Python/Version.h"

#include <stdexcept>

bool Version::operator < (const Version &other) const
{
    if (m_major < other.m_major)
        return true;
    if (m_minor < other.m_minor)
        return true;
    if (m_revision < other.m_revision)
        return true;
    if (m_build < other.m_build)
        return true;
    return false;
}

bool Version::operator == (const Version &other) const
{
    return m_major == other.m_major
           && m_minor == other.m_minor
           && m_revision == other.m_revision
           && m_build == other.m_build;
}

Version::Version(std::string version)
        : m_major(0), m_minor(0), m_revision(0), m_build(0)
{
    if(0 > version.length() > 4)
    {
        throw std::runtime_error("Invalid python version - " + version);
    }

    std::sscanf(version.c_str(), "%d.%d.%d.%d", &m_major, &m_minor, &m_revision, &m_build); // NOLINT
}

std::string Version::toString()
{
    return std::to_string(m_major) + "." +
            std::to_string(m_minor) + '.' +
            std::to_string(m_revision);
}

Version::~Version()
= default;
