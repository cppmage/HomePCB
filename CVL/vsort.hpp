#ifndef __vsort__
	#define __vsort__
		#include <iostream>
		#include <vector>
		#include <functional>
		#include <string>
		#include <iterator>
		#include <algorithm>

		//using namespace std;
		using std::string;
		using std::vector;

		using vs_t = std::vector <string>;	
		using vvs_t = std::vector <vs_t>;
		using vs_iterator = vs_t::iterator;
		using pss_t = std::pair <size_t,std::string>;	
		using vpss_t = std::vector <pss_t>;	
	
		vpss_t StartPositionFinder(vs_iterator& ,vs_iterator& );
	 	/*  * This function find start positions in range of first and last iterators in string vector.After sorting and return them. 
			* From "CVL/vsort.hpp" 	
			* firstit -> fist iterator in string vector  	
	 		* lastit -> lastnext iteraor in string vector
			* Return sort vector pair of points counter in lines and startposition
	 	*/

		vs_t LinesVectorCreate ( vs_iterator& ,vs_iterator& ,vpss_t& );
#endif
