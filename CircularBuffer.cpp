// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/circular_buffer.hpp>
using namespace boost;

void CircularBuffer(){
   circular_buffer<int> cb(3);

   cb.push_back(1);
   cb.push_back(2);
   cb.push_back(3);
   // 1 == cb[0] == cb.front()
   // 3 == cb[2] == cb.back()

   cb.push_back(4);
   // 4 == cb[0] == cb.back()
   // 2 == cb[1] == cb.front()
   
   cb.pop_front();
   // 3 == cb[2] == cb.front()

   cb.pop_back();
   // 3 == cb[2] == cb.front() == cb.back()
}

BOOST_AUTO_TEST_CASE(Circular) {
   CircularBuffer();
}