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

        _file << "public:" << std::endl;
        if (_class.DefaultConstructor)
            writeDefaultConstructorHPP();
        if (_class.CopyConstructor)
            writeCopyConstructorHPP();
        if (_class.Destructor)
            writeDestructorHPP();
        _file << std::endl;
        if (_class.ComparisonOperator)
            writeComparisonOperatorDecl();
        if (_class.RelationalOperator)
            writeRelationalOperatorDecl();

        writeClassEnding();


        if (_class.ComparisonOperator)
            writeComparisonOperatorDef();
        if (_class.RelationalOperator)
            writeRelationalOperatorDef();

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
        _file << "#include \"" << QString(_class.ClassName.c_str()).toLower().toStdString() << ".hpp\"" << std::endl << std::endl;
        if (_class.DefaultConstructor)
        {
            writeDefaultConstructorCPP();
            _file << std::endl;
        }
        if (_class.CopyConstructor)
        {
            writeCopyConstructorCPP();
            _file << std::endl;
        }
        if (_class.Destructor)
        {
            writeDestructorCPP();
            _file << std::endl;
        }

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

void ClassWriter::writeDefaultConstructorHPP()
{
    _file << "\t" << _class.ClassName << "()" << (_class.twoFiles?";":" { }");
    _file << std::endl;
}

void ClassWriter::writeDefaultConstructorCPP()
{
    _file << _class.ClassName << "::" << _class.ClassName;
    _file << "()" << std::endl;
    _file << "{" << std::endl << std::endl << "}" << std::endl;
}

void ClassWriter::writeCopyConstructorHPP()
{
    _file << "\t" << _class.ClassName << "(const " << _class.ClassName << "& __in_";
    _file << ")" << (_class.twoFiles?";":" { }");
    _file << std::endl;
}

void ClassWriter::writeCopyConstructorCPP()
{
    _file << _class.ClassName << "::" << _class.ClassName;
    _file << "(const " << _class.ClassName << "& __in_)" << std::endl;
    _file << "{" << std::endl << std::endl << "}" << std::endl;
}

void ClassWriter::writeDestructorHPP()
{
    _file << "\t" << (_class.VirtualDestructor?"virtual ":"");
    _file << "~" << _class.ClassName << "()" << (_class.twoFiles?";":" { }");
    _file << std::endl;
}

void ClassWriter::writeDestructorCPP()
{
    _file << _class.ClassName << "::" << "~" << _class.ClassName;
    _file << "()" << std::endl;
    _file << "{" << std::endl << std::endl << "}" << std::endl;
}

void ClassWriter::writeComparisonOperatorDecl()
{
    _file << "\tfriend bool operator==(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b);" << std::endl;
    _file << "\tfriend bool operator!=(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b);" << std::endl;
}

void ClassWriter::writeComparisonOperatorDef()
{
    _file << "inline bool operator==(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b)" << std::endl << "{" << std::endl;
    _file << "\t// TODO : implement your comparison operator code here" << std::endl;
    _file << "\tbool ret = (&a == &b);" << std::endl << "\treturn ret;" << std::endl;
    _file << "}" << std::endl << std::endl;

    _file << "inline bool operator!=(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b)" << std::endl << "{" << std::endl;
    _file << "\treturn !(a==b);" << std::endl;
    _file << "}" << std::endl << std::endl;
}

void ClassWriter::writeRelationalOperatorDecl()
{
    _file << "\tfriend bool operator<(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b);" << std::endl;
    _file << "\tfriend bool operator<=(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b);" << std::endl;
    _file << "\tfriend bool operator>(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b);" << std::endl;
    _file << "\tfriend bool operator>=(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b);" << std::endl;
}

void ClassWriter::writeRelationalOperatorDef()
{
    _file << "inline bool operator<(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b)" << std::endl << "{" << std::endl;
    _file << "\t// TODO : implement your operator < code here" << std::endl;
    _file << "\tbool ret = (&a < &b);" << std::endl << "\treturn ret;" << std::endl;
    _file << "}" << std::endl << std::endl;

    _file << "inline bool operator<=(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b)" << std::endl << "{" << std::endl;
    _file << "\treturn ((a<b) || (a==b));" << std::endl;
    _file << "}" << std::endl << std::endl;

    _file << "inline bool operator>(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b)" << std::endl << "{" << std::endl;
    _file << "\treturn !(a<=b);" << std::endl;
    _file << "}" << std::endl << std::endl;

    _file << "inline bool operator>=(const " << _class.ClassName << "& a, const ";
    _file << _class.ClassName << "& b)" << std::endl << "{" << std::endl;
    _file << "\treturn !(a<b);" << std::endl;
    _file << "}" << std::endl << std::endl;
}
