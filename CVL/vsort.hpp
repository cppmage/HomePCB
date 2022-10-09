#ifndef __vsort__
	#define __vsort__
		#include <iostream>
		#include <vector>
		#include <string>
		
		#include <functional>
		#include <iterator>
		#include <algorithm>

		//conteiners declarations
		using std::string;
		using std::vector;
		
		//type_declarations
		using vs_t = std::vector <string>;	
		using vvs_t = std::vector <vs_t>;
		using vs_iterator = vs_t::iterator;
		using pss_t = std::pair <size_t,std::string>;	
		using vpss_t = std::vector <pss_t>;	
	
		vpss_t StartPositionFinder(vs_iterator& ,vs_iterator& );
	 	/*  * This function finding start positions in range first and last iterators of unsorted string vector of move positions ,
		    * then counting all points in moving , sorting them and return . 
		    
		    @ __firstparam -> reference on begin iterator in string vector  	
	 	    @ __secondparam -> reference on end iteraor in string vector
		    @ Return sorted vector of pairs of points counter and startposition
	 	*/

		vs_t LinesVectorCreate ( vs_iterator& ,vs_iterator& ,vpss_t& );
		/*  * This function will create vector of move positions. This positions are present in strings coordinates.
		    * Start positions string are ends "...D2*" and shpindel should be up. If string ends "...D1*", then shpindel should be down.
		    
		    @ __firstparam -> begin iterator of vector string type. 
		    @ __secondparam -> end iterator of vector string type.
		    @ __thirdparam -> reference to vector of pair of repeat_point_counter and start point string.
		    @ Return sorted vector of move positions.
		 */

#endif
