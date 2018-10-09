#include "htmlparser.h"

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
		assert(parse_tag_dq.empty());
		parseTag(std::string{parse_tag_dq.begin(), parse_tag_dq.end()});

	default:
		parse_tag_dq.push_back(ch);
		break;
	}
}

void HtmlParser::parseTag(const std::string &tagString)
{
	std::istringstream iss(tagString);
	std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
}
