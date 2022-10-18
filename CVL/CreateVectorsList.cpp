#include "cmv.hpp"
//--path=...
//--mkdir=...
//--out=...

int main(int argc,char** argv){
	opt::options_description main_desc ("All options");
	main_desc.add_options()
		("path",opt::value <string>(),"")
		("mkdir",opt::value <string>(),"")
		("out",opt::value <string>(),"")
		("help",opt::value <string>(),"");


	try{
		if(argc == 1 ) FilesWork( "./", "./" );
		else if(argc == 2 ) FilesWork( argv[1], "../" );
		else if(argc == 3 ) FilesWork( argv[1], argv[2] );
		else throw string {"Input parametres are unindentifited."};
	}
	catch( const std::exception &ex ){
		cout << "Program down..." << endl << "[ Error ]: " << ex.what() << endl;
		exit(0);
	}
	catch( const string& excstr ){
		cout << "Program down..." << endl << "[ Error ]: "<< excstr << endl;	
		exit(0);
	}
	return 0;
}
	
	
