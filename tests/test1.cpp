
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Simple"
#include <boost/test/unit_test.hpp>

#include <iostream>
#include "htmlparser.h"

// BOOST_AUTO_TEST_CASE(test_string)
// {
// 	Html html;
//     html.parse("<html></html>");

//     BOOST_TEST(html.root()->name() == "html");

// }

BOOST_AUTO_TEST_CASE(test_file)
{
  Html html;
  if(html.parseHtml("a.html")){
    BOOST_TEST(!html.hasError());
    BOOST_TEST(html.root()->name() == "html");
    auto children = html.root()->children();
    for(auto itr = children.begin(); itr != children.end(); ++itr){
      auto tag = **itr;
      if(tag.has_attr("class")){
        std::cout << tag.name() <<  "'s class is ";
        auto class_ = tag["class"];
        for(auto itr = class_.begin(); itr != class_.end(); ++itr){
          std::cout << *itr << " ";
        }
      }else{
        std::cout << tag.name() << std::endl;
      }
    }

  }

}
