// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/chrono.hpp>
#include <boost/date_time.hpp>
#include <thread>
#include <sstream>
using namespace boost;

BOOST_AUTO_TEST_CASE(HighPerformance) {
   auto start = chrono::steady_clock::now();

   int sum = 0;
   for (int i = 0; i < 100; i++)
   {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      sum += i;
   }

   auto stop = chrono::steady_clock::now();

   auto elapsed = chrono::nanoseconds(stop - start);
   // over serveral runs ranged from 99141021-99997786
}

std::string FormatDateTime(std::string format, posix_time::ptime dateTime);
std::string FormatDateTime(std::string format, local_time::local_date_time dateTime);

BOOST_AUTO_TEST_CASE(BiggerTimeScale) {
   auto now = chrono::system_clock::now(); // UTC 
   auto dtNow = posix_time::from_time_t(chrono::system_clock::to_time_t(now)); // Warning: 2038 bug!
   std::string isoFormat = posix_time::to_iso_string(dtNow); // "20160729T231514"
   std::string isoExtended = posix_time::to_iso_extended_string(dtNow); // "2016-07-29T23:15:14"
   std::string simpleFormat = posix_time::to_simple_string(dtNow); // "2016-Jul-29 23:15:14"

   std::string isoLike = FormatDateTime("%Y-%m-%d %H:%M:%S%F", dtNow);
   std::string other = FormatDateTime("Day of week: %A/%a/%w Month: %B/%b/%m Day of Year: %j Week of Year: %W", dtNow);
   // "Day of week: Friday/Fri/5 Month: July/Jul/07 Day of Year: 211 Week of Year: 30"

   local_time::time_zone_ptr tzUtc(new local_time::posix_time_zone("UTC-00:00:00"));
   local_time::local_date_time localNowUtc(dtNow, tzUtc);
   std::string zone = FormatDateTime("%H:%M:%S %q", localNowUtc);
   // "2016-Jul-29 23:15:14 UTC"

   local_time::time_zone_ptr tzCdt(new local_time::posix_time_zone("CDT-05:00:00"));
   std::string centralZone = FormatDateTime("%H:%M:%S %q", localNowUtc.local_time_in(tzCdt));
   // "2016-Jul-29 18:15:14 CDT"

   local_time::local_date_time nextWeek = localNowUtc + gregorian::weeks(1);
   std::string nextWeekStr = FormatDateTime("%H:%M:%S %q", nextWeek);
   // "2016-Aug-05 23:15:14 UTC"

   local_time::local_date_time lastHour = localNowUtc - posix_time::hours(1);
   std::string lastHourStr = FormatDateTime("%H:%M:%S %q", lastHour);
   // "2016-Jul-29 22:15:14 UTC"
}

std::string FormatDateTime(std::string format, posix_time::ptime dateTime) {
   posix_time::time_facet* facet = new posix_time::time_facet(format.c_str());
   std::ostringstream ss;
   ss.imbue(std::locale(ss.getloc(), facet));
   ss << dateTime;
   return ss.str();
}
std::string FormatDateTime(std::string format, local_time::local_date_time dateTime) {
   posix_time::time_facet* facet = new posix_time::time_facet(format.c_str());
   std::ostringstream ss;
   ss.imbue(std::locale(ss.getloc(), facet));
   ss << dateTime;
   return ss.str();
}
