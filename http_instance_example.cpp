#include <string>
#include "json/json.h"
#include "my_exception.h"
#include "http_instance_example.h"

using namespace std;

void CHttpInstanceExample::Init()
{
    m_thread_num = 1;
    m_run_count = 10;
    m_name = "http_example";

    m_url = "http://xxxx/interfaces/interface.php";

    Json::Value cgwReqPkg;
    Json::Value interface;
    Json::Value para;

    para["appId"] = 111111;
    interface["para"] = para;
    interface["interfaceName"] = "TestAction";
    cgwReqPkg["interface"] = interface;
    cgwReqPkg["version"] = 1;
    cgwReqPkg["componentName"] = "api";
    cgwReqPkg["eventId"] = 121;
    cgwReqPkg["timestamp"] = 1352121016;
    cgwReqPkg["user"] = "auto";

    Json::FastWriter writer;
    m_cgw_req_str = writer.write(cgwReqPkg);

    m_http = new CHttp();
}

bool CHttpInstanceExample::action()
{
    string result = "";
    int timeout = 3;
    m_http->request("POST", m_url, m_cgw_req_str, result, timeout);

    Json::Reader reader;
    Json::Value value;
    if(!reader.parse(result, value))
    {
        throw ClientException("Json parse failed, result:"+result);
        return false;
    }

    int code = value["code"].asInt();
    if(code != 0)
    {
        throw ClientException("code!=0, result:"+result);
        return false;
    }

    return true;
}

void CHttpInstanceExample::destory()
{

}
