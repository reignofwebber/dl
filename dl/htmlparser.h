// dl.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <unordered_map>
#include <set>
#include <cassert>
#include <sstream>
#include <iterator>

class Tag
{
public:
  Tag()
    : parent(0)
  {

  }

	Tag(const std::string &name)
      : name(name), parent(0)
	{
	}

  void setName(const std::string &name)
  {
    this->name = name;
  }

  std::string getName() const
  {
    return name;
  }

	void addContent(const std::string &content)
	{
		this->content += content;
	}

	std::string getContent() const
	{
		return content;
	}

	void setParent(Tag *ptag)
	{
		parent = ptag;
	}

	Tag * getParent() const
	{
		return parent;
	}

	void addChild(Tag *child)
	{
		children.insert(child);
	}

	std::set<Tag *> getChildren()
	{
		return children;
	}

	std::vector<std::string>& operator[](const std::string &attr)
	{
		return attrs[attr];
	}

private:
	Tag *parent;
	std::set<Tag *> children;
	std::string name;
	std::string content;
	std::unordered_map<std::string, std::vector<std::string>> attrs;
};



class HtmlParser
{
public:
	HtmlParser();

	void streamParse(const std::string &buffer);

	void streamParse(const char *ptr, size_t size);

private:
	void pushChar(char ch);

	template <typename ChIter>
	void parseTag(ChIter begin, ChIter end);


private:
	// parse tag
	std::deque<char> parse_tag_dq;
	// tag
	std::stack<Tag *> tag_stk;
    // tag tree head
    Tag *root;

};
