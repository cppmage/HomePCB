/************************************************************************************** 
 * The header file is part of the "HomePCB" project. The task of the project subroutine 
 * is to convert the input file created in the "KiCad" program with the extension "gbr"
 * into a file of sorted sequential displacement points milling tool.
 *
 * The subroutine contains the logic of collecting and processing the input file and 
 * sorting the data with writing it at the output to a file with the same name and 
 * extension "smv". path" and "--out", which are described in the help material 
 * of the program.
 *------------------------------------------------------------------------------------
 * Program operating modes:
 * Using: csmv 
 *  1)If the user has not specified any input data, then by default the program 
 *  searches for files with the extension "gbr" in the directory where the program 
 *  is located and the result will be written to a file with the same name, extension
 *  "smv" in the same directory.
 *
 * Using: csmv --path=PathToFile/filename.gbr or /PathToFile/filename.gbr 
 *  2)If the user only specified a relative or full path to the file as input, then 
 *  the program will by default consider the location of the program as the output 
 *  directory, create a file there with the same name and extension "smv" and write 
 *  the result to this file.
 * 
 * Using: csmv --out==/OutDirectoryPath/ 
 *  3)If the user only "--out=/OutDirectoryPath/", then the program will search in 
 *  local directory for files with the extension "gbr" and, with the consent of the
 *  user, will convert them. The result of the work will be written to a file with 
 *  the same name as the input file with the extension "smv" to the directory where 
 *  the default program is located.
 *
 * Using: csmv /PathToFile/filename.gbr /OutDirectoryPath/ or 
 *        csmv --path=/PathToFile/filename.gbr --out=/OutDirectoryPath/
 *  4)If you explicitly specify the path to the input file and the output directory 
 *  where the result of the work will be written, the program will do it. Similarly,
 *  using the input parameters.
 *------------------------------------------------------------------------------------
 * Markings:
 *  X_Y_D02* -> start of movement of successive directional movement points with 
 *  tool raised and rapid movement.
 *  X_Y_D01* -> subsequent tool movement with the tool down.
 ************************************************************************************/


#ifndef __CVL__
	#define __CVL__

	#include <iostream>
	#include <fstream>

	#include <boost/filesystem/operations.hpp>
	#include <boost/program_options.hpp>

	using dir_entry_t = boost::filesystem::directory_entry;
	using dir_iter_t = boost::filesystem::directory_iterator;
	using var_map_t = boost::program_options::variables_map;
	
	/* This main function is designed to convert a file with 
	 * the "gbr" extension into a file containing sorted ordered
	 * displacement points with the "smv" extension. The function
	 * contains inside the check for the existence of paths and 
	 * directories of input and output data for different modes 
	 * of operation, the logic for creating and sorting the vector
	 * tool movement data.
	 *
	 * @firststring -> input data, where is program works with "gbr" files.
	 * @secondstring -> output data, there are program input file with result of program work.
	 *
	 * Output file have a "smv" extention.("Sorted Movement Vector")
	 * */
	void ConvertSMV( const std::string& , const std::string& );
	
	/* This function is designed to collect and process data from 
	 * the command line */
	var_map_t ParseCommandLine( int& , char** );
#endif
