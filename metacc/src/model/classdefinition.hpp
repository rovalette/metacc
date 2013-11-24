#ifndef __CLASS_DEFINITION_HPP__
#define __CLASS_DEFINITION_HPP__

#include <string>

struct ClassDefinition
{
    bool            twoFiles;

    std::string     ClassName;
    std::string     Guardian;
    std::string     FileName;

    bool            DefaultConstructor;
    bool            CopyConstructor;
    bool            Destructor;
    bool            VirtualDestructor;

    bool            ComparisonOperator;
};

#endif // __CLASS_DEFINITION_HPP__
