#include "CVL.hpp"
// ./CVL ./file.gdr || ./CVL
//main(CVL,file)

int main(int argc,char** argv){

	if(argc == 2) FilesWork(argv[1]);
	else if(argc == 1){
		for(dirit_t begin("../"),end; begin != end; ++begin){
			if(string answer; begin->path().extension() == ".gbr") {
				cout << "Open file: "<< *begin << " ?[Yes/no]" << endl;
				if(cin >> answer; answer == "Y" || answer == "Yes" || answer == "y" || answer == "yes")
					FilesWork(begin->path().string());

			}/*if*/
		}/*for*/
	}/*else if*/
return 0;
}
	
	
