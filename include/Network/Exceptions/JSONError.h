//
// Created by Sam on 2/25/2018.
//

#ifndef WHISPERERENGINE_KEYERROR_H
#define WHISPERERENGINE_KEYERROR_H


#include <stdexcept>

class JSONError
        : public std::runtime_error
{
public:
    virtual const char* what() const throw();

    explicit JSONError(const char* message);
    explicit JSONError(const std::string& message);
    virtual ~JSONError() throw();

protected:
    std::string msg_;
};


#endif //WHISPERERENGINE_KEYERROR_H
