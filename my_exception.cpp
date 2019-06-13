#include "my_exception.h"

const char* ClientException::what() const throw()
{
    return this->msg.c_str();
}
