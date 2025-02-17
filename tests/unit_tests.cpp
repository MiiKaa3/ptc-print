//====================================================
//     Preprocessor directives
//====================================================
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS

//====================================================
//     Headers
//====================================================

// My headers
#include "../include/ptc/print.hpp"
#include "utils.hpp"

// Extra headers
#include <doctest/doctest.h>

// STD headers
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <complex>

// Containers for testing
#include <vector>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>

//====================================================
//     Print default constructor
//====================================================
TEST_CASE( "Testing the Print default constructor." )
 {
  CHECK_EQ( ptc::print.getEnd(), "\n" );
  CHECK_EQ( ptc::print.getSep(), " " );
 }

//====================================================
//     Print operator () overload
//====================================================
TEST_CASE( "Testing the operator () overload." )
 {  
  // General case
  SUBCASE( "General case." )
   {
    const std::string test = ptc::osout( std::cerr, "Test passes", "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // General case with different types
  SUBCASE( "General case." )
   {
    const std::string test = ptc::osout( std::cerr, "Test passes", 123, "(ignore this)", '.' );
    CHECK_EQ( test, "Test passes 123 (ignore this) . \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // General case with no args
  SUBCASE( "General case with no args." )
   {
    const std::string test = ptc::osout( std::clog );
    CHECK_EQ( test, "\n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // stdout case
  SUBCASE( "Stdout case." )
   {
    const std::string test = ptc::osout( "Test passes", "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // No arguments case
  SUBCASE( "No arguments case." )
   {
    std::streambuf* coutbuf = std::cout.rdbuf();
    ptc::savebuf sbuf( coutbuf );
    std::cout.rdbuf( &sbuf );
    ptc::print();
    std::cout.rdbuf( coutbuf );
    CHECK_EQ( sbuf.str(), "\n" );
    CHECK( sbuf.str() != "Test thisssa.\n" );
   }

  // std::ostringstream case
  SUBCASE( "std::ostringstream case." )
   {
    std::ostringstream ostr;
    ptc::print( ostr, "Test", "this." );
    CHECK_EQ( ostr.str(), "Test this.\n" );
    CHECK( ostr.str() != "Test thisssa.\n" );
   }
   
  // std::ofstream case
  SUBCASE( "std::ofstream case." )
   {
    std::ofstream file_stream_o;
    file_stream_o.open( "test.txt", std::ios::trunc );
    ptc::print( file_stream_o, "Test", "passes (ignore this)." );
    file_stream_o.close();

    char str[26];
    std::ifstream file_stream_i;
    file_stream_i.open( "test.txt" );
    file_stream_i.read( str, 26 );
    file_stream_i.close();

    CHECK_EQ( static_cast<std::string> ( str ), "Test passes (ignore this)." );
   }

  // std::fstream case
  SUBCASE( "std::fstream case." )
   {
    std::ofstream file_stream_f;
    file_stream_f.open( "test.txt", std::ios::out | std::ios::trunc );
    ptc::print( file_stream_f, "Test", "passes (ignore this)." );
    file_stream_f.close();

    char str[26];
    std::ifstream file_stream_i;
    file_stream_i.open( "test.txt" );
    file_stream_i.read( str, 26 );
    file_stream_i.close();

    CHECK_EQ( static_cast<std::string> ( str ), "Test passes (ignore this)." );
   }

  // Passing variables inside ptc::print
  SUBCASE( "Passing variables inside ptc::print." )
   {
    std::string str = "Test passes";
    const std::string test = ptc::osout( str, "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // Testing the string return overload
  SUBCASE( "String return overload" )
   {
    ptc::print.setEnd( "" );

    CHECK_EQ( ptc::print( ptc::mode::str, "Test", "this!" ), "Test this!" );
    const std::string test_string = ptc::print( ptc::mode::str, "Test", "this!" );
    CHECK_EQ( test_string, "Test this!" );
    CHECK_EQ( ptc::print( ptc::mode::str ), "" );
    CHECK_EQ( ptc::print( ptc::mode::str, "" ), "" );

    ptc::print.setEnd( "\n" );
   }

  // Testing usage of ANSI escape sequence and final reset
  SUBCASE( "Testing usage of ANSI escape sequence and final reset." )
   {
    const std::string test_a = ptc::osout( "\033[31mTesting colors", "(ignore this)." );
    CHECK_EQ( test_a, "\033[31mTesting colors (ignore this). \n\033[0m" );

    ptc::print.setEnd( "" );
    const std::string test_b = ptc::print( ptc::mode::str, "Testing", "\033[31mcolors", "(ignore this)." );
    CHECK_EQ( test_b, "Testing \033[31mcolors (ignore this).\033[0m" );
    const std::string test_c = ptc::print( ptc::mode::str, "Testing", "the \033[31mcolors", "(ignore this)." );
    CHECK_EQ( test_c, "Testing the \033[31mcolors (ignore this).\033[0m" );
    CHECK_EQ( ptc::print( ptc::mode::str, 1, "Number" ), "1 Number" );
    const std::string test_nullptr = ptc::print( ptc::mode::str, "Hey", nullptr, nullptr );
    CHECK_EQ( test_nullptr, "Hey nullptr nullptr" );
    ptc::print.setEnd( "\n" );
   }

  // Testing usage of ANSI or empty character as first argument
  SUBCASE( "Testing ANSI escape sequence or empty character as first argument." )
   {
    ptc::print.setEnd( "" );
    const std::string test_a = ptc::print( ptc::mode::str, "", "Testing empty char (ignore this)." );
    CHECK_EQ( test_a, "Testing empty char (ignore this). " ); 
    const std::string test_b = ptc::print( ptc::mode::str, "\033[31m", "Testing empty char (ignore this)." );
    CHECK_EQ( test_b, "\033[31mTesting empty char (ignore this). \033[0m" ); 
    ptc::print.setEnd( "\n" );
   }
 }

//====================================================
//     Print operator << overload
//====================================================
TEST_CASE( "Testing the Print operator << overloads." )
 {
  // Testing std::complex printing
  SUBCASE( "Testing std::complex printing." )
   {
    ptc::print.setEnd( "" );
    std::complex <int> no( 1, 6 );
    const std::string test_a = ptc::print( ptc::mode::str, no );
    CHECK_EQ( test_a, "1+6j" );
    std::complex <double> no_d( 1, 2.1 );
    const std::string test_b = ptc::print( ptc::mode::str, no_d );
    CHECK_EQ( test_b, "1+2.1j" );

    std::ostringstream ostr;
    ptc::print( ostr, no );
    CHECK_EQ( ostr.str(), "1+6j" );
    ptc::print.setEnd( "\n" );
   }

  // Testing all std containers printing
  SUBCASE( "Testing all std containers printing." )
   {
    ptc::print.setEnd( "" );

    // std::array
    //std::array <int, 3> array = { 1, 2, 3 };
    //CHECK_EQ( ptc::print( ptc::mode::str, array ), "[1, 2, 3]" );

    // std::vector
    std::vector <int> vec = { 1, 2, 3 };
    CHECK_EQ( ptc::print( ptc::mode::str, vec ), "[1, 2, 3]" );
    std::vector <int> null_v = {};
    CHECK_EQ( ptc::print( ptc::mode::str, null_v ), "[]" );

    // std::deque
    std::deque <int> deque = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, deque ), "[7, 5, 16]" );

    // std::forward_list
    std::forward_list <std::pair <int, int> > forwardListOfPairs;
    std::pair<int, int> pair1 = std::make_pair( 11, 22 );
    forwardListOfPairs.push_front( pair1 );
    std::pair<int, int> pair2 = std::make_pair( 33, 44 );
    forwardListOfPairs.push_front( pair2 );
    CHECK_EQ( ptc::print( ptc::mode::str, forwardListOfPairs ), "[[33, 44], [11, 22]]" );

    // std::list
    std::list<int> list = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, list ), "[7, 5, 16]" );

    // std::set
    std::set<int> set = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, set ), "[5, 7, 16]" );

    // std::map
    std::map <int,int> map = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
    CHECK_EQ( ptc::print( ptc::mode::str, map ), "[[1, 1], [2, 2], [3, 3]]" );

    // std::multiset
    //std::multiset <int,int> multiset;
    //multiset.insert(40);
    //multiset.insert(23);
    //multiset.insert(1);
    //CHECK_EQ( ptc::print( ptc::mode::str, multiset ), "[40, 23, 1]" );

    // std::multimap
    //std::multimap <int, int> multimap;
    //multimap.insert( std::pair <int, int> ( 1, 40 ) );
    //multimap.insert( std::pair <int, int> ( 2, 30 ) );
    //CHECK_EQ( ptc::print( ptc::mode::str, multimap ), "[40, 23, 1]" );

    // std::unordered_set
    std::unordered_set<int> u_set = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, u_set ), "[5, 16, 7]" );

    // std::unordered_map
    std::unordered_map <int,int> u_map = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
    CHECK_EQ( ptc::print( ptc::mode::str, u_map ), "[[3, 3], [2, 2], [1, 1]]" );

    // std::unordered_multiset

    // std::unordered_multimap

    // std::stack
    //std::stack <int> stack;
    //stack.push( 21 );
    //stack.push( 22 );
    //stack.push( 24 );
    //CHECK_EQ( ptc::print( ptc::mode::str, stack ), "[21, 22, 24]" );

    // std::priority_queue ?
    //std::priority_queue<int> p_queue;
    //p_queue.push( 2 );
    //p_queue.push( 5 );
    //p_queue.push( 6 );
    //CHECK_EQ( ptc::print( ptc::mode::str, p_queue ), "[2, 5, 6]" );

    ptc::print.setEnd( "\n" );
   }

  // Testing C arrays printing
  SUBCASE( "Testing C arrays printing." )
   {
    int arr[3] = { 1, 2, 3 };
    CHECK_EQ( ptc::print( ptc::mode::str, arr ), "[1, 2, 3]\n" );
   }

  // Testing nested std containers printing
  SUBCASE( "Testing nested std containers printing." )
   {
    std::vector <std::vector <int>> vec = { { 1, 3 }, { 2, 1 } };
    CHECK_EQ( ptc::print( ptc::mode::str, vec ), "[[1, 3], [2, 1]]\n" );
   }
 }

//====================================================
//     Print setEnd and getEnd
//====================================================
TEST_CASE( "Testing the Print setEnd and getEnd methods." )
 {
  ptc::print.setEnd( '.' );
  CHECK_EQ( ptc::print.getEnd(), "." );
  
  std::streambuf* cerrbuf = std::cerr.rdbuf();
  ptc::savebuf sbuf( cerrbuf );
  std::cerr.rdbuf( &sbuf );
  ptc::print( std::cerr, "Test passes (ignore this)." );
  std::cerr.rdbuf( cerrbuf );
  CHECK_EQ( sbuf.str(), "Test passes (ignore this).." );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setEnd( "\n" );
  ptc::print( "\n" );
 }

//====================================================
//     Print setSep and getSep
//====================================================
TEST_CASE( "Testing the Print setSep and getSep methods." )
 {
  ptc::print.setSep( "*" );
  CHECK_EQ( ptc::print.getSep(), "*" );

  std::streambuf* coutbuf = std::cout.rdbuf();
  ptc::savebuf sbuf( coutbuf );
  std::cout.rdbuf( &sbuf );
  ptc::print( "Test", "passes", "(ignore this)." );
  std::cout.rdbuf( coutbuf );
  CHECK_EQ( sbuf.str(), "Test*passes*(ignore this).\n" );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setSep( " " );
 }

//====================================================
//     Print setFlush and getFlush
//====================================================
TEST_CASE( "Testing the Print setFlush and getFlush methods." )
 {
  ptc::print.setFlush( true );
  CHECK_EQ( ptc::print.getFlush(), true );

  std::streambuf* coutbuf = std::cout.rdbuf();
  ptc::savebuf sbuf( coutbuf );
  std::cout.rdbuf( &sbuf );
  ptc::print( "Test", "passes", "(ignore this)." );
  std::cout.rdbuf( coutbuf );
  CHECK_EQ( sbuf.str(), "Test passes (ignore this).\n" );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setFlush( false );
 }