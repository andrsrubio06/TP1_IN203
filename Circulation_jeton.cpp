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

	MPI_Status status;

	int jeton;

    if (rank == 0) {

        jeton = initValue;
        MPI_Send(&jeton, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&jeton, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
    
	} else {
        MPI_Recv(&jeton, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        MPI_Send(&(++jeton), 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        std::cout 
			<< std::endl
            << "The final value of the jeton: " 
            << jeton 
            << ", initial value of the jeton:"
            << initValue
            << std::endl;
    }



	MPI_Finalize();
	return EXIT_SUCCESS;
}
