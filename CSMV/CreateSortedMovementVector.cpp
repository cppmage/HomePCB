#include "csmv.hpp"

int main(int argc,char** argv){
		
	try{
		var_map_t vm = ParseCommandLine(argc,argv);

		if(argc == 1 ) ConvertSMV( "./", "./" );
		else if(argc == 2 ) {
			//Use path parameters only in command line 
			if (vm.count("path"))
				ConvertSMV( vm["path"].as<std::string>(), "./" );
			//Use out directory parameter only in command line
			else if (vm.count("out"))
				ConvertSMV( "./" , vm["out"].as<std::string>() );
			//By default
			else ConvertSMV( argv[1], "./" );
		}
		else if(argc == 3 ) {
			//Use path and out parameters
			if(vm.count("path") && vm.count("out") )
				ConvertSMV( vm["path"].as<std::string>() , vm["out"].as<std::string>() );
			//Use input and output arguments in command line
			else
				ConvertSMV( argv[1], argv[2] );
		}
		//Other  
		else throw std::string {"Input parameters are unindentifited."};
	}
	catch( const std::exception &ex ){
		std::cout << "Program down..." << std::endl << "[ Error ]: " << ex.what() << std::endl;
		return 0;
	}
	catch( const std::string& excstr ){
		std::cout << "Program down..." << std::endl << "[ Error ]: "<< excstr << std::endl;	
		return 0;
	}
	return 0;
}
	
	
