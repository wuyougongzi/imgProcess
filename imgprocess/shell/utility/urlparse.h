#include <string>
#include <map>

using namespace std;

class UrlParse
{
public:
	UrlParse(const string &url);
	string getParam(const string &param);
public:
	void parsrUrl();
public:
	string m_rootUrl;
	string m_protocal;
	string m_host;
	string m_port;	//一般根据协议缺省
	string m_path;
	std::map<string, string> m_query;
	string m_fragment;
};