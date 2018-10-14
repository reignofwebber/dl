#include "htmlparser.h"
#include <iostream>
#include <vector>
#include <fstream>

Html::Html()
  : root_(0), has_error_(false)
{

}

bool Html::parseHtml(const std::string &filename)
{
  std::ifstream in(filename);
  if(!in.is_open()){
    std::cout << "Cannot open file " << filename << std::endl;
    return false;
  }
  char ch;
  in >> std::noskipws;
  while(in >> ch && !has_error_){
    std::cout << ch;
    pushChar(ch);
  }
  return true;
}

bool Html::parse(const std::string & buffer)
{
  for(auto itr = buffer.begin(); itr != buffer.end() && !has_error_; ++itr){
    pushChar(*itr);
  }
  return true;
}

bool Html::parse(const char * ptr, size_t size)
{
	auto pointer = ptr;
	size_t read_count = 0;

	while (read_count < size && !has_error_)
	{
		pushChar(*pointer++);
		++read_count;
	}
    return true;
}

void Html::pushChar(char ch)
{
	switch (ch)
	{
	case '<':
		// content
      if(!tag_stk_.empty()){
        tag_stk_.top()->addContent(std::string(parse_tag_dq_.begin(), parse_tag_dq_.end()));
      }
	  parse_tag_dq_.clear();
      break;
	case '>':
		// tag
		parseTag(parse_tag_dq_.begin(), parse_tag_dq_.end());
		parse_tag_dq_.clear();
        break;
	default:
		parse_tag_dq_.push_back(ch);
		break;
	}
}

template <typename ChIter>
void Html::parseTag(ChIter begin, ChIter end)
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
          name.clear();
        }else{
          assert(cur_name != "");
          (*tag)[cur_name].push_back(name);
          name.clear();
        }
      }
      continue;
    }
    if(*itr == '"'){
      ++quote_cnt;
      if(quote_cnt % 2) is_value = true;
      else{
        assert(cur_name != "");
        (*tag)[cur_name].push_back(name);
        name.clear();
        is_value = false;
      }
      continue;
    }

    name.push_back(*itr);
  }
  if(is_tag_end){
    while(true){
      //     assert(!tag_stk_.empty());
      if(tag_stk_.empty()){
        has_error_ = true;
        return;
      }
      if(tag_stk_.top()->name() == tag->name()){
        tag_stk_.pop();
        break;
      }else{
        tag_stk_.pop();
      }
    }
  }else{
    if(!tag_stk_.empty()){
      tag_stk_.top()->addChild(tag);
      tag->setParent(tag_stk_.top());
    }else{
      root_ = tag;
    }
    tag_stk_.push(tag);
  }
}
