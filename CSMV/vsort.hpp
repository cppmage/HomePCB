#ifndef __vsort__
/*
	"vsort.cpp" and "vsort.hpp" files is designed to sort string vectors into a string vector of successive tool movement points only.

   	This header file describes a simple search for the initial position points of the spindle movement using the " StartPositionFinder " function,
	which also fetches the maximum number of tool position points and then sorts the vector of initial position points from the smallest to the largest
	number of incoming sequential movement points. This function returns a sorted string vector of points from which the tool movement starts.

	Using the " LinesVectorCreate " function, it is possible to create a vector of consecutive points from the start to the end of the tool movement. 
	For this reason, iterators of the start and end of the vector of position points of movement and a vector of start position points are used as input.
	This function writes a sequence of points of movement of the tool from start to end with a check for the coincidence of the coordinates of the beginning and end of
	the movement into a string vector and returns it as a result.	
 
 */
	#define __vsort__
		#include <vector>
		#include <string>
		#include <iterator>
		#include <algorithm>

		using vs_t = std::vector <std::string>;	
		using vvs_t = std::vector <vs_t>;
		using vs_iterator = vs_t::iterator;
		using pss_t = std::pair <size_t, std::string>;	
		using vpss_t = std::vector <pss_t>;	
	
		vpss_t StartPositionFinder(vs_iterator& ,vs_iterator& );
	 	/*  * This function finding start positions in range first and last iterators of unsorted string vector of move positions ,
		    * then counting all points in moving , sorting them and return . 
		    
		    @ firstparam -> reference at begin iterator in string vector  	
	 	    @ secondparam -> reference at end iteraor in string vector
		    @ Return sorted vector of pairs of points counter and startposition
	 	*/

		vs_t LinesVectorCreate ( vs_iterator& ,vs_iterator& ,vpss_t& );
		/*  * This function will create vector of move positions. This positions are present in strings coordinates.
		    * Start positions string are ends "...D2*" and shpindel should be up. If string ends "...D1*", then shpindel should be down.
		    
		    @ firstparam -> reference at begin iterator in vector string . 
		    @ secondparam -> reference at end iterator in vector string .
		    @ thirdparam -> reference at vector of pair of repeat_point_counter and start point string.
		    @ Return sorted vector of move positions.
		 */

#endif
