// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

// If you want to seamlessly upgrade to C++11 smart pointers, you can do
// something like this for includes:

// #if _MSC_VER < 1600 // Visual Studio 2010+
//  #include <boost/smart_ptr.hpp>
//  using namespace boost;
// #else
//  #include <memory>
//  using namespace std;
// #endif


// Very Simple Example

#include <boost/smart_ptr.hpp>
using namespace boost;

struct MyType { int something; };
shared_ptr<MyType> Factory(int value) {
   auto an_object = shared_ptr<MyType>(
      new MyType);
   an_object->something = value;
   return an_object;
}

void TopLevel(){
   auto an_object = Factory(3);
   // .. do other things with an_object
   // destroyed when all users are out of scope
}


BOOST_AUTO_TEST_CASE(SimpleSmartPointer) {
   TopLevel();
}

// More complicated Example, uses MyType and Factory from above. This would be
// extremely difficult to implement (without memory leaks) using normal
// pointers to objects.
#include <list>

void Executive() {
   std::list<shared_ptr<MyType>> low_numbers;
   std::list<shared_ptr<MyType>> odd_starts;
   // For telemetery
   std::list<weak_ptr<MyType>> alive_objects;
   int i = 0;

   while (i < 1000) {
      // Add numbers to a list depending if they are low or odd, keeps a
      // weak_ptr for everything, for debugging.
      int imod = i % 20;
      if (imod > 5) {
         auto an_object = Factory(imod);
         alive_objects.push_back(an_object);
         if (imod % 2) {
            odd_starts.push_back(an_object);
         }
         if (imod < 10) {
            low_numbers.push_back(an_object);
         }
      }

      // Increment the low numbers, then remove them if they get too big.
      auto obj = low_numbers.begin();
      while ( obj != low_numbers.end() ) {
         (*obj)->something++;
         if ((*obj)->something > 20) {
            obj = low_numbers.erase(obj);
         }
         else { obj++; }
      }

      // Clear the numbers that started out odd at the end of each loop.
      if (imod == 0)
      {
         odd_starts.clear();
      }
      i++;
   }
}

BOOST_AUTO_TEST_CASE(SmartPointer) {
   Executive();
}
