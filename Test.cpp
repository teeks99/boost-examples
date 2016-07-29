// This includes a main() function here that will execute the tests.
// Obviously you only need one of these per test executable.
#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>

// Usually the object under test would be in a different file
class Converter {
public:
   Converter(int multiplier = 1)
      : multiplier(multiplier)
   {}

   int Add(int first, int second)
   {
      return multiplier * (first + second);
   }
private:
   int multiplier;
};


BOOST_AUTO_TEST_SUITE( Unit )
BOOST_AUTO_TEST_SUITE( ConverterTest )

BOOST_AUTO_TEST_CASE( BasicAdd ) {
   Converter conv;
   int expected = 3;

   int output = conv.Add(1, 2);

   BOOST_CHECK_EQUAL(expected, output);
}

class ConverterFixture {
public:
   ConverterFixture() {
      first = 1;
      second = 2;
      expected = 3;
   }

   int first;
   int second;
   int expected;

   Converter conv;

   void Check() {
      int result = conv.Add(first, second);
      BOOST_CHECK_EQUAL(expected, result);
   }
};

BOOST_FIXTURE_TEST_CASE(Default, ConverterFixture){
   Check();
}
BOOST_FIXTURE_TEST_CASE(OtherValue, ConverterFixture) {
   first = 2;
   second = 3;
   expected = 5;

   Check();
}
BOOST_FIXTURE_TEST_CASE(Multiplier, ConverterFixture) {
   int multiplier = 10;
   expected = 30;
   conv = Converter(multiplier);

   Check();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Integration )
BOOST_AUTO_TEST_SUITE( ConverterTest )

BOOST_AUTO_TEST_CASE(LotsOfAdding) {
   Converter conv;
   for (int i = 0; i < 500000; i++)
   {
      BOOST_CHECK_EQUAL(i + 1, conv.Add(i, 1));
   }
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()