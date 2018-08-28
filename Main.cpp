
#include "StringDemo.h"				// string 实例
using namespace std;
#include <string>


#include <stdio.h>
#include <windows.h>  
#include <iostream>
#include <string>

using namespace std;


#define BUILDING_LIBCURL
#define HTTP_ONLY
#pragma comment(lib,"libcurl.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")
#pragma comment(lib,"ws2_32.lib")
#include <curl/curl.h>
#include "assert.h"

size_t Reply(void * ptr, size_t size, size_t nmemb, void * stream)
{
	string* str = (string*)stream;
	(*str).append((char*)ptr, size*nmemb);
	return size*nmemb;
}
wstring str_cvt(const string& from_str, int cvt_type) {
	int wstr_len = MultiByteToWideChar(cvt_type, 0, from_str.c_str(), -1, nullptr, 0);
	wchar_t *wstr = new wchar_t[wstr_len + 1];
	memset(wstr, 0, (wstr_len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(cvt_type, 0, from_str.c_str(), -1, wstr, wstr_len);
	wstring ret_str(wstr); delete[] wstr;
	return ret_str;
}
string str_cvt(const wstring& from_str, int cvt_type) {
	int str_len = WideCharToMultiByte(cvt_type, 0, from_str.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char *str = new char[str_len + 1];
	memset(str, 0, str_len + 1);
	WideCharToMultiByte(cvt_type, 0, from_str.c_str(), -1, str, str_len, nullptr, nullptr);
	string ret_str(str); delete[] str;
	return ret_str;
}

#define  SKIP_PEER_VERIFICATION 1  
//#define  SKIP_HOSTNAME_VERFICATION 1  

/*
ptr是指向存储数据的指针，
size是每个块的大小，
nmemb是指块的数目，
stream是用户参数。
所以根据以上这些参数的信息可以知道，ptr中的数据的总长度是size*nmemb
*/
size_t call_wirte_func(const char *ptr, size_t size, size_t nmemb, std::string *stream)
{
	assert(stream != NULL);
	size_t len = size * nmemb;
	stream->append(ptr, len);
	return len;
}
// 返回http header回调函数    
size_t header_callback(const char  *ptr, size_t size, size_t nmemb, std::string *stream)
{
	assert(stream != NULL);
	size_t len = size * nmemb;
	stream->append(ptr, len);
	return len;
}


size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream)
{
	cout << "----->reply" << endl;
	string *str = (string*)stream;
	cout << *str << endl;
	(*str).append((char*)ptr, size*nmemb);
	return size * nmemb;
}

// http GET  
CURLcode curl_get_req(const std::string &url, std::string &response)
{
	// init curl  
	CURL *curl = curl_easy_init();
	// res code  
	CURLcode res;
	if (curl)
	{
		// set params  
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3); // set transport and time out time  
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
		// start req  
		res = curl_easy_perform(curl);
	}
	// release curl  
	curl_easy_cleanup(curl);
	return res;
}

// http POST  
CURLcode curl_post_req(const string &url, const string &postParams, string &response)
{
	// init curl  
	CURL *curl = curl_easy_init();

	// res code  
	CURLcode res;
	if (curl)
	{
		// set params  
		curl_easy_setopt(curl, CURLOPT_POST, 1); // post req  
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str()); // params  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // if want to use https  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
		// start req  
		res = curl_easy_perform(curl);
	}
	// release curl  
	curl_easy_cleanup(curl);
	return res;
}


int main(int arg , char ** args)
{

	// global init  
	curl_global_init(CURL_GLOBAL_ALL);

	CURLcode res;
	// test get requery  
	string getUrlStr = "https://cn.bing.com/images/trending?form=Z9LH";
	string getResponseStr;
	res = curl_get_req(getUrlStr, getResponseStr);
	if (res != CURLE_OK)
		cerr << "curl_easy_perform() failed: " + string(curl_easy_strerror(res)) << endl;
	else
		cout << getResponseStr << endl;

	// test post requery  
// 	string postUrlStr = "https://www.baidu.com/s";
// 	string postParams = "f=8&rsv_bp=1&rsv_idx=1&word=picture&tn=98633779_hao_pg";
// 	string postResponseStr;
// 	res = curl_post_req(postUrlStr, postParams, postResponseStr);
// 	if (res != CURLE_OK)
// 		cerr << "curl_easy_perform() failed: " + string(curl_easy_strerror(res)) << endl;
// 	else
// 		cout << postResponseStr << endl;

	// global release  
	curl_global_cleanup();
	system("pause");
	return 0;
}