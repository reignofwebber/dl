
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Simple"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test1)
{
	BOOST_TEST(0 == 0);
	BOOST_TEST(1 == 2);
}


