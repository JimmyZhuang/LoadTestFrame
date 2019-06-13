#ifndef __HTTP_H__
#define __HTTP_H__

#include <string>
#include <curl/curl.h>

class CHttp
{
	public:
		CHttp(int timout=5/*sec*/,bool isKeepAlive=true);
		~CHttp();

		void request(const std::string &method, const std::string &url, const std::string &req, std::string &rsp, const int timeout = 0);

	protected:
		CURL *curl;
		int timeout;
		bool isKeepAlive;
};


#endif

