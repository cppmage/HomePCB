#ifndef __tool
	#define __tool
	#include <iostream>
	#include <string>
	#include <fstream>
	using namespace std;
	
namespace tool{
	template <class T>
		class tool {
			T xpos_,ypos_,zpos_;
			T dx_,dy_,dz_;
			T delay_;
			bool zupflag_;
			bool onflag_;
		public:
			tool() noexcept;
			tool(const tool &tl)=delete;

			void goTo(const int &xpos,const int &ypos);
			void zMove(const int &up);
			
			void operator <<(string &&str);
			void operator = (const tool &tl)=delete;
			
			bool isUp() const ;
			bool isOn() const ;
			
			void home();
			void on();
			void off();

			~tool();
	};
}
#endif
