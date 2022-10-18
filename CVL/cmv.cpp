#include "cmv.hpp"
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
void VectorSort(vvs_t& vvs){
	for(auto& lv : vvs){
		auto firstit=lv.begin()+1;
		auto lastit=find_if(firstit,lv.end(),[](std::string &str){return str=="G75*";});
			if(lastit != lv.end()) lastit-=1;
			
			// Return_sorted_vector_of_pair <repeat_counter, start_positions> 
				vpss_t pcounter = StartPositionFinder(firstit,lastit);
			
			// Create_vector_of_chains_points
				auto vs = LinesVectorCreate(firstit,lastit,pcounter);
			
			//Repalce_unsort-vector_of-points_into_sort_vector_of_chains_points 
				lv.erase(firstit,lastit);
				lv.insert(firstit,vs.begin(),vs.end());
	}
}

vvs_t LinePointsMoveUp (vvs_t&& vvs){
//This function moving up points of lines 
	for(auto& vs:vvs){

		for(auto findit=vs.begin()+1,lastit=vs.end(); findit!=lastit; ){
			findit=find_if(vs.begin()+1,lastit,[](std::string& str){return str=="G75*";});
			//Circle_MoveDown
			if(findit!=lastit){
				--findit;
				for(int k=0;k<5;++k){
					vs.push_back(*findit);
					vs.erase(findit);
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
	for(std::string line =""; getline(filename,line); ){

		/*Add_apertures_into_vector*/
		if(line == "G04 APERTURE LIST*")
			for(size_t acounter=0; getline(filename,line) && line!="G04 APERTURE END LIST*"; ++acounter){
				if( line.substr(0,3) == "%AD" )vvs.push_back(vs_t {line});
				std::cout << "  * Vector ["<<acounter<<"][0] = \""<< line <<"\" was created." << std::endl;
			}
		
		/*Add_positioins_to_apertures*/
		else if(line[0]=='D')
			for_each(vvs.begin(),vvs.end(),[&](vs_t& subvs){
				if(subvs[0].substr(3,3)==line.substr(0,3))
					for(; getline(filename,line) && line[0]!='D' && line!="M02*"; subvs.push_back(line));
			});
		
		//Check line on data end
		if(line=="M02*") break;
	}
	return vvs;
}
void inline CreateSortedMovementVector ( std::ifstream&& input, std::ofstream&& output ){
	cout << "* File opened. " << endl;

	//Sorting points one by one like chains
	auto vs=LinePointsMoveUp(AperturesIntoVector(input));
	VectorSort(vs);
	
	//Try open output file and write linepoints into it
	for(auto& v:vs)
		for(auto& s:v)
			output << s << endl;
}
void FilesWork( const string& input_path_string , const string& output_path_string){
// ./CVL [default_in_path] [default_out_path] ||
// ./CVL ./input_filt_path] ||
// ./CVL [default_in_path]   ./outputfile_path ||
// ./CVL .../inputfile.gbr  .../outputfile_path 

	if(!exists( bfs::path { input_path_string } ))
		throw string { "\" " + input_path_string + " \" is not exists."};
	else if(string answer;!exists(bfs::path { output_path_string } )){ 
		cout << " -> Direction " << bfs::path {output_path_string} <<" not exist.Would you like to create this directory?[yes/No]" << endl;	
			if( cin >> answer ; answer == "Y" || answer == "Yes" || answer == "y" || answer == "yes"){
				bfs::create_directory (bfs::path { output_path_string } ) ;
			}
			else  throw string { "\" " + output_path_string + " \"is not exists."};
	}
 
	if( bfs::is_regular_file( bfs::path { input_path_string } ) )
		CreateSortedMovementVector(
			std::ifstream { bfs::path { input_path_string }.string() }, 
			std::ofstream { bfs::path { output_path_string }.string() +  bfs::path { input_path_string }.stem().string() + ".smv" }
		);						
	else if (bfs::is_directory(bfs::path {input_path_string})){
	
		for(dir_iter_t begin{bfs::path {input_path_string}},end; begin != end; ++begin){
			
			if(string answer; begin->path().extension() == ".gbr"){
				cout << " * Open file: "<< begin->path().filename() << " ?[yes/No]" << endl;
				if( cin >> answer ; answer == "Y" || answer == "Yes" || answer == "y" || answer == "yes"){
					CreateSortedMovementVector(
						std::ifstream { begin->path().string() },
						std::ofstream { bfs::path { output_path_string + begin->path().stem().string() + ".smv" }.string() }
					);
					cout << "* Result was writed into " 
						 << bfs::canonical(bfs::path { output_path_string + begin->path().stem().string() + ".smv"}) << endl << endl;
				}
			}
		}
	}
}
