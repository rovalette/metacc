#ifndef __LOG_MANAGER_HPP__
#define __LOG_MANAGER_HPP__

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <iterator>

class Log
{
protected:
	static std::ostream * _os;
	
public:
	
	static void setOutput(std::ostream * os) { _os = os; }
	static std::ostream * getOutput() { return _os; }
	
	// use of std::endl and other ostream manipulators (flush,ends)
	inline Log& operator<<(std::ostream& (*pf)(std::ostream&))
	{
		pf(*_os);
		return *this;
	}
	
	// generic operator <<
	template <typename T>
	inline Log& operator<<(const T& t)
	{
		*_os << t;
		return *this;
	}
	
	// specialized operator << for list
	template <typename T>
	inline Log& operator<<(const std::list<T>& l)
	{
		for (typename std::list<T>::const_iterator it = l.begin() ; it != l.end() ; ++it)
		{
			*this << *it << std::endl;
		}
		
		return *this;
	}
	
	// specialized operator << for vector
	template <typename T>
	inline Log& operator<<(const std::vector<T>& l)
	{
		unsigned i = 0;
		for (typename std::vector<T>::const_iterator it = l.begin() ; it != l.end() ; ++it, ++i)
		{
			*this << "[" << i << "] = " << *it << std::endl;
		}
		
		return *this;
	}
	
	// specialized operator << for map
	template <typename K, typename V>
	inline Log& operator<<(const std::map<K,V>& m)
	{
		for (typename std::map<K,V>::const_iterator it = m.begin() ; it != m.end() ; ++it)
		{
			*this << "[ " << it->first << " ; " << " ]" << std::endl;
		}
		
		return *this;
	}
};

//std::ostream * Log::_os(&std::cout);

// specialized operator << for bool
template <>
inline Log& Log::operator<< <bool>(const bool& b)
{
	*_os << ( b ? "true" : "false" );
	return *this;
}

// specialized operator << for string
template <>
inline Log& Log::operator<< <std::string>(const std::string& s)
{
	*_os << '"' << s << '"';
	return *this;
}

#endif // __LOG_MANAGER_HPP__
