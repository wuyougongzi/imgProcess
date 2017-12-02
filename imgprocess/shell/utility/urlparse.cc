
#include "urlparse.h"
#include <string>
#include <algorithm>    // find
#include <vector>
using namespace std;


void spilt(string strSrc, string strTar, std::vector<string> &spiltVec)
{
	size_t sp = 0;
	size_t ep  = 0;
	do 
	{
		ep = strSrc.find(strTar, sp);
		spiltVec.push_back(strSrc.substr(sp, ep -sp));
		sp = ep + strTar.length();
	} while (ep != string::npos);
}


UrlParse::UrlParse(const string &url) 
	: m_rootUrl(url)
{
	parsrUrl();
}

void UrlParse::parsrUrl()
{
	string tmpUrl = m_rootUrl;
	int pEnd = tmpUrl.find(":");
	m_protocal = tmpUrl.substr(0, pEnd);
	
	//Ìø¹ý"://"
	int hEnd = tmpUrl.find("/", pEnd + 3);
	string tmpHost = tmpUrl.substr(pEnd + 3, hEnd - pEnd - 3);
	{
		string::size_type iSz = tmpHost.find(":");
		if(iSz != string::npos)
		{
			m_host = tmpHost.substr(0, iSz);
			m_port = tmpHost.substr(iSz, tmpHost.length());
		}
		else
		{
			m_host = tmpHost;
			
			m_port = "80";	//default port;
		}
	}

	pEnd = tmpUrl.find("?", hEnd);
	m_path = tmpUrl.substr(hEnd, pEnd - hEnd);
	
	hEnd = tmpUrl.find("#", pEnd);
	//Ìø¹ý"?" 
	string strTmpQuery = tmpUrl.substr(pEnd + 1, hEnd - pEnd - 1);
	
	{
		int sp = 0;
		int ep = 0;
		string subQuery;
		do 
		{
			ep = strTmpQuery.find("&", sp);
			subQuery = strTmpQuery.substr(sp, ep - sp);
			int equalIndex = subQuery.find("=");
			string param = subQuery.substr(0, equalIndex);
			string value = subQuery.substr(equalIndex + 1, subQuery.length() - equalIndex - 1);
			m_query.insert(std::make_pair(param, value));
			//Ìø¹ý "&"
			sp = ep + 1;
		} while (ep != string::npos);
		
	}
	if (hEnd < (tmpUrl.length() - 1))
	{
		m_fragment = tmpUrl.substr(hEnd + 1, tmpUrl.length() - hEnd - 1);
	}
}

string UrlParse::getParam(const string &param)
{
	std::map<string, string>::iterator it = m_query.find(param);
	if (it != m_query.end())
	{
		return it->second;
	}
	return "";
}
