#include "CVL.hpp"
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

vvs_t AperturesIntoVector (std::ifstream& filename){
//This function sorting data by apertures and return vector of string vector
	vvs_t vvs;
	for(std::string line =""; getline(filename,line); ){
		/*Add_apertures_into_vector*/
		if(line == "G04 APERTURE LIST*"){
			for(size_t acounter=0; getline(filename,line) && line!="G04 APERTURE END LIST*"; ++acounter){
				vvs.push_back(vs_t {line});
				std::cout << "  * Vector ["<<acounter<<"][0] = \""<< line <<"\" was created." << std::endl;
			}
		}
		/*Add_positioins_to_apertures*/
		else if(line[0]=='D'){
			for_each(vvs.begin(),vvs.end(),[&](vs_t& subvs){
				if(subvs[0].substr(3,3)==line.substr(0,3))
					for(; getline(filename,line) && line[0]!='D' && line!="M02*"; subvs.push_back(line));
			});
		}
		//Check line on data end
		if(line=="M02*") break;
	}
	return vvs;
}

void FilesWork( const std::string& ifilename,const std::string& ofilename){
	//Create fstreams with RAII
	std::ifstream filename;
	std::ofstream CVLfile;
	
	// settings bits
	filename.exceptions(std::ifstream::badbit | std::ifstream::failbit );
	CVLfile.exceptions(std::ifstream::badbit | std::ifstream::failbit );
	
	try{
		if(ifilename.substr(ifilename.find_last_of('.')) != ".gbr") 
			throw string {"File \" "+ ifilename + " \" with not \"gbr\" extention."};
		//Try open input files 	
		cout << "* Try opening file... " << endl;
			filename.open(ifilename);
		cout << "  * File was opened. " << endl;
		
		//Sorting points one by one like chains
		auto vs=LinePointsMoveUp(AperturesIntoVector(filename));
		VectorSort(vs);
		
		//Try open output file and write linepoints into it
		CVLfile.open(ofilename);
			for(auto& v:vs)
				for(auto& s:v)
					CVLfile << s << endl;
		//Message about datat was writed	
		cout << "* Result was writed into " << ofilename << endl;
	}
	catch( const std::exception &ex ){
		cout << "Program down..." << endl << "[ Error ]: " << ex.what() << endl;
		exit(0);
	}
	catch( const string& excstr ){
		cout<< "[ Error ]: "<< excstr << endl;	
		exit(0);
	}
}
