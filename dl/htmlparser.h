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
    : parent_(0)
  {

  }

	Tag(const std::string &name)
      : name_(name), parent_(0)
	{
	}

  void setName(const std::string &name)
  {
    name_ = name;
  }

  std::string name() const
  {
    return name_;
  }

	void addContent(const std::string &content)
	{
		content_ += content;
	}

	std::string content() const
	{
		return content_;
	}

	void setParent(Tag *parent)
	{
		parent_ = parent;
	}

	Tag * parent() const
	{
		return parent_;
	}

	void addChild(Tag *child)
	{
		children_.insert(child);
	}

	std::set<Tag *> children()
	{
		return children_;
	}

	std::vector<std::string>& operator[](const std::string &attr)
	{
		return attrs_[attr];
	}

    bool has_attr(const std::string &attr)
    {
      return attrs_.find(attr) != attrs_.end();
    }

private:
	Tag *parent_;
	std::set<Tag *> children_;
	std::string name_;
	std::string content_;
	std::unordered_map<std::string, std::vector<std::string>> attrs_;
};



class Html
{
public:
	Html();

    bool parseHtml(const std::string &filename);

	bool parse(const std::string &buffer);

	bool parse(const char *ptr, size_t size);

    Tag *root(){return root_;}

    bool hasError(){return has_error_;}


private:
	void pushChar(char ch);

	template <typename ChIter>
	void parseTag(ChIter begin, ChIter end);


private:
	// parse tag
	std::deque<char> parse_tag_dq_;
	// tag
	std::stack<Tag *> tag_stk_;
    // tag tree head
    Tag *root_;

    // has error;
    bool has_error_;
};
