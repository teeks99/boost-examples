// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/lexical_cast.hpp>
using namespace boost;

void LexicalCast()
{
   short val1 = lexical_cast<short>("12345");
   double val2 = lexical_cast<double>("1.23e4");
   std::string val3 = lexical_cast<std::string>(12345);
   std::string val4 = lexical_cast<std::string>(1.23e4);

   std::string embedded = "cut me 123";
   int val5 = lexical_cast<int>(embedded.data() + 7, 3);
}

BOOST_AUTO_TEST_CASE( Lexical ){
   LexicalCast();
}