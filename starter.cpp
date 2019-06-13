#include <iostream>
#include <mutex>

#include "thread_manager.h"
#include "tencentcloudapi_instance_example.h"
#include "http_instance_example.h"

using namespace std;

mutex g_mutex;
CThreadManager g_thread_manager(1);

int main(int argc,char *argv[])
{
    CTencentCloudApiInstanceExample *api_scenario = new CTencentCloudApiInstanceExample();
    api_scenario->Init();
    g_thread_manager.add_scenario(api_scenario);

    CHttpInstanceExample *http_scenario = new CHttpInstanceExample();
    http_scenario->Init();
    g_thread_manager.add_scenario(http_scenario);

    g_thread_manager.run();
    bool is_quit = false;
    string q;
    while(!is_quit)
    {
        cout << "press q/Q + Enter is quit:" << endl;
        cin >> q;
        if(q=="q" || q=="Q")
        {
            g_thread_manager.is_stop = true;
            is_quit = true;
        }
    }
    g_thread_manager.join();

    return 0;
}

