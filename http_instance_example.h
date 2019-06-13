#ifndef __CHTTP_INSTANCE_EXAMPLE_H__
#define __CHTTP_INSTANCE_EXAMPLE_H__

#include "scenario.h"
#include <string>
#include "http.h"

class CHttpInstanceExample: public CAbstractScenario
{
public:
    CHttpInstanceExample() {}
    ~CHttpInstanceExample() {}

    void Init();
    bool action();
    void destory();
    CAbstractScenario *create_copy() {
        return new CHttpInstanceExample();
    }

public:
    std::string m_cgw_req_str;
    std::string m_url;
    CHttp *m_http;
};

#endif
