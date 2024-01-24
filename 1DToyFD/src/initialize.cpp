#include "definitions.h"

void initialize(std::vector<double>& vecTemp, const int istart, const int iend, bool setElementsToZero=0)
{
  if(!setElementsToZero){
	for(int i=istart;i<iend;i++){
		vecTemp[i]=static_cast<double>(i);
	}
  }
  else{
	for(int i=istart;i<iend;i++){
		vecTemp[i]=0.;
	}
  }
}
