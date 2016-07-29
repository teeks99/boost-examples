// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include <fstream>
#include <list>

BOOST_AUTO_TEST_CASE(Filesystem) {
   std::string testFileName = "test_file.tmp";
   std::ofstream testFile(testFileName);
   testFile << "Some data in here" << std::endl;
   testFile.close();

   auto size = file_size(testFileName);
   // size == 19

   path newDir("dir1");
   path subDir = newDir / path("dir2");
   create_directories(subDir);

   path testFilePath(testFileName);
   std::string fstem = testFilePath.stem().string(); // test_file
   std::string fext = testFilePath.extension().string(); // .tmp

   path secondTestPath = subDir / testFilePath;
   copy(testFilePath, secondTestPath);
   bool regular_exists = is_regular_file(secondTestPath); // true
   bool relative = secondTestPath.is_relative(); // true

   path current = current_path();
   bool absolute = current.is_absolute(); // true

   path combined = current / secondTestPath;
   bool combined_absolute = combined.is_absolute(); // true
   bool combined_complete = combined.is_complete(); // true

   std::list<path> paths;
   recursive_directory_iterator diritem(newDir), end;
   while (diritem != end) {
      paths.push_back(diritem->path());
      ++diritem;
   }
   // paths = { dir1/dir2, dir1/dir2/test_file.tmp }

   auto removed = remove_all(newDir);
   remove(testFileName);
}
