#include "csmv.hpp"
#include "vsort.hpp"
#include <boost/program_options.hpp>

namespace bfs=boost::filesystem;
namespace opt=boost::program_options;

void inline VectorSort(vvs_t& vvs){
	for(auto& lv : vvs){
		//scip string about aperture
		auto firstit=lv.begin()+1;

		auto lastit=find_if(firstit,lv.end(),[](std::string &str){return str=="G75*";});
			//If circle founted ,then return to circle start movement position
			if(lastit != lv.end()) --lastit;
			// Return_sorted_vector_of_pair <repeat_counter, start_positions> 
			vpss_t pcounter = StartPositionFinder(firstit,lastit);
			// Create_vector_of_chains_points
			auto vs = LinesVectorCreate(firstit,lastit,pcounter);
			//Repalce_unsort_vector_of_points_into_sort_vector_of_chains_points 
			lv.erase(firstit,lastit);
			lv.insert(firstit,vs.begin(),vs.end());
	}
}

vvs_t LinePointsMoveUp (vvs_t&& vvs){
/*
#############_CIRCLE_#############
    * Command G01*	
    * Start_position: X_Y_D02*;
    * Command G75*;
    * 
    * Command G03*;
    * End_position: X_Y_I_J_D01*;
    * Command G01*;
##################################
*/
//This function moving up points of lines 
	for(auto& vs:vvs){

		for(auto CircleIter=vs.begin()+1,lastit=vs.end(); CircleIter!=lastit; ){
			CircleIter=find_if(vs.begin()+1,lastit,[](std::string& str){return str=="G75*";});
			//Circle_MoveDown
			if(CircleIter!=lastit){
				--CircleIter;
				for(int k=0;k<5;++k){
					vs.push_back(*CircleIter);
					vs.erase(CircleIter);
				}
				lastit-=5;
			}
		}
	}
	return vvs;
}

vvs_t AperturesIntoVector ( std::ifstream& filename){
//This function sorting data by apertures and return vector of string vector
	vvs_t vvs;
	for(std::string line {""}; getline(filename,line); ){
		/*Add_apertures_into_vector*/
		if(line == "G04 APERTURE LIST*")
			for( size_t acounter=0; getline(filename,line) && line!="G04 APERTURE END LIST*"; ++acounter){
				if( line.substr(0,3) == "%AD" ){
					vvs.push_back(vs_t {line});
						std::cout << "  * Vector ["<< acounter <<"][0] = \""<< line <<"\" was created." << std::endl;
				}
			}
		/*Add_positioins_to_apertures*/
		else if(line[0]=='D')
			for_each(vvs.begin(),vvs.end(),[&line,&filename](vs_t& sub_vs){
				if( sub_vs[0].substr(3,3) == line.substr(0,3))
					for( ; getline(filename,line) && line[0]!='D' && line!="M02*"; sub_vs.push_back(line));
			});
		//Check line on data end
		if(line=="M02*") break;
	}
	return vvs;
}

void CreateSortedMovementVector ( std::ifstream&& input, std::ofstream&& output ){
	std::cout << "* File opened. " << std::endl;
	
	auto vs=LinePointsMoveUp(AperturesIntoVector(input));
	VectorSort(vs);
		
	for(auto& v:vs)
		for(auto& s:v)
			output << s << std::endl;
}

void inline IOPathExistsCheck( const std::string& input_path_string, const std::string& output_path_string ){	
///This function check input and output data on exist,direction and file type.
	//Check input data 
	if(!exists(bfs::path { input_path_string })){
		if (input_path_string[input_path_string.size()-1] == '/' ) 
			throw std::string { "Directory: \" " + input_path_string + " \" is not exists."};
		else 
			throw std::string { "File : \" " + input_path_string + " \" is not exists."}; 
	}
	//Check_output_data
	else if(std::string answer; !exists(bfs::path { output_path_string } )){ 
		//Throw out about outputpath not a directory
		if (output_path_string[output_path_string.size()-1] != '/' ) 
			throw std::string { " \" " + output_path_string + " \" is not directory."}; 

		//Asks about creating the directory 
		std::cout << " -> Direction " << 
			bfs::path {output_path_string} << 
				" not exist.Would you like to create this directory?[yes/No]" << std::endl;	
		if( std::cin >> answer ; answer == "Y" || answer == "Yes" || answer == "y" || answer == "yes")
			bfs::create_directory (bfs::path { output_path_string } ) ;
		
		//If user want not create the directory ,then throw out.
		else  throw std::string { "\" " + output_path_string + " \" directory is not exists."};
	}
}

void ConvertSMV( const std::string& input_path_string , const std::string& output_path_string){
	//Check data
	IOPathExistsCheck ( input_path_string, output_path_string );

	if( bfs::is_regular_file( bfs::path { input_path_string } ) ){
		CreateSortedMovementVector(
			std::ifstream { bfs::path { input_path_string }.string() }, 
			std::ofstream { bfs::path { output_path_string }.string() +  bfs::path { input_path_string }.stem().string() + ".smv" }
		);						
		std::cout << "* Result was writed into " 
			 << bfs::canonical(bfs::path { output_path_string + bfs::path { input_path_string }.stem().string() + ".smv"}) << std::endl << std::endl;
	}
	else if ( bool file_finded = false; bfs::is_directory ( bfs::path { input_path_string } ) ){
		//Run to files in directory 
		for(dir_iter_t begin{bfs::path {input_path_string}}, end; begin != end; ++begin){
			
			if(std::string answer; begin->path().extension() == ".gbr"){
				std::cout << "* Open file: "<< begin->path().filename() << " ?[yes/No] -> ";
				
				if( std::cin >> answer ; answer == "Y" || answer == "Yes" || answer == "y" || answer == "yes"){
					CreateSortedMovementVector(
						std::ifstream { begin->path().string() },
						std::ofstream { bfs::path { output_path_string + begin->path().stem().string() + ".smv" }.string() }
					);
					std::cout << "* Result was writed into " 
						<< bfs::canonical(bfs::path { output_path_string + begin->path().stem().string() + ".smv"}) 
							<< std::endl << std::endl;
				}
				file_finded=true;
			}
		}
		if( !file_finded ) std::cout << " -> Files with \"gbr\" extension not finded. " << std::endl;
	}
}
var_map_t ParseCommandLine( int& argc , char** argv){
	//Options description 
	opt::options_description desc (
		"Using: csmv [Parameters]/[Path]\n"
		"The \"csmv\" program convert unsorted data file from \"KiCad\" with \"gbr\" extention to sorted movement vector file with \"smv\" extention.\n\n"
		"1)If user not used command parameters , then program search files with \"gbr\" extention in local path by default.\n"
		"Result will be write into file with filename and \"smv\" to local directory by default.\n\n"
		"2)If user used \"PathToFile\" or \"--path\" parameter only, then program will write result into file with filename \nand \"smv\" extention to local directory by default.\n\n"
		"3)If user used \"--out\" parameter only, then the program will be search files with \"gbr\" extention\nin local direcory and result will write into file with out directory."
		"If out directory do not exist,then the program\nwill ask user about creating the directory.\n\n"
		"4)If user used first parameter PathToFile with \"gbr\" extention or \"--path\" and second parameter OutDirectory or \"--out\" ,\nthen the program will be work with this file and result will write to file with \"smv\" extention in out directory.\n\n"
		"All_Parameters"
		);
	//Options creation
	desc.add_options()
		("path",opt::value <std::string>(),"File path with \"gbr\" extetion.")
		("out",opt::value <std::string>(),"Out path files with \"smv\" extention.")
		("help,h","Display this help and exit.");

	opt::variables_map vm;
	opt::store(opt::parse_command_line (argc, argv, desc), vm );
	opt::notify(vm);
	
	if(vm.count("help")){ 
		std::cout << desc << std::endl;
		exit(0);
	}
	return vm;
}
