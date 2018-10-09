// dl.cpp : Defines the entry point for the application.
//

#include "dl.h"
#include "htmlparser.h"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>

int main()
{
	//DL dl;
	//bool res = dl.safe_download("https://www.dofactory.com/reference/visual-studio-shortcuts");
	//if (res)
	//{
	//	if (dl.getType() == DL::HTML)
	//	{
	//		std::cout << dl.getBody() << std::endl;
	//	}
	//	
	//}

	//std::cout << dl.get_content("https://www.dofactory.com/reference/visual-studio-shortcuts");

	//auto start = std::chrono::system_clock::now();
	//dl.setProxy("http://127.0.0.1:1080");
	//dl.fast_download("https://www.isd.gov.hk/chi/images/gallery_calendar.jpg");

	//auto end = std::chrono::system_clock::now();
	//std::chrono::duration<double> elapsed_time = end - start;
	//std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	//std::cout << "done at "<< elapsed_time.count() << "s !";

	std::string s("this   is a              test");

	std::istringstream iss(s);
	std::copy(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << "jjjjjjjj";
	getchar();
	return 0;
}





















