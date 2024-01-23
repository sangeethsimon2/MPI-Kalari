#include "definitions.h"

int main(int argc, char **argv)
{
    //Variable for MPI
    int rank, size, status;

    //Initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::cout<<"I am rank="<<rank<<"\n";

    //End MPI
	MPI_Finalize();

    return(0);
}