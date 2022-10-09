include "../Include/tool.hpp"
// main(VectorListFile);
int main (int argc,char** argv){
	//string path="/home/hwmi3/Coding/Cpp/";
	ifstream file;
	tool graver;
		try{
			file.open(static_cast<string>(argv[1])+"VectorList");
			for(string line="";getline(file,line););// action(analysis(line));	
		}
		catch(const exception &ex){
			cout<<"Can't open file"<<argv[1]<<endl;
			exit(0);
		}


	return 0;
}
