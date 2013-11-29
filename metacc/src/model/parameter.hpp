#ifndef __PARAMETER_HPP__
#define __PARAMETER_HPP__

#include <string>

struct Parameter
{
    std::string         Name;
    std::string         Type;
    std::string         Default;

    bool                isConst;
};

#endif // __PARAMETER_HPP__
