#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <sys/time.h>
#include "thread_manager.h"

using namespace std;

long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


void monitor()
{
    cout << "monitor start!" << endl;
    int total_count = 0;
    int total_failed_count = 0;
    while(!g_thread_manager.is_stop && g_thread_manager.m_done_count < g_thread_manager.m_thread_pool.size()-1)
    {
        string log_msg = "";
        for (auto iter = g_thread_manager.m_scenarios.begin(); iter != g_thread_manager.m_scenarios.end(); ++iter)
        {
            string name = (*iter)->m_name;
            int stat_done_count = 0;
            int stat_failed_count = 0;
            int stat_response_time = 0;
            for (auto iter2 = g_thread_manager.m_copy_scenarios[name].begin(); iter2 != g_thread_manager.m_copy_scenarios[name].end(); ++iter2)
            {
                CAbstractScenario* scenario = *iter2;
                stat_done_count += scenario->m_stat_done_count;
                stat_failed_count += scenario->m_stat_failed_count;
                stat_response_time += scenario->m_stat_response_time;
                scenario->clear_stat_info();
            }
            int scenario_count = stat_done_count + stat_failed_count;
            total_failed_count += stat_failed_count;
            if(scenario_count == 0)
            {
                cout << name << ":" << scenario_count << "(0)" <<endl;
            }
            else
            {
                total_count += scenario_count;
                cout << name << ":" << scenario_count << "(" << stat_response_time << ")" << endl;
            }
            ostringstream msg;
            float avg_late = 0.0;
            if(scenario_count!=0)
                avg_late = stat_response_time / (float)scenario_count;
            //sprintf(tmp,"<%s|%d|%d|%d|%f|%f>", name.c_str(), stat_done_count, stat_failed_count, stat_response_time, avg_late, (float)stat_done_count/g_thread_manager.m_monitor_interval);
            msg << "<" << name << "|" << stat_done_count << "|" << stat_failed_count
                << "|" << stat_response_time << "|" << avg_late << "|" << (float)stat_done_count/g_thread_manager.m_monitor_interval;
            log_msg += msg.str();
        }
        cout << "total:" << total_count << ", total failed:" << total_failed_count << endl;
        cout << log_msg << endl;
        cout << "---------------------------------" << endl;
        this_thread::sleep_for(chrono::seconds(g_thread_manager.m_monitor_interval));
    }
    cout << "runner is over,press q/Q + Enter for quit!" << endl;
}

void run_scenario(void  *arg)
{
    CAbstractScenario *scenario = (CAbstractScenario *)arg;
    unsigned int run_count = 0;
    while (!g_thread_manager.is_stop)
    {
        long startTs = getCurrentTime();
        bool ret = scenario->real_action();
        scenario->stat_info(getCurrentTime() - startTs, ret);
        run_count += 1;
        if (scenario->m_run_count > 0 && run_count >= scenario->m_run_count)
            break;
    }
    scenario->destory();

    lock_guard<mutex> lock(g_mutex);
    g_thread_manager.m_done_count += 1;
}


CThreadManager::CThreadManager(unsigned int monitor_interval)
{
    m_monitor_interval = monitor_interval;
    m_done_count = 0;
    is_stop = false;
}

void CThreadManager::add_scenario(CAbstractScenario* scenario)
{
    m_scenarios.push_back(scenario);
    for(unsigned int i=0; i<scenario->m_thread_num; i++)
    {
        CAbstractScenario* new_scenario = scenario->real_create_copy();
        m_copy_scenarios[scenario->m_name].push_back(new_scenario);
    }
}

void CThreadManager::run()
{
    for (auto iter = m_scenarios.begin(); iter != m_scenarios.end(); ++iter)
    {
        string name = (*iter)->m_name;
        for (auto iter2 = m_copy_scenarios[name].begin(); iter2 != m_copy_scenarios[name].end(); ++iter2)
        {
            thread *ti = new thread(run_scenario, (void *)(*iter2));
            m_thread_pool.push_back(ti);
        }
    }
    thread *t = new thread(monitor);
    m_thread_pool.push_back(t);
    cout << "start run! total: " << m_thread_pool.size()-1 << endl;
}

void CThreadManager::join()
{
    for (auto iter = m_thread_pool.begin(); iter != m_thread_pool.end(); ++iter)
    {
        if ((*iter)->joinable())
            (*iter)->join();

        delete *iter;
    }
}


