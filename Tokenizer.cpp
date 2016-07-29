// This runs the examples with the tests
#include <boost/test/unit_test.hpp>
#include <iostream>

#include <boost/tokenizer.hpp>
using namespace boost;

void Tokenizer() {
   std::string input = "This is a test-ish line";
   tokenizer<> tokens(input);
   std::string output = "";
   for (auto t = tokens.begin(); t != tokens.end(); t++) {
      output += *t + "_";
   }
   // output == "This_is_a_test_ish_line_"

   std::string ip4 = "123.045.067.089";
   std::string ip6 = "1234:5678:9abc:def0:1234:5678:9abc:def0";
   char_separator<char> sep(".:");

   tokenizer<char_separator<char> > sections4(ip4, sep);
   output = "";
   for (auto t = sections4.begin(); t != sections4.end(); t++) {
      output += *t + "_";
   }
   // output == "123_045_067_089_"

   tokenizer<char_separator<char> > sections6(ip6, sep);
   output ="";
   for (auto t = sections6.begin(); t != sections6.end(); t++) {
      output += *t + "_";
   }
   // output == "1234_5678_9abc_def0_1234_5678_9abc_def0_"
}

BOOST_AUTO_TEST_CASE(Token) {
   Tokenizer();
}