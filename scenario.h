#ifndef __SCENARIO_H__
#define __SCENARIO_H__

#include <string>

class CAbstractScenario
{
public:
    CAbstractScenario(): m_name(""), m_thread_num(1), m_run_count(0), m_stat_done_count(0), m_stat_failed_count(0), m_stat_response_time(0) {}

    virtual ~CAbstractScenario() {}

    virtual void Init()=0;
    virtual bool action()=0;
    virtual void destory()=0;
    virtual CAbstractScenario *create_copy()=0;

    bool real_action();
    void stat_info(long costTime, bool ret=true, unsigned int count=1);
    void clear_stat_info();
    CAbstractScenario *real_create_copy();

public:
    std::string m_name;
    unsigned int m_thread_num;
    unsigned int m_run_count;
    unsigned int m_stat_done_count;
    unsigned int m_stat_failed_count;
    unsigned int m_stat_response_time;
};

#endif
