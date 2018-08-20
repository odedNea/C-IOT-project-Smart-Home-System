#ifndef _CONFIGURATOR_H_
#define _CONFIGURATOR_H_

#include <string>
#include <fstream>



struct ConfigStruct
{
	std::string m_type;
	std::string m_room;
	std::string m_floor;
	std::string m_config;
	std::string m_log;
};


class Configurator
{
public:
	Configurator(std::string& m_filePath);

	int Config(ConfigStruct& _pack);
	
private:
	std::ifstream m_is;

};



#endif //_CONFIGURATOR_H_
