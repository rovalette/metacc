#ifndef __CLASS_DEFINITION_HPP__
#define __CLASS_DEFINITION_HPP__

#include <string>
#include <vector>
#include "src/model/fieldmember.hpp"

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
    bool            RelationalOperator;
    bool            CopyOperator;

    std::vector<FieldMember> fms;
};

#endif // __CLASS_DEFINITION_HPP__
