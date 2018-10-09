// dl.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <stack>
#include <deque>
#include <unordered_map>
#include <set>
#include <cassert>
#include <sstream>
#include <iterator>

class tag
{
public:
	tag();

	void setContent(const std::string &content)
	{
		this->content = content;
	}

	std::string getContent() const
	{
		return content;
	}

	void setParent(tag *ptag)
	{
		parent = ptag;
	}

	tag * getParent() const
	{
		return parent;
	}

	void addChild(tag *child)
	{
		children.insert(child);
	}

	std::set<tag *> getChildren()
	{
		return children;
	}

	std::string& operator[](const std::string &attr)
	{
		return attrs[attr];
	}

private:
	tag *parent;
	std::set<tag *> children;
	std::string content;
	std::unordered_map<std::string, std::string> attrs;
};



class HtmlParser
{
public:
	HtmlParser();

	void streamParse(const std::string &buffer);

	void streamParse(const char *ptr, size_t size);

private:
	void pushChar(char ch);

	void parseTag(const std::string &tagString);

private:
	// parse tag
	std::deque<char> parse_tag_dq;
	// tag
	std::stack<tag *> tag_stk;
};