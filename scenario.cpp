#include "scenario.h"
#include "my_exception.h"
#include <iostream>

bool CAbstractScenario::real_action()
{
	try {
		return action();
	}
    catch(ClientException &e)
    {
        std::cout<<"Client Exceptrion:"<<e.what()<< std::endl;
        return false;
    }
    catch (...) {
        return false;
    }
}

void CAbstractScenario::stat_info(long costTime, bool ret, unsigned int count)
{
	if(ret)
		m_stat_done_count += count;
	else
		m_stat_failed_count += count;
	m_stat_response_time += costTime;
}

void CAbstractScenario::clear_stat_info()
{
    m_stat_done_count = 0;
    m_stat_failed_count = 0;
    m_stat_response_time = 0;
}

CAbstractScenario *CAbstractScenario::real_create_copy()
{
    CAbstractScenario *new_scenario = create_copy();
    new_scenario->Init();
    return new_scenario;
}
