// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/algorithm/string.hpp>
using namespace boost;

void StringAlgorithms() {
   std::string str(" Hello World ");
   std::string out = to_upper_copy(str);
   // out == " HELLO WORLD ");
   to_lower(str);
   // str == " hello world ");
   out = trim_copy(str);
   // out == "hello world"
   trim_left(str);
   // str == "hello world "
   trim_right(str);
   // str == "hello world"

   bool result = starts_with(str, "hello"); // true
   result = ends_with(str, "world"); // true
   result = contains(str, "lo wo"); // true
   result = equals(str, "hello world"); // true
   result = lexicographical_compare(str, "hello world and goodbye"); // true

   auto substr = find_first(str, "lo"); // begin: "lo world" end: " world", evaluates true
   replace_all(str, "lo", "LO");
   // str == "helLO world"
   std::vector<std::string> splitData;
   std::string input = "some things-seperated_by";
   split(splitData, input, is_any_of(" -_"), token_compress_on);
   // splitData == {"some", "things", "seperated", "by"}
}

BOOST_AUTO_TEST_CASE(String) {
   StringAlgorithms();
}