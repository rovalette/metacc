#include "classwriter.hpp"

ClassWriter::ClassWriter()
{
}

void ClassWriter::write()
{
    Log log;

    _file.setFileName(_class.FileName + ".hpp");
    log << _class.FileName << std::endl;
    if (_file.open())
    {
        log << "File opened" << std::endl;
        writeTopGuardian();
        writeIncludes();
        writeClassBeginning();
        writeClassEnding();
        writeDownGuardian();
        _file.close();
        log << "File closed" << std::endl;
    }
}

void ClassWriter::writeTopGuardian()
{
    _file << "#ifndef " << _class.Guardian << std::endl;
    _file << "#define " << _class.Guardian << std::endl << std::endl;
}

void ClassWriter::writeIncludes()
{

}

void ClassWriter::writeClassBeginning()
{
    _file << "class " << _class.ClassName << std::endl;
    _file << "{" << std::endl;
}

void ClassWriter::writeClassEnding()
{
    _file << "};" << std::endl << std::endl;
}

void ClassWriter::writeDownGuardian()
{
    _file << "#endif // " << _class.Guardian << std::endl;
}
