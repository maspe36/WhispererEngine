//
// Created by Sam on 2/25/2018.
//

#include "../../../include/Network/Exceptions/JSONError.h"


const char *JSONError::what() const throw()
{
    return msg_.c_str();
}

JSONError::JSONError(const char *message)
        : runtime_error(message), msg_(message)
{
}

JSONError::JSONError(const std::string &message)
        : runtime_error(message), msg_(message)
{
}

JSONError::JSONError(json rawJSON)
        : runtime_error(rawJSON.dump(4)), msg_(rawJSON.dump(4))
{
}

JSONError::~JSONError() throw()
= default;
