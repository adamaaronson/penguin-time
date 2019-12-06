#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

/*
 * DO NOT PUT YOUR TESTS IN THIS FILE UNLESS YOU LIKE LONG COMPILE TIMES!
 * ======================================================================
 *
 * When this file is compiled it will compile ALL of Catch2, which is quite
 * slow. Given that the compiler will recompile any files that change between
 * compilations, we want this file to NEVER CHANGE so that it only gets
 * compiled once (and all subsequent compilations will be speedy!)
 *
 * Keep all of your test cases in other `.cpp` files. You only need to
 * `#include "catch.hpp"` and then you can write your TEST_CASEs
 * and REQUIREs as usual.
 *
 * Testing compilation notes:
 * 1. Add any test .cpp files to the test/CMakeLists.txt if CLion doesn't do it
 * 2. Add any src .cpp files that you need to the test/CMakeLists.txt if CLion
 *    doesn't do it, so that your testing executable has what it needs
 *    to compile
 * 3. We've set up the test executable so it can use any headers in src/, but if
 *    you make a different (sub)folder that has header files, you should
 *    add that folder as well to the CMakeLists.txt if you need to #include
 *    those header files in your test files
 */
