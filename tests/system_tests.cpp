//====================================================
//     headers
//====================================================

// My headers
#include "../include/ptc/print.hpp"

// STD headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <complex>
#include <vector>
#include <map>

//====================================================
//     standard
//====================================================
void standard()
 {
  // Print with stdout
  ptc::print( "Print", "with", "stdout." );

  // Print a new line
  ptc::print();

  // Print with stderr (or other ostream objects)
  ptc::print( std::cerr, "Print", "with", "stderr." );
  ptc::print( std::cerr );

  // Print by changing the "end" variable value (and/or type)
  ptc::print.setEnd( '.' );
  ptc::print( "Test" );
  ptc::print();
  ptc::print.setEnd( "\n" );
  ptc::print( "\n" );

  // Print by changing the "sep" variable value (and/or type)
  ptc::print.setSep( '*' );
  ptc::print( "", "Test", "the", "new", "sep." );
  ptc::print();
  ptc::print.setSep( " " );

  // Print ostringstream
  std::ostringstream strout;
  ptc::print( strout, "I am an", "std::ostringstream object!" );
  ptc::print( strout.str() );

  // Printing on a file with ostream
  std::ofstream file_stream_o( "test.txt", std::ios::trunc );
  ptc::print( file_stream_o, "You can also write in a file! ", 1, 2, 3, 4.5, 7 );
  file_stream_o.close();

  // Printing on a file with fstream
  std::fstream file_stream_f( "test.txt", std::ios::out | std::ios::trunc );
  ptc::print( file_stream_f, "You can also write in a file! ", 1, 2, 3, 4.5, 7 );
  file_stream_f.close();
  ptc::print( "Text has been wrote to", "test.txt", "file!" );

  // Printing with std::flush
  ptc::print.setFlush( true );
  ptc::print( "Printing", "with std::flush on." );
  ptc::print.setFlush( false );

  // Passing variables into print
  std::string var = "This var";
  ptc::print( var, "is printed." );

  // Printing colored output
  ptc::print( "\033[31m", "Red string!");
  ptc::print( "\033[31mAnother", "red string!");
  ptc::print( "This is", "a \033[34mblue string!", "yeah!");

  // Printing with a number as first argument
  ptc::print( 1, 2, "numbers as first arguments." );

  // Using the str method
  ptc::print.setEnd( "" );
  std::string str_out_a = ptc::print( ptc::mode::str, "This", "is a string!\n" );
  std::cout << str_out_a;
  std::string str_out_b = ptc::print( ptc::mode::str, "Also this one" );
  ptc::print( str_out_b );
  ptc::print.setEnd( "\n" );

  // Testing usage of "nullptr" as argument
  ptc::print( "\nTesting", nullptr, nullptr );

  // Testing usage of other std::ostream objects
  //ptc::print( std::wcout, "Testing std::wcout!" ); // ERROR
 }

//====================================================
//     other_types
//====================================================
void other_types()
 {
  // Testing std::complex printing
  std::complex<int> cmplx_no( 2, 3 );
  std::cout << "Normal complex number printing: " << cmplx_no << "\n";
  ptc::print( "ptc::print complex number printing:", cmplx_no );

  std::complex<double> cmplx_no_d( 2.1, 3.6 );
  ptc::print( "ptc::print complex number printing:", cmplx_no_d );

  // Other containers printing
  std::vector <int> vec = { 1, 2, 3 };
  ptc::print( "Printing an std::vector:", vec );

  std::map <int,int> map = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
  ptc::print( "Printing an std::map:", map );
 }

//====================================================
//     main
//====================================================
int main()
 {
  standard();
  other_types();
 }