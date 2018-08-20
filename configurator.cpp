#include "configurator.h"
#include "smartHomeException.h"


#include <sstream>

using namespace std;


Configurator::Configurator(string& m_filePath)
{
	m_is.open(m_filePath.data(), std::fstream::in);
	if (! m_is.good())
	{
		throw(InitException("fail to open config file"));
	}
}



int Configurator::Config(ConfigStruct& _pack)
{
	string token;
	
	
	while (getline(m_is, token, '\n'))
	{
		istringstream iss(token);
		string a, b, c;
		iss >> a >> b >>c;
	
	
		if (a[0] == '[')
		{
			continue;
		}
	
		else if (a == "type")
		{
			_pack.m_type = c;
		}
	
		else if (a == "room")
		{
			_pack.m_room = c;
		}
	
		else if (a == "floor")
		{
			_pack.m_floor = c;
		}
	
		else if (a == "log")
		{
			_pack.m_log = a;
		}
	
		else if (a == "config")
		{
			_pack.m_config = c;
		}
		
		else
		{
			return 1;
		}
		
	}
	
	m_is.close();
	return 0;
}


