// dl.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <curl/curl.h>

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <map>

// TODO: Reference additional headers your program requires here.

class DL
{
public:
	enum Type
	{
		HTML,
		TEXT,
		IMG,
		UNSUPPORT
	};
	
	DL();
	~DL();
	
	void setProxy(const std::string &proxy);

	void setHeader(const std::map<std::string, std::string> &headers);

	// safe version
	bool safe_download(const std::string &url, const std::string &fileName = "");

	// write to file directly
	bool fast_download(const std::string &url, const std::string &fileName = "");
	//return raw string directly
	std::string get_content(const std::string &url);

	Type getType() const { return m_type; }

	std::string getBody() const { return m_body; }
	
private:
	static size_t writeToString(void *ptr, size_t size, size_t nmemb, void *buffer);

	static size_t writeToFile(void *ptr, size_t size, size_t nmemb, void *file);
	
	std::string getNameFromUrl(const std::string &url);

	void reset();

	bool checkStatus();

 	void setContentType();

private:
	CURL * m_curl;

	Type m_type;

	std::string m_header;
	std::string m_body;
	std::ofstream m_body_out;
};

