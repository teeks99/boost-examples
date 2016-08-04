Boost 

Modern C++ Libraries

What is Boost?
==============

*   A _large_ collection of C++ libraries
    *   Diverse topics
    *   147 libraries and tools
    *   Minimal interdependencies (only use what you want)
    *   Cross-platform, many supported compilers
*   An incubator for C++ Standard Library
    *   10+ library contributions for C++11/14
    *   Several more for C++17
    *   Provides backwards compatibility for compilers not supporting C++11/14/17
*   An incubator for new C++ libraries
    *   [Boost Library Incubator](http://blincubator.com/)
    
Library Categories
==================

*   String and Text Processing
*   Containers
*   Iterators
*   Algorithms
*   Function Objects
*   Generic Programming
*   Template Metaprogramming
*   Preprocessor Metaprogramming
*   Concurrent Programming
*   Math and Numerics
*   Correctness and Testing
*   Data Structures
*   Time/Units
*   Image Processing
*   Input/Output
*   Inter-Language Support
*   Language Features Emulation
*   Memory
*   Parsing
*   Patterns
*   State Machines
*   System
*   Tools

Most of these categories have >10 individual libraries under them.

A Handful of Libraries
======================

*   Smart Pointers
*   Test
*   Program Options
*   Thread
*   Lexical Cast
*   Circular Buffer
*   Tokenizer
*   String Algorithms
*   Function/Bind
*   ASIO
*   Filesystem
*   Endian
*   Chrono/DateTime
*   Math
*   Python
*   Regex
*   Iostreams

Smart Pointers
==============

*   **`shared_ptr<T>`** - Automatically reference counted, destroyed when the last instance passes out of scope. (Implemented in C++11: VS2010+, GCC 4.7+)
*   **`weak_ptr<T>`** - Keep a pointer to an object owned by a `shared_ptr`, but don’t increase the reference count. 
*   **`scoped_ptr<T>`** - Keeps an object for the lifetime of the scope, destroys it when passing out of scope. (Similar to C++11 `unique_ptr` without move-ability)

Example:

    #include <boost/smart_ptr.hpp>
    using namespace boost;

    struct MyType { int something; };
    shared_ptr<MyType> Factory(int value) {
       auto an_object = shared_ptr<MyType>(new MyType);
       an_object->something = value;
       return an_object;
    }

    void TopLevel(){
       auto an_object = Factory(3);
       // .. do other things with an_object
       // destroyed when all users are out of scope
    }

Test
====

*   A complete unit-testing framework
*   Make test suites composed of other suites and test cases
*   Basic test cases, fixture test cases, parameter test cases
*   Comparison Assertions
    *   `BOOST_CHECK_EQUAL(a,b);`
    *   `BOOST_CHECK_CLOSE(a, b, tolerance);` (for floating point)
    *   `BOOST_CHECK_THROW(expression, function);`
*   Includes an executive for running the tests

Program Options
===============

*   Pass startup options to a program
*   Command Line
    *   -o, --option, -oValue, --option value, --option=value
    *   Optional and required
    *   Positional arguments without flags 
    *   Autogenerates –help output
    *   Combine multiple instances in a vector
*   Environmental Variable Storage
*   Config File (INI-like syntax)
    *   option = value
    *   Sections (provides `section.option`)

            [section]
            option = value
            
Thread
======

*   Cross Platform Thread Library
*   Create threads from callables
    *   Function Pointers
    *   Function Objects
    *   Objects with operator()
*   C++ 11 plus extensions 
*   Thread Local Storage
*   Synchronization 
    *   Mutex (many flavors)
    *   Scoped `lock_guard`
    *   Barriers
    *   Futures
    *   Many more
    
Lexical Cast
============

*   Convert Strings and Numbers
*   Avoid pitfalls of C (atoi, atof)
*   Much simpler than << with stringstream for number -> string, more secure than sprintf.

Example:

    #include <boost/lexical_cast.hpp>
    using namespace boost;

    void LexicalCast()
    {
       short val1 = lexical_cast<short>("12345");
       double val2 = lexical_cast<double>("1.23e4");
       std::string val3 = lexical_cast<std::string>(12345);
       std::string val4 = lexical_cast<std::string>(1.23e4);

       std::string embedded = "cut me 123";
       int val5 = lexical_cast<int>(embedded.data() + 7, 3);
    }

Circular Buffer
===============

*   Simple Data Structure
*   Specify the maximum size
*   Add values
    *   Overwrite if buffer is full
    
Example:

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

Tokenizer
=========

*   Splits a string into tokens
    *   Words from a sentence
    *   Values from a CSV line
    
Example:

    std::string input = "This is a test-ish line";
    tokenizer<> tokens(input);
    std::string output = "";
    for (auto t = tokens.begin(); t != tokens.end(); t++) {
        output += *t + "_";
    }
    // output == "This_is_a_test_ish_line_"

String Algorithms
=================

*   Change Case
*   Trim Space
*   String contains another
*   Find a substring
*   Replace/Erase substring
*   Split
*   Join
*   ...More
*   The [quick-reference page](http://www.boost.org/doc/libs/1_61_0/doc/html/string_algo/quickref.html) has a great list

Function/Bind
=============
*   Function - Replacement for C-style function pointers
*   Compatible with
    *   C-Style function pointer
    *   C++ Function Object (Callable)
    *   Bind’ed member functions
*   Bind – allows a member function to be called like a free function
*   Both have corresponding elements in C++11, but the syntax differs.

ASIO
====
*   Asynchronous (or Synchronous) Input/Output
    *   Cross Platform
*   Net: TCP, UDP, ICMP
*   Serial Port
*   Timers
*   Signals
*   Unix Specific: Sockets, File Descriptors
*   Windows Specific: Stream, Random, Object Handles

Filesystem
==========
*   Work with the files/directories accessible to the system
    *   Will be in C++17
*   Paths – create to any file directory
    *   Absolute or relative
    *   Get parts of path (root, stem, extension, etc)
    *   Determineermin if path is file, directory, or link
*   File status: permissions, size, read/write times
*   Manipulate
    *   Create (dirs), copy, rename, remove
*   Symlinks/hardlinks (if supported)
*   Iterate directory contents (recursive option)

Endian
======
*   Convert between big and little
*   Automatically detects native order
*   Functions for conversion
    *   native_to_big(value), big_to_native(value)
*   Data types for local storage
    *   E.g. use big_int32_t my_val = 0x01020304; to store as 0x04030201 in memory, on a little endian machine

Chrono/DateTime
===============
*   Chrono matches C++11’s Chrono (VS 2012, GCC 4.7) 
    *   Clock, TimePoint, Duration
    *   System Clock or Steady Clock (replaces QueryPerformanceCounter)
    *   Includes some process/thread clocks not in C++11
*   DateTime - Some overlap with Chrono, many more features
    *   More POSIX compliant (100% windows compatible)
    *   Timezones - uses tzdata
    *   Calendars
    *   Serialization/Deserialization of dates and times 

Math
====

*   **Lots of Math functionality!**
*   Statistics
*   Geometry
*   Linear Algebra (uBLAS)
*   Multiprecision
*   Quaternian/Octernian
*   Ordinary Differential Equations

Python
======

*   Interface to the Python Programming Language
*   C++ calls Python
*   Python calls C++
*   Wrap C++ classes into python objects
    *   Specify an interface definition for each module/class

Regex
=====

*   Create regex objects
*   Match
*   Replace 
*   Search
*   Perl (default), POSIX basic, and POSIX extended are all supported syntaxes
*   Sed, Perl, and Boost-Extended replace formats

Iostreams
=========

*   Make pipelines to flow IO
*   Sources, Input Filters, Output Filters, Sinks
*   Combine multiple filters/sources/sinks
*   Files, arrays, network streams, zlib/gzip/bzip2
*   Hook to your own (e.g. TLS)

Example

    io::filtering_ostream out;
    out.push(compressor());
    out.push(base64_encoder());
    out.push(file_sink("my_file.txt"));
    // write to out using std::ostream interface

Links
=====

*   [Boost Site](http://www.boost.org)
*   [Boost Book](http://theboostcpplibraries.com/)
*   [Good Boost Test Tutorial](https://legalizeadulthood.wordpress.com/2009/07/04/c-unit-tests-with-boost-test-part-1/)

