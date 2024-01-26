#include "definitions.h"


void computeArraySliceIndexForEachRank(const int& n1, const int& n2, const int& nprocs, const int& irank, int& istart, int& iend,
int& _nElementsForRank){
    int iwork1 = static_cast<int>((n2-n1+1)/nprocs);
    int iwork2 = (n2-n1+1)%nprocs;
    istart = irank*iwork1 + n1 + std::min(irank, iwork2);
    iend   = istart + iwork1 - 1;
    if(iwork2>irank)
      iend = iend +1;
   _nElementsForRank = iend - istart + 1;
}

void computeExchangeNeighbourIndexForEachRank(const int irank, const int nprocs, int& _nextNeighbourIndex,
int& _prevNeighbourIndex){
   //Compute index of next and previous processes for data exchange
	_nextNeighbourIndex = irank+1;
	_prevNeighbourIndex = irank-1;

	//Modify for first and last ranks
	if(irank==MASTER)
		_prevNeighbourIndex = nprocs-1;
	if(irank==nprocs-1)
		_nextNeighbourIndex = MASTER;
}