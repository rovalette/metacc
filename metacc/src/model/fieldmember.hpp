#ifndef __FIELD_MEMBER_HPP__
#define __FIELD_MEMBER_HPP__

#include <string>
#include "src/model/range.hpp"

struct FieldMember
{
    RANGE               range;

    std::string         Type;
    std::string         Name;
    std::string         Default; // mandatory if const !!

    bool                isConst;
    bool                isStatic;
    bool                hasGet;
    bool                hasSet;
};

#endif // __FIELDMEMBER_HPP
