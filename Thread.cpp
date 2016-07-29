// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

// If you want to seamlessly upgrade to C++11 smart pointers, you can do
// something like this for includes:

// #if _MSC_VER < 1700 // Visual Studio 2012+
//  #include <boost/thread.hpp>
//  using namespace boost;
// #else
//  #include <thread>
//  using namespace std;
// #endif

#include <boost/thread.hpp>
#include <boost/chrono.hpp> // For sleep
using namespace boost;

mutex global_mutex;
int val = 0;

class CallableExample {
public:
   void operator()(){
      for (int i = 0; i < maxValue; i++) {
         lock_guard<mutex> global(global_mutex);
         val += i;
         boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
      }
   }
   int maxValue;
};

void FunctionExample(){
   for (int i = 0; i < 50; i++) {
      lock_guard<mutex> global(global_mutex);
      val += i;
      boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
   }
}

void RunSome()
{
   CallableExample callable;
   callable.maxValue = 30;

   thread t1(callable);
   thread t2(FunctionExample);

   t1.join();
   t2.join();
}

BOOST_AUTO_TEST_CASE(threads) {
   RunSome();
}