#include "definitions.h"

void initialize(std::vector<double>& vecTemp, const int istart, const int iend, const int _nElementsForRank, bool setElementsToZero=0)
{
  if(!setElementsToZero){
	for(int i=1;i<=_nElementsForRank;i++){
		vecTemp[i]=static_cast<double>(istart+(i-1));
	}
  }
  else{
	for(int i=1;i<=_nElementsForRank;i++){
		vecTemp[i]=0.;
	}
  }
}
