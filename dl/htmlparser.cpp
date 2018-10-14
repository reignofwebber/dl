#include "htmlparser.h"
#include <iostream>
#include <vector>

HtmlParser::HtmlParser()
  : root(0)
{

}


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
      if(!tag_stk.empty()){
        tag_stk.top()->addContent(std::string(parse_tag_dq.begin(), parse_tag_dq.end()));
      }
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
  bool is_tag_end = false;
  auto itr = begin;

  Tag *tag = new Tag;
  std::string name;

  // parse name
  for(;itr != end; ++itr){
    if(*itr == '/' && name == ""){
      is_tag_end = true;
      continue;
    }
    if(*itr == ' '){
      if(name == "") continue;
      else break;
    }

    name.push_back(*itr);
  }
  tag->setName(name);
  name.clear();

  // parse attrs
  bool is_value(false);
  uint8_t quote_cnt(0);
  std::string cur_name;
  for(;itr != end; ++itr){
    if(*itr == ' ' || *itr == '=' || *itr == '/'){
      if(name != ""){
        if(!is_value){
          cur_name = name;
        }else{
          assert(cur_name != "");
          (*tag)[cur_name].push_back(name);
        }
      }
      continue;
    }
    if(*itr == '"'){
      ++quote_cnt;
      if(quote_cnt % 2) is_value = true;
      else is_value = false;
      continue;
    }

    name.push_back(*itr);
  }
  if(is_tag_end){
    while(true){
      assert(!tag_stk.empty());
      if(tag_stk.top()->getName() == tag->getName()){
        tag_stk.pop();
        break;
      }else{
        tag_stk.pop();
      }
    }
  }else{
    if(!tag_stk.empty()){
      tag_stk.top()->addChild(tag);
      tag->setParent(tag_stk.top());
    }else{
      root = tag;
    }
    tag_stk.push(tag);
  }
}
