#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <bitset>
#include <cerrno>
#include <cstring>

#include "huff_n_write3.h"
#include "huff_n_write.h"
//#include "huff_n_write.hpp"

template <typename V, typename K>
void showme( const std::map<V, K>& els ) {
   std::cout << "Alphabet Table:\n";
   for( auto el = els.begin(); el != els.end(); el++ )
      std::cout << el->first << ": " << el->second << "\n";
}

int main( int argc, char** argv ) {

   using tallies = int;
   using mysym_t = wchar_t;

   if( !(argc > 1) ) {
      std::cout << "dummy_prog: please provide a filename as argument\n";
      return 0;
   }
   std::basic_ifstream<mysym_t> instream_kun {argv[1]};

   if( !instream_kun.is_open() ) {
      std::cout << "dummy_prog: file using this argument does not exist. Perhaps a typo? Terminate.\n";
      return 0;
   }



   //char n;

   std::basic_ostringstream<char32_t> sstream_kun{std::ios::binary};
   std::basic_ofstream<char32_t> fstream_kun{"test_comp_file.sp", std::ofstream::binary };

   huff_n_write<mysym_t, char32_t> myhuffler { /*s*/fstream_kun };

   myhuffler.tally_up( instream_kun );

   instream_kun.clear();
   instream_kun.seekg(0, instream_kun.beg );

   if( instream_kun.eof() )
      std::cout << "EOF???\n";
   else if( instream_kun.fail() )
      std::cout << "Fail state\n";
   else if( instream_kun.good() )
      std::cout << "Good state\n";
   else
      std::cout << "...\n";

   //char n = 'a';
   mysym_t n;
   //myhuffler.print2strm( n );

   int k = 0;
   int j = 0;
#if 1
   while( instream_kun.get(n) ) {
      ++k;
      myhuffler.print2strm( n );
   }
   myhuffler.print2strm( 0b100000000 );
#endif
   myhuffler.flush();

#if 0
   std::basic_string<char32_t> result = sstream_kun.str();
   std::basic_ofstream<char32_t> fileoutput {"fudrukkers.sp", std::ofstream::binary | std::ofstream::out};
   if( !fileoutput.is_open() )
      std::cout << "Not open!\n";
   if( fileoutput.bad() )
      std::cout << "Bad state " << result.size() << "\n";
   if( fileoutput.fail() )
      std::cout << "Fail state\n";

   fileoutput.write( result.data(), result.size() );
   std::cout << errno << '\n';
   if( fileoutput.bad() )
      std::cout << "Bad state 02 " << result.size() << "\n";
   if( fileoutput.fail() )
      std::cout << "Failed operation 02\n";
   fileoutput.flush();
   fileoutput.close();
#endif

   //std::basic_istringstream<char32_t> isstream_kun{result, std::ios::binary};

   
#if 0
   std::cout << "CONTENTS" << result.size() << "\n";
   int i = 0;
   for( auto sym_it = result.begin(); sym_it != result.end(); sym_it++ )
      std::cout << "sstream_kun[" << i++ << "] has value '" << std::bitset<32>(*sym_it) <<"'\n";
#endif
   //std::cout << sstream_kun.str() << "\n";
   //myhuffler.huff_spawna_tree( isstream_kun );

   //myhuffler.huff_decode( isstream_kun );

   std::cout << "Terminate in peace!\n";

   instream_kun.close();
   fstream_kun.close();

}