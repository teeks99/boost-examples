// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>

void OptionsProgram(int argc, char* argv[]) {
   po::options_description desc;
   desc.add_options()
      ("help", "show help message")
      ("first,f", po::value<int>(), "first option")
      ("second,s", po::bool_switch()->default_value(false), "second option")
      ("third,t", po::value<std::string>()->default_value("Hello World"), "third option")
      ("fourth", po::value<std::vector<std::string>>(), "fourth option")
      ;
   po::positional_options_description positional;
   positional.add("fourth", -1);

   po::variables_map results;

   store(po::command_line_parser(argc, argv).options(desc).
      positional(positional).run(), results);

   // Config File
   // ifstream cfg_file("my_config.cfg");
   // store(po::parse_config_file(cfg_file, desc), results);

   // Environmental variables 
   // Needs a "Name Mapper" function that will take in the env variable name
   // and return the description name if we want to use that env variable or
   // a blank string if we don't want to use that env variable
   // store(po::parse_environment(desc, name_mapper_pointer), results);

   std::cout << "Program Options Example" << std::endl;
   if (results.count("help")) {
      std::cout << desc << std::endl;
      return;
   }

   // Use the values added in
   if (results.count("first")) {
      std::cout << "First: " << results["first"].as<int>() << std::endl;
   }
   std::cout << "Second: ";
   if (results["second"].as<bool>()) { std::cout << "true\n"; }
   else { std::cout << "false\n"; }
   std::cout << "Third: " << results["third"].as<std::string>() << std::endl;
   if (results.count("fourth")) {
      auto fourth = results["fourth"].as<std::vector<std::string>>();
      std::cout << "Fourth: ";
      for (auto item = fourth.begin(); item != fourth.end(); item++) {
         std::cout << *item << " ";
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(Help) {
   char* argv[2] = { "", "--help" };
   OptionsProgram(2, argv);

   /* output

   Program Options Example
   --help                            show help message
   - f[--first] arg                first option
   - s[--second]                   second option
   - t[--third] arg(= Hello World) third option
   --fourth arg                      fourth option

   */
}

BOOST_AUTO_TEST_CASE(basics) {
   char* argv[3] = { "", "-s", "--first=8" };
   OptionsProgram(3, argv);

   /* output

   Program Options Example
   First : 8
   Second : true
   Third : Hello World

   */
}

BOOST_AUTO_TEST_CASE(multiple) {
   char* argv[4] = { "", "--fourth=Something", "--fourth=Else", "--fourth=Funny" };
   OptionsProgram(4, argv);

   /* output

   Program Options Example
   Second : false
   Third : Hello World
   Fourth : Something Else Funny
 
   */
}


BOOST_AUTO_TEST_CASE(positional) {
   char* argv[5] = { "", "-s", "--fourth=Something", "Else", "Funny" };
   OptionsProgram(5, argv);

   /* output

   Program Options Example
   Second : true
   Third : Hello World
   Fourth : Something Else Funny

   */
}
