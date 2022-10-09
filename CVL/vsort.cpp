#include "vsort.hpp"

vpss_t StartPositionFinder(vs_iterator& firstit,vs_iterator& lastit){
	vpss_t startpoints;
	//Runing on d2 positions only
	for(auto D2=firstit; D2!=lastit; D2+=2){
		//Local value definitions
		size_t D2_repeat_counter=0;
		string D2_string=*D2;

		for(auto D1=firstit; D1!=lastit; ){
			//Searching start points
			D1=find_if(firstit, lastit, [&D2_string](std::string& str){
				// "...D01*->\n" =>_sub_2_=> "...D0->1*\n" && "...D0->2*\n" != "...D0->1*\n"
				return D2_string.substr(0,19)==str.substr(0,19) && str.at(str.size()-2)!= D2_string.at( D2_string.size()-2 ) ;});
			if( D1 != lastit ){
				//"...D1*" point founted and if cordinates of this point equal start point ,then quit.
				if( --D1; *D2 == *D1 )break;
				D2_string = *D1;
				++D2_repeat_counter;
			}
		}
		//Start positions was founted and locate in d2_string.
		auto OldStartPointIt=find_if(startpoints.begin(), startpoints.end(), [&](auto& pis){return pis.second == D2_string;});

		//Start point add if not exist in startpoints vector.
		if(OldStartPointIt == startpoints.end())
			startpoints.push_back(make_pair(D2_repeat_counter,D2_string));
		//If a new start point have repeate counter greater then in startpoints vector,then replace repeate counters ;
		else if(OldStartPointIt != startpoints.end() && OldStartPointIt->first < D2_repeat_counter){
			OldStartPointIt -> first = D2_repeat_counter;
			OldStartPointIt -> second = D2_string;
		}
	}
	//Sort result default ( min to max )
	sort(startpoints.begin(), startpoints.end());
	
	//NRVO
	return startpoints;
}

vs_t LinesVectorCreate ( vs_iterator& FirstIt, vs_iterator& LastIt, vpss_t& startpoints ){
	vs_t vs;
	
	// Find start points one by one
	for(string start_point; !startpoints.empty(); startpoints.pop_back()){
		
		//Put start point from startpoints into start_point string
		start_point = startpoints.back().second;	
		auto D2Find=find_if(FirstIt,LastIt,[&start_point](string& str){ return start_point == str; });

				//Put into string vector start point "D2" and next "D1" point.	
				vs.push_back(*D2Find);
				vs.push_back(*++D2Find);
				
			for(start_point = *D2Find; D2Find!=LastIt; ){
			
				//Search next D2 point
				D2Find=find_if(FirstIt,LastIt,[&start_point](std::string& str){ 
					return start_point.substr(0,19)==str.substr(0,19) && 
					str.at(str.size()-2)!= start_point.at(start_point.size()-2);});

				//Search d2 in startpoints and if it founted delete this point frome d2_vector ;
				auto d2_founted=find_if(startpoints.begin(),startpoints.end()-1,[&D2Find](pss_t& pis){
					return *D2Find==pis.second; });
				if(d2_founted != startpoints.end()-1) startpoints.erase(d2_founted);
				
				//Push back next d2 point into string vector "vs" .
				if(D2Find!=LastIt && *D2Find!=startpoints.back().second){
					vs.push_back(*(++D2Find));
					start_point = *D2Find;
				}
				//If d2 repeat with poped string, then goto next d2 point from startpoints.
				else if (*D2Find == startpoints.back().second) break;
			}
	}
	//NRVO
	return vs;
}
