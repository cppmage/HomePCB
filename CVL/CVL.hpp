#ifndef __CVL__
	#define __CVL__
		#include "vsort.hpp"
		#include <boost/filesystem/operations.hpp>

		#include <fstream>
		#include <iostream>
		#include <string>
		#include <vector>

		#include <iterator>
		#include <algorithm>
	
		//vvs_t = vector <vector <string>>	declarated in vsort heandler
	
		using dirit_t = boost::filesystem::directory_iterator;
		using std::cout;
		using std::cin;
		using std::endl;

		void FilesWork( const std::string& ,const std::string& );
		void VectorSort(vvs_t &);
	
#endif
