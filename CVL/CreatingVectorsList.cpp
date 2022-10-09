#include "CVL.hpp"
// ./CVL ./file.gdr || ./CVL
//main(CVL,file)

int main(int argc,char** argv){

	if(argc == 2) {
		string filename = argv[1];
		filename = filename.substr(filename.find_last_of('/')+1, filename.find_last_of('.') - filename.find_last_of('/')-1 );
	
		FilesWork(argv[1],"../"+filename+".svl");
	}
	else if(argc == 1){
		for(dirit_t begin("../"),end; begin != end; ++begin){
			if(string answer; begin->path().extension() == ".gbr") {
				
			cout << "Open file: "<< *begin << " ?[Yes/no]" << endl;
				cin >> answer;
					//cout<<begin->path().string()<<endl;
				if(answer == "Y" || answer == "Yes" || answer == "y" || answer == "yes")
					FilesWork(begin->path().string(), "../" + begin->path().stem().string() + ".svl");
				else if (answer == "N" || answer == "No" || answer == "n" || answer == "no") 
					continue;

			}/*if*/
		}/*for*/
	}/*else if*/
return 0;
}
	
	
