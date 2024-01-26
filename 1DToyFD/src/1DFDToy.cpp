#include "definitions.h"

int main(int argc, char **argv)
{
    //Common variables
    int nIterations=0, iter=0;

    //Variable for MPI
    int rank, commSize;
    int arrayIndexBegin, arrayIndexEnd, numberOfElementsOwnedByRank;
    int nextNeighbourIndex, prevNeighbourIndex;
    //int leftDataSendTag=0, rightDataSendTag=1, leftDataRecvTag=1, rightDataRecvTag=0;
    int leftPhysBoundDataSendTag =0, leftPhysBoundDataRecvTag=0;
    int rightPhysBoundDataSendTag =1, rightPhysBoundDataRecvTag=1;
    int leftInternalDataSendTag = 2, leftInternalDataRecvTag=2;
    int rightInternalDataSendTag=3, rightInternalDataRecvTag=3;



    MPI_Request sendRequest1, sendRequest2, recvRequest1, recvRequest2;
    MPI_Status status;

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


    //Initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Compute the index range for each rank
    computeArraySliceIndexForEachRank(0, std::atoi(argv[1])-1, commSize, rank, arrayIndexBegin, arrayIndexEnd, numberOfElementsOwnedByRank);
    //std::cout<<"rank="<<rank<<" startIndex="<<arrayIndexBegin<<" endIndex="<<arrayIndexEnd<< " noOfElem="<<numberOfElementsOwnedByRank<<std::endl;


    computeExchangeNeighbourIndexForEachRank(rank, commSize, nextNeighbourIndex, prevNeighbourIndex);

	//std::cout<<"rank="<<rank<<" nextNeigbourIndex="<<nextNeighbourIndex<<" prevNeighbourIndex="<<prevNeighbourIndex<<std::endl;
    allocateMemory(vecA,numberOfElementsOwnedByRank+2);
    allocateMemory(vecB,numberOfElementsOwnedByRank+2);
	std::cout<<" Finished allocating memory\n";

    //Initialize the arrays with index values for vecA and 0 for vecB
    initialize(vecA, arrayIndexBegin, arrayIndexEnd, numberOfElementsOwnedByRank, 0);
    initialize(vecB, arrayIndexBegin, arrayIndexEnd, numberOfElementsOwnedByRank ,1);
    std::cout<<"Finished initializing vectors with values\n";
    MPI_Barrier(MPI_COMM_WORLD);

    while(iter<nIterations){

        std::cout<<"Iteration: "<<iter<<std::endl;
        //Perform rank-boundary data exchanges
        //Issue Right data recv req for non-master ranks

       if(rank!=MASTER){
         //std::cout<<"I am rank "<<rank<<" recieving right data from "<<prevNeighbourIndex<<std::endl;
         MPI_Recv(&vecA[0], 1, MPI_DOUBLE, prevNeighbourIndex, rightInternalDataRecvTag, MPI_COMM_WORLD, &status);
       }

       // Isse Right data Send req for all ranks
       //std::cout<<"I am rank "<<rank<<" sending right data to "<<nextNeighbourIndex<<std::endl;
       MPI_Ssend(&vecA[numberOfElementsOwnedByRank], 1, MPI_DOUBLE, nextNeighbourIndex, rightInternalDataSendTag, MPI_COMM_WORLD);

       //Issue Right data Rec req for master
       if(rank==MASTER){
        //std::cout<<"I am rank "<<rank<<" recieving right data from "<<prevNeighbourIndex<<std::endl;
        MPI_Recv(&vecA[0], 1, MPI_DOUBLE, commSize-1, rightInternalDataRecvTag, MPI_COMM_WORLD, &status);
       }

      //Issue left data rec req for non-master ranks
      if(rank!=MASTER){
        //std::cout<<"I am rank "<<rank<<" recieving left data from "<<nextNeighbourIndex<<std::endl;
		 MPI_Recv(&vecA[numberOfElementsOwnedByRank+1], 1, MPI_DOUBLE, nextNeighbourIndex, leftInternalDataRecvTag, MPI_COMM_WORLD, &status);
      }
      //Issue left data send req for all ranks
      //std::cout<<"I am rank "<<rank<<" sending left data to "<<prevNeighbourIndex<<std::endl;
      MPI_Ssend(&vecA[1], 1, MPI_DOUBLE, prevNeighbourIndex, leftInternalDataSendTag, MPI_COMM_WORLD);

      //Issue left data rec req for master
      if(rank==MASTER){
        //std::cout<<"I am rank "<<rank<<" recieving left data from "<<nextNeighbourIndex<<std::endl;
        MPI_Recv(&vecA[numberOfElementsOwnedByRank+1], 1, MPI_DOUBLE, nextNeighbourIndex, leftInternalDataRecvTag, MPI_COMM_WORLD, &status);
      }

      std::cout<<"Finished Exchanging data across Rank boundaries\n";

     //Perform update of vecA values
     updateVector(vecA, numberOfElementsOwnedByRank);


     std::cout<<"Finished updating vector\n";


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