#ifndef __CLASS_WRITER_HPP__
#define __CLASS_WRITER_HPP__

#include "src/model/classdefinition.hpp"
#include "src/utils/FileManager.hpp"
#include "src/utils/LogManager.hpp"

class ClassWriter
{
protected:
    File                _file;
    ClassDefinition     _class;

    void writeTopGuardian();
    void writeIncludes();
    void writeClassBeginning();
    void writeClassEnding();
    void writeDownGuardian();

public:
    ClassWriter();

    void setFileName(const std::string& fileName) {
        _file.setFileName(fileName);
    }

    void setClassDefinition(const ClassDefinition& classDef) {
        _class = classDef;
    }

    void write();
};

#endif // __CLASS_WRITER_HPP__
