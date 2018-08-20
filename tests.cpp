#include "mu_test.h"
#include "smartBuilding.h"
#include "smartHomeException.h"


#include <string>
#include <stdio.h>
using namespace std;



UNIT(flow)
	try
	{
		SmartBuilding smartBuilding("config.ini");
		smartBuilding.Start();
	}
	catch(InitException& _except)
	{
		SmartBuilding smartBuilding("config2.ini");
		smartBuilding.Start();
	}
	
	ASSERT_THAT(1);
END_UNIT
	
	

	
TEST_SUITE(Initialization_Test)
	TEST(flow)
END_SUITE



