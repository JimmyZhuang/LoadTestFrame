#ifndef __THREADMANAGER_H__
#define __THREADMANAGER_H__

#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include "scenario.h"

class CThreadManager
{
public:
    CThreadManager(unsigned int m_monitor_interval);
    ~CThreadManager() {};

    void add_scenario(CAbstractScenario* scenario);
    void run();
    void join();

public:
	unsigned int m_monitor_interval;
	std::vector<CAbstractScenario*> m_scenarios;
	std::map<std::string, std::vector<CAbstractScenario*> > m_copy_scenarios;
	std::vector<std::thread*> m_thread_pool;
	bool is_stop;
	unsigned int m_done_count;
};

extern std::mutex g_mutex;
extern CThreadManager g_thread_manager;

#endif
