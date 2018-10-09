#include "dl.h"
#include <ctime>

DL::DL()
{
	m_curl = curl_easy_init();
	if (!m_curl)
	{
		std::cout << "curl init failed. " << std::endl;
	}

	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
}

DL::~DL()
{
	if (m_curl)
	{
		curl_easy_cleanup(m_curl);
	}
}

void DL::setProxy(const std::string & proxy)
{
	curl_easy_setopt(m_curl, CURLOPT_PROXY, proxy.c_str());
}

void DL::setHeader(const std::map<std::string, std::string>& headers)
{
}

bool DL::safe_download(const std::string & url, const std::string &fileName)
{
	if (!m_curl) return false;

	reset();
	CURLcode res;

	// set url
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

	// set header data
	curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &m_header);
	curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, &DL::writeToString);
	curl_easy_setopt(m_curl, CURLOPT_NOBODY, 1L);
	res = curl_easy_perform(m_curl);

	if (res != CURLE_OK)
	{
		std::cout << curl_easy_strerror(res) << std::endl;
		return false;
	}

	// check response code
	if (!checkStatus())
	{
		std::cout << m_header << std::endl;
		return false;
	}

	// get content-type
	setContentType();
	if (m_type == UNSUPPORT)
	{
		std::cout << m_header << std::endl;
		return false;
	}

	// perform download

	// unset header data
	curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, 0L);
	curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, 0L);
	curl_easy_setopt(m_curl, CURLOPT_NOBODY, 0L);


	// set body data
	if (m_type < IMG)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_body);
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &DL::writeToString);
	}
	else
	{
		auto file = fileName;
		if (file == "")
		{
			file = getNameFromUrl(url);
		}
		m_body_out.open(file, std::ios::binary);
		if (!m_body_out.is_open())
		{
			std::cout << "can not open file to write. filename is " << file << std::endl;
			return false;
		}
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_body_out);
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &DL::writeToFile);
	}

	// perform
	res = curl_easy_perform(m_curl);

	if (res != CURLE_OK)
	{
		std::cout << curl_easy_strerror(res) << std::endl;
		return false;
	}
	return true;
}

bool DL::fast_download(const std::string & url, const std::string & fileName)
{
	if (!m_curl) return false;
	
	auto file = fileName;
	if (file == "") file = getNameFromUrl(url);
	std::ofstream out(file, std::ios::binary);
	
	if (!out.is_open())
	{
		std::cout << "can not open file to write. filename is " << file << std::endl;
		return false;
	}

	CURLcode res;

	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &out);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &DL::writeToFile);

	res = curl_easy_perform(m_curl);
	if (res != CURLE_OK)
	{
		std::cout << curl_easy_strerror(res) << std::endl;
		return false;
	}

	return true;
}

std::string DL::get_content(const std::string & url)
{
	if (!m_curl) return false;

	CURLcode res;
	std::string buffer;

	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &DL::writeToString);

	res = curl_easy_perform(m_curl);
	if (res != CURLE_OK)
	{
		std::cout << curl_easy_strerror(res) << std::endl;
		return std::string();
	}

	return buffer;
}

size_t DL::writeToString(void * ptr, size_t size, size_t nmemb, void * buffer)
{
	auto data = static_cast<std::string *>(buffer);
	data->append((char *)ptr, size * nmemb);
	return size * nmemb;
}

size_t DL::writeToFile(void * ptr, size_t size, size_t nmemb, void * file)
{
	auto out = static_cast<std::ofstream *>(file);
	out->write((char *)ptr, size * nmemb);
	return size * nmemb;
}

std::string DL::getNameFromUrl(const std::string & url)
{
	auto pos = url.find_last_of('/');
	if (pos == std::string::npos && pos != url.size() - 1)
	{
		std::time_t t = std::time(nullptr);
		char mbstr[100];
		if (std::strftime(mbstr, sizeof(mbstr), "%y-%m-%d-%H-%M-%S", std::localtime(&t)))
		{
			return mbstr;
		}
		else
		{
			assert(false);
			std::cout << "format time error." << std::endl;
			return std::string();
		}
	}
	else
	{
		return url.substr(pos + 1);
	}
}

void DL::reset()
{
	m_type = UNSUPPORT;
	m_header = "";
	m_body = "";
	if (m_body_out.is_open())
	{
		m_body_out.close();
	}
}

bool DL::checkStatus()
{
	assert(m_header.size());

	if (m_header.find("302") != std::string::npos)
		return true;
	return false;
}

void DL::setContentType()
{
	assert(m_header.size());

	if(m_header.find("html") != std::string::npos)
	{
		m_type = HTML;
	}
	else if (m_header.find("text") != std::string::npos)
	{
		m_type = TEXT;
	}
	else if (m_header.find("img") != std::string::npos)
	{
		m_type = IMG;
	}
	else 
	{
		m_type = UNSUPPORT;
	}
}
