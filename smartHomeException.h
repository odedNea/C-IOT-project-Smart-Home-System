#ifndef _SMART_HOME_EXCEPTION_H_
#define _SMART_HOME_EXCEPTION_H_

//#include <exception>
#include <stdexcept>
#include <string>

class SB_Exception : public std::runtime_error
{
public:
	SB_Exception(const std::string& msg) : std::runtime_error(msg) {}
};


class HubException : public SB_Exception
{
public:
	HubException(const std::string& msg) : SB_Exception(msg) {}
};


class InitException : public SB_Exception
{
public:
	InitException(const std::string& msg) : SB_Exception(msg) {}
};


class SchedulerException : public SB_Exception
{
public:
	SchedulerException(const std::string& msg) : SB_Exception(msg) {}
};

class LibraryException : public SB_Exception
{
public:
	LibraryException(const std::string& msg) : SB_Exception(msg) {}
};


#endif //_SMART_HOME_EXCEPTION_H_



