#include "definitions.h"

int main(int argc, char **argv)
{
    //Common variables
    int nIterations=0, iter=0;

    //Variable for MPI
    int rank, commSize, status;
    int arrayIndexBegin, arrayIndexEnd;
    int nextNeighbourIndex, prevNeighbourIndex;

    // error check on the input size
    if(std::atoi(argv[1])<=0){
        std::cerr<<" Invalid size of array ! They have to be >0!"<<std::endl;
        abort();
    }
    if(std::atoi(argv[2])<=0){
        std::cerr<<" Invalid number of iterations ! They have to be >0!"<<std::endl;
        abort();
    }
    else{
    //Store the number of iterations
    nIterations = std::atoi(argv[2]);
    }

    //Create arrays to store the values
    std::vector<double> vecA;
    std::vector<double> vecB;

    allocateMemory(vecA,std::atoi(argv[1])+2);
    allocateMemory(vecB,std::atoi(argv[1])+2);
	std::cout<<" Finished allocating memory\n";


    //Initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Compute the index range for each rank
    computeArraySliceIndexForEachRank(0, std::atoi(argv[1])-1, commSize, rank, arrayIndexBegin, arrayIndexEnd);
    std::cout<<"rank="<<rank<<" startIndex="<<arrayIndexBegin<<" endIndex="<<arrayIndexEnd<<std::endl;

    computeExchangeNeighbourIndexForEachRank(rank, commSize, nextNeighbourIndex, prevNeighbourIndex);

	//std::cout<<"rank="<<rank<<" nextNeigbourIndex="<<nextNeighbourIndex<<" prevNeighbourIndex="<<prevNeighbourIndex<<std::endl;

    //Initialize the arrays with index values for vecA and 0 for vecB
    initialize(vecA, arrayIndexBegin, arrayIndexEnd, 0);
    initialize(vecB, arrayIndexBegin, arrayIndexEnd, 1);
    std::cout<<"Finished initializing vectors with values\n";

    while(iter<nIterations){
        //Perform physical boundary condition; currently periodic.

        //Perform rank-boundary data exchanges

        //Perform update of vecB based on values in vecA

        //copy vecB into vecA

        //increment the iteration index
        iter++;
    }

    //End MPI
	MPI_Finalize();

    deAllocateMemory(vecA);
    deAllocateMemory(vecB);

	std::cout<<" Finished de-allocating memory\n";
    return(0);
}