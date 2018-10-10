#include "htmlparser.h"
#include <iostream>

void HtmlParser::streamParse(const std::string & buffer)
{

}

void HtmlParser::streamParse(const char * ptr, size_t size)
{
	auto pointer = ptr;
	size_t read_count = 0;

	while (read_count < size)
	{
		pushChar(*pointer++);
		++read_count;
	}
}

void HtmlParser::pushChar(char ch)
{
	switch (ch)
	{
	case '<':
		// content
		tag_stk.top()->setContent(std::string(parse_tag_dq.begin(), parse_tag_dq.end()));
		parse_tag_dq.clear();
	case '>':
		// tag
		parseTag(parse_tag_dq.begin(), parse_tag_dq.end());
		parse_tag_dq.clear();
	default:
		parse_tag_dq.push_back(ch);
		break;
	}
}

template <typename ChIter>
void HtmlParser::parseTag(ChIter begin, ChIter end)
{
	for (auto itr = begin; itr != end; ++itr)
	{
		char c = *itr;
	}
}
