#include "classwriter.hpp"
#include <QString>

ClassWriter::ClassWriter()
{
}

void ClassWriter::write()
{
    writeHPP();
    writeCPP();
}

void ClassWriter::writeHPP()
{
    Log log;

    _file.setFileName(_class.FileName + ".hpp");

    if (_file.open())
    {
        log << "File " << _file.getFileName() << "opened" << std::endl;
        writeTopGuardian();
        writeIncludes();
        writeClassBeginning();
        writeClassEnding();
        writeDownGuardian();
        _file.close();
        log << "File closed" << std::endl;
    }
    else
    {
        log << "Cannot open file : " << _file.getFileName() << std::endl;
    }
}

void ClassWriter::writeCPP()
{
    Log log;

    _file.setFileName(_class.FileName + ".cpp");

    if (_file.open())
    {
        log << "File " << _file.getFileName() << "opened" << std::endl;
        _file << "#include \"" << QString(_class.ClassName.c_str()).toLower().toStdString() << ".hpp\"" << std::endl;
        _file.close();
        log << "File closed" << std::endl;
    }
    else
    {
        log << "Cannot open file : " << _file.getFileName() << std::endl;
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
