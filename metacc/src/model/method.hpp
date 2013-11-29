#ifndef __METHOD_HPP__
#define __METHOD_HPP__

#include <string>
#include <vector>
#include "src/model/parameter.hpp"
#include "src/model/range.hpp"

struct Method
{
    RANGE           Range;

    std::string     Name;

    Parameter       ReturnedValue;

    std::vector<Parameter>  Parameters;

    bool            isStatic;
    bool            isConst;
    bool            isVirtual;
    bool            isAbstract;
};

#endif // __METHOD_HPP__
