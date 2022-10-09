#include "vsort.hpp"

vpss_t StartPositionFinder(vs_iterator& firstit,vs_iterator& lastit){
	vpss_t d2_vector;
	for(auto d2=firstit; d2!=lastit; d2+=2){
		//
		size_t d2_repeat_counter=0;
		string d2_string=*d2;

		for(auto d1=firstit; d1!=lastit; ){
			d1=find_if(firstit, lastit, [&d2_string](std::string& str){
				// ...D01*->\n =>_sub_2_=> ...D0->1*\n && ...D0->2*\n != ...D0->1*\n
				return d2_string.substr(0,19)==str.substr(0,19) && str.at(str.size()-2)!=d2_string.at(d2_string.size()-2);});
			if(d1!=lastit){
				if(--d1,*d2==*d1)break;
				d2_string=*d1;
				++d2_repeat_counter;
			}
		}
		//Check beginpositions repeat;
		auto findit=find_if(d2_vector.begin(), d2_vector.end(), [&](auto& pis){return pis.second == d2_string;});

		if(findit == d2_vector.end())
			d2_vector.push_back(make_pair(d2_repeat_counter,d2_string));
		else if(findit!=d2_vector.end() && findit->first < d2_repeat_counter){
			findit->first=d2_repeat_counter;
			findit->second=d2_string;
		}
	}
	//Sort result default ( min to max )
	sort(d2_vector.begin(), d2_vector.end());
	
	//NRVO
	return d2_vector;
}

vs_t LinesVectorCreate ( vs_iterator& firstit,vs_iterator& lastit,vpss_t& d2_vector){
	vs_t vs;
	// Find start points one by one
	for(string start_point; !d2_vector.empty(); d2_vector.pop_back()){
		
		//Put start point from d2_vector into start_point string
		start_point = d2_vector.back().second;	
		auto d2_find=find_if(firstit,lastit,[&start_point](std::string& str){ return start_point == str; });

				//Put into string vector "vs" start point d2 and next point.	
				vs.push_back(*d2_find);
				vs.push_back(*++d2_find);
			for(start_point = *d2_find; d2_find!=lastit; ){
			
				//Search next de point
				d2_find=find_if(firstit,lastit,[&start_point](std::string& str){ 
					return start_point.substr(0,19)==str.substr(0,19) && 
					str.at(str.size()-2)!= start_point.at(start_point.size()-2);});

				//Search d2 in d2_vector and if it founted delete this point frome d2_vector ;
				auto d2_founted=find_if(d2_vector.begin(),d2_vector.end()-1,[&d2_find](pss_t& pis){
					return *d2_find==pis.second; });
				if(d2_founted != d2_vector.end()-1) d2_vector.erase(d2_founted);
				
				//Push back next d2 point into string vector "vs" .
				if(d2_find != lastit && *d2_find != d2_vector.back().second){
					vs.push_back(*(++d2_find));
					start_point = *d2_find;
				}
				//If d2 repeat with poped string, then goto next d2 point from d2_vector.
				else if (*d2_find == d2_vector.back().second) break;
			}
	}
	//NRVO
	return vs;
}
