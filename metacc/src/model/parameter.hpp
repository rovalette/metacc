#ifndef __PARAMETER_HPP__
#define __PARAMETER_HPP__

#include <string>
#include "src/model/range.hpp"

struct Parameter
{
    RANGE               Range;

    std::string         Name;
    std::string         Type;
    std::string         Default;

    bool                isConst;
};

#endif // __PARAMETER_HPP__
