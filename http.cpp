#include "http.h"
#include <string>
#include "my_exception.h"
#include <sstream>

using namespace std;

class HttpGlobalInit
{
public:
    HttpGlobalInit()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    ~HttpGlobalInit()
    {
        curl_global_cleanup();
    }
};
static HttpGlobalInit __http_global_init__;


static size_t http_write_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
    size_t n = size * nmemb;
    string *rsp = (string*)userp;

    rsp->append((const char*)buffer, n);

    return n;
}

static string int2str(int n)
{
    stringstream ss;
    ss<<n;
    return ss.str();
}

CHttp::CHttp(int timeout,bool isKeepAlive)
{
	this->timeout = timeout;
	this->isKeepAlive = isKeepAlive;
	this->curl = NULL;
}

CHttp::~CHttp()
{
	if(this->curl != NULL)
	{
		curl_easy_cleanup(this->curl);
		this->curl = NULL;
	}
}

void CHttp::request(const string &method, const string &url, const string &req, string &rsp,const int timeout)
{
	if(!this->isKeepAlive)
	{
		this->curl = curl_easy_init();
	}
	else
	{
		if(this->curl == NULL)
			this->curl = curl_easy_init();

	}

	if(this->curl == NULL)
	{
		throw ClientException("Curl init failed");
		return;
	}

	curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_CONNECTTIMEOUT, this->timeout);
	curl_easy_setopt(this->curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(this->curl, CURLOPT_TIMEOUT, this->timeout+timeout);
	//curl_easy_setopt(this->curl, CURLOPT_TCP_KEEPALIVE, 1L);
	//curl_easy_setopt(this->curl, CURLOPT_TCP_KEEPIDLE, 120L);
	//curl_easy_setopt(this->curl, CURLOPT_TCP_KEEPINTVL, 60L);
	curl_slist* header = NULL;
	if(this->isKeepAlive)
	{
		header = curl_slist_append(header, "Connection: keep-alive");
		curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, header);
	}

	curl_easy_setopt(this->curl, CURLOPT_ENCODING, "UTF-8");

	if(method == "POST")
	{
		curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
		curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, req.c_str());
	}

	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, http_write_callback);
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, (void *)&rsp);

	CURLcode ret = curl_easy_perform(this->curl);
	if(this->isKeepAlive)
		curl_slist_free_all(header);

	if(ret != CURLE_OK)
	{
		string error = "Curl Send Request Fail, code:" + int2str(ret) + " ,error:" + curl_easy_strerror(ret) + " ,rsp:" + rsp;
		throw ClientException(error);
		return;
	}

	//long status = 0;
	//curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &status);
	//if(status != 200)
    //{
    //    string error = "http rsp status!=200, status:" + int2str(status) + " ,rsp:" + rsp;
    //    throw ClientException(error);
    //}
}

