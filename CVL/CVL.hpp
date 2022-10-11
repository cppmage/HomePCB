#ifndef __CVL__
	#define __CVL__
		#include "vsort.hpp"
		
		#include <fstream>
		#include <boost/filesystem/operations.hpp>

		#include <iostream>
		#include <string>
		#include <vector>
		
		#include <iterator>
		#include <algorithm>
	
		//vvs_t = vector <vector <string>>	declarated in vsort heandler
		//Types declaration 	
		using dirit_t = boost::filesystem::directory_iterator;
		using std::cout;
		using std::cin;
		using std::endl;

		void FilesWork( const string& );
		void VectorSort(vvs_t &);
	
#endif
