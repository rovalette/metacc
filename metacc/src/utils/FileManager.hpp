#ifndef __FILE_MANAGER_HPP__
#define __FILE_MANAGER_HPP__

#include <fstream>

class File
{
protected:
    std::string     _fileName;
    std::ofstream   _file;
    bool            _opened;

public:
    File(const std::string& fileName = "") :
        _fileName("/tmp/" + fileName), _opened(false) {}

    void setFileName(const std::string& fileName) {
        _fileName = "/tmp/" + fileName;
    }

    bool open() {
        if (_opened) _file.close(), _opened = false;
        _file.open(_fileName.c_str(), std::fstream::out | std::fstream::trunc);
        if (!_file.fail()) _opened = true;
        return (_opened);
    }

    bool exists() const {
        std::ifstream f(_fileName.c_str(), std::fstream::out | std::fstream::app);
        bool exists = !f.fail();
        f.close();
        return exists;
    }

    void close() {
        if (_file) _file.close(), _opened = false;
    }

    inline File& operator<<(const std::string& str) {
        _file << str;
        return *this;
    }

    // std endl, flush, ends
    inline File& operator<<(std::ostream& (*pf)(std::ostream&)) {
        pf(_file);
        return *this;
    }
};

#endif // __FILE_MANAGER_HPP__
