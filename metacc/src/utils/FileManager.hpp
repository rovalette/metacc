#ifndef __FILE_MANAGER_HPP__
#define __FILE_MANAGER_HPP__

#include <fstream>

class FileManager
{
protected:
    std::string     _fileName;
    std::ofstream   _file;
    bool            _opened;

public:
    FileManager(const std::string& fileName) :
        _fileName(fileName), _opened(false) {}

    bool open() {
        if (_opened) _file.close(), _opened = false;
        _file.open(_fileName.c_str());
        if (!_file.fail()) _opened = true;
        return (_opened);
    }

    bool exists() const {
        std::ifstream f(_fileName.c_str());
        return !f.fail();
    }

    void close() {
        if (_file) _file.close(), _opened = false;
    }

    inline FileManager& operator<<(const std::string& str) {
        _file << str;
        return *this;
    }

    // std endl, flush, ends
    inline FileManager& operator<<(std::ostream& (*pf)(std::ostream&)) {
        pf(*_file);
        return *this;
    }
};

#endif // __FILE_MANAGER_HPP__
