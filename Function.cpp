// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>
using namespace boost;

int simpleCalled = 0;
int callableCalled = 0;
int otherTypeCalled = 0;

void SimpleExample(int i) {
   simpleCalled++;
}
struct Callable
{
   void operator()(int) {
      callableCalled++;
   }
};
struct OtherType
{
   void SomeFcn(int) {
      otherTypeCalled++;
   }
};

void CReceiver(void(*fcn)(int)) {
   fcn(99);
}
void CPPReceiver(function<void(int)> fcn) {
   fcn(99);
}

void Function()
{
   Callable c;
   OtherType ot;

   CReceiver(SimpleExample);
   //CReceiver(c); -> ERROR not __cdecl !
   //CReceiver(bind(&OtherType::SomeFcn, &ot, _1)); -> ERROR not __cdecl !

   CPPReceiver(SimpleExample);
   CPPReceiver(c);
   CPPReceiver(bind(&OtherType::SomeFcn, &ot, _1));
}


BOOST_AUTO_TEST_CASE(Func) {
   Function();
   BOOST_CHECK_EQUAL(simpleCalled, 2);
   BOOST_CHECK_EQUAL(callableCalled, 1);
   BOOST_CHECK_EQUAL(otherTypeCalled, 1);
}