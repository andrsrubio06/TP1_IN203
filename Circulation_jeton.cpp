# include <iostream>
# include <cstdlib>
# include <mpi.h>
# include <sstream>

int main( int argc, char* argv[] )
{

    int initValue = (argc > 1) ? atoi(argv[1]) : 10;

	MPI_Init( &argc, &argv );
	
	int rank, numTasks, next, prev;

	MPI_Comm globComm;
	MPI_Comm_dup(MPI_COMM_WORLD, &globComm);
	MPI_Comm_size(globComm, &numTasks);
	MPI_Comm_rank(globComm, &rank);

	prev = rank - 1;
    next = rank + 1;
    if (rank == 0) prev = numTasks - 1;
    if (rank == (numTasks - 1)) next = 0;

	MPI_Request reqs;
	MPI_Status stats;

	int jeton;

		jeton = initValue+rank;
		
        MPI_Isend(&jeton, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &reqs);
		MPI_Irecv(&jeton, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &reqs);
        MPI_Wait(&reqs, &stats);
        
		std::cout 
			<< std::endl
            << "This is the jeton: " 
			<< jeton
			<< " in the rank: "
			<< rank
            << std::endl;

		

	MPI_Finalize();
	return EXIT_SUCCESS;
}
