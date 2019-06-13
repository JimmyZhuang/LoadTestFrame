#ifndef __MY_EXCEPTION_H__
#define __MY_EXCEPTION_H__

#include <exception>
#include <string>

class ClientException : public std::exception
{
public:
    ClientException(const std::string &msg) throw()
    {
        this->msg = msg;
    }

    virtual ~ClientException() throw(){}

	virtual const char* what() const throw();

	std::string msg;
};

#endif
