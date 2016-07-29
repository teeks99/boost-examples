// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/endian/conversion.hpp>
#include <boost/endian/arithmetic.hpp>
using namespace boost::endian;

BOOST_AUTO_TEST_CASE(Endian) {
   // Examples run on a little endian machine

   // Read from [disk, network]
   int a_be = 0x01020304;
   
   // convert to local
   int a_le = big_to_native(a_be); // 0x04030201

   // manual conversion
   bool on_le = order::little == order::native; // true
   int a_le2 = endian_reverse(a_be); // 0x04030201

   // Create local
   int b_le = 0x05060708;

   // Create value to write to disk/network
   int b_be = native_to_big(b_le); // 0x08070605



   struct MixedData
   {
      big_int32_t a;
      big_int32_t b;
      little_int32_t c;
      little_int32_t d;
   };

   MixedData m;
   m.a = 0x01020304;
   m.b = 0x00000010;
   m.c = 0x00000010;
   m.d = 0x01020304;

   uint32_t* chunks = reinterpret_cast<uint32_t*>(&m);
   // chunks in memory: { 0x04030201 0x10000000 0x00000010 0x01020304 }
}