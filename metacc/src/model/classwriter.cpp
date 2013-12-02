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

        writeFieldMembers();

        writeMethodsDecl();

        writeClassEnding();

        if (_class.CopyOperator)
            writeCopyOperatorDef();
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

        if (!_class.ms.empty())
        {
            writeMethodsDef();
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
    _file << "\treturn true;" << std::endl;
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
    _file << "\treturn true;" << std::endl;
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

void ClassWriter::writeCopyOperatorDecl()
{
    _file << "\t" << _class.ClassName << "& operator=(const " << _class.ClassName << "& __in_);";
    _file << std::endl;
}

void ClassWriter::writeCopyOperatorDef()
{
    _file << "inline " << _class.ClassName << "& " << _class.ClassName << "::operator=(const " << _class.ClassName;
    _file << "& __in_)" << std::endl;
    _file << "{" << std::endl << "\t// TODO : implement your assignment code here" << std::endl;
    _file << "\treturn *this;" << std::endl;
    _file << "}" << std::endl << std::endl;
}

void ClassWriter::writeFieldMembers()
{
    _file << "public:" << std::endl;

    // public
    for (std::vector<FieldMember>::const_iterator it = _class.fms.begin();
         it != _class.fms.end(); ++it)
    {
        if ((*it).Range == PUBLIC)
            writeFieldMember(*it);
    }

    _file << std::endl << "protected:" << std::endl;

    // protected
    for (std::vector<FieldMember>::const_iterator it = _class.fms.begin();
         it != _class.fms.end(); ++it)
    {
        if ((*it).Range == PROTECTED)
            writeFieldMember(*it);
    }

    _file << std::endl << "private:" << std::endl;

    // private
    for (std::vector<FieldMember>::const_iterator it = _class.fms.begin();
         it != _class.fms.end(); ++it)
    {
        if ((*it).Range == PRIVATE)
            writeFieldMember(*it);
    }

    _file << std::endl;
}

void ClassWriter::writeFieldMember(const FieldMember &fm)
{
    _file << "\t" << (fm.isStatic?"static ":"") << (fm.isConst?"const ":"");
    _file << fm.Type << " " << fm.Name << ";" << std::endl;
}

void ClassWriter::writeMethodsDecl()
{
    _file << "public:" << std::endl;

    if (_class.DefaultConstructor)
        writeDefaultConstructorHPP();
    if (_class.CopyConstructor)
        writeCopyConstructorHPP();
    if (_class.Destructor)
        writeDestructorHPP();
    _file << std::endl;
    if (_class.CopyOperator)
        writeCopyOperatorDecl();
    if (_class.ComparisonOperator)
        writeComparisonOperatorDecl();
    if (_class.RelationalOperator)
        writeRelationalOperatorDecl();

    // public
    for (std::vector<Method>::const_iterator it = _class.ms.begin();
         it != _class.ms.end(); ++it)
    {
        if (it->Range == PUBLIC)
            writeMethodDecl(*it);
    }

    _file << "protected:" << std::endl;
    // public
    for (std::vector<Method>::const_iterator it = _class.ms.begin();
         it != _class.ms.end(); ++it)
    {
        if (it->Range == PROTECTED)
            writeMethodDecl(*it);
    }

    _file << "private:" << std::endl;
    // public
    for (std::vector<Method>::const_iterator it = _class.ms.begin();
         it != _class.ms.end(); ++it)
    {
        if (it->Range == PRIVATE)
            writeMethodDecl(*it);
    }

}

void ClassWriter::writeMethodDecl(const Method& m)
{
    _file << "\t" << (m.isVirtual?"virtual ":"") << (m.isStatic?"static ":"");
    _file << m.ReturnedValue << " " << m.Name << "(";

    if (!m.Parameters.empty())
    {
        std::vector<Parameter>::const_iterator it = m.Parameters.begin();

        _file << (it->isConst?"const ":"") << it->Type;
        if (!it->Default.empty())
        {
            _file << " = " << it->Default;
        }
        ++it;
        for (; it != m.Parameters.end() ; ++it)
        {
            _file << ", ";
            _file << (it->isConst?"const ":"") << it->Type;
            if (!it->Default.empty())
            {
                _file << " = " << it->Default;
            }
        }
    }

    _file << ")";
    _file << (m.isConst?" const":"");
    _file << (m.isAbstract?" = 0":"");
    _file << ";" << std::endl;
}

void ClassWriter::writeMethodsDef()
{
    for (std::vector<Method>::const_iterator it = _class.ms.begin() ;
         it != _class.ms.end() ; ++it)
    {
        if (!it->isAbstract) // && !it->isInline)
        {
            writeMethodDef(*it);
        }
    }
}

void ClassWriter::writeMethodDef(const Method& m)
{
    _file << (m.isVirtual?"virtual ":"") << (m.isStatic?"static ":"");
    _file << m.ReturnedValue << " " << _class.ClassName << "::" << m.Name << "(";

    if (!m.Parameters.empty())
    {
        std::vector<Parameter>::const_iterator it = m.Parameters.begin();

        _file << (it->isConst?"const ":"") << it->Type << " " << it->Name;
        ++it;
        for (; it != m.Parameters.end() ; ++it)
        {
            _file << ", ";
            _file << (it->isConst?"const ":"") << it->Type << " " << it->Name;
        }
    }

    _file << ")";
    _file << (m.isConst?" const":"");

    _file << std::endl << "{" << std::endl << std::endl << "}";
    _file << std::endl << std::endl;
}
