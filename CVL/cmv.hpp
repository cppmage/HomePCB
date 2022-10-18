#ifndef __CVL__
	#define __CVL__
		#include <boost/filesystem/operations.hpp>
		#include <boost/program_options.hpp>
		#include <fstream>
		#include <ncurses.h>
		#include <filesystem>
		#include "vsort.hpp"
		//Inside vsort.hpp declare:
		//<iostream>,<iterators>,<string>,<vector> and using some types declarations
		
		//Types declaration 	
		using dir_entry_t = boost::filesystem::directory_entry;
		using dir_iter_t = boost::filesystem::directory_iterator;
		using std::cout;
		using std::cin;
		using std::endl;

		namespace opt=boost::program_options;
		namespace bfs=boost::filesystem;



		//void FilesWork( const string& );
		void FilesWork( const string& , const string& );
		void VectorSort(vvs_t &);
	
#endif
