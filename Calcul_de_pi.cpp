#include <mpi.h> 
# include <chrono>
# include <random>
#include <iostream>

using namespace std;

double approximate_pi( unsigned long nbSamples ) 
{
	int nbp, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nbp);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    unsigned long nbDarts = 0;

    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    myclock::duration d = myclock::now() - beginning;
    unsigned seed = d.count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution <double> distribution ( -1.0 ,1.0);
    


	cout << endl;
    if(rank == 0) {
        MPI_Status status[nbp - 1];
        MPI_Request reqs[nbp - 1];
        int nbDartsRecv[nbp - 1];
        
        for ( unsigned i = nbp - 1; i > 0 ; i --)
            MPI_Irecv (&nbDartsRecv[i - 1], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &reqs[i - 1]);

        MPI_Waitall(nbp - 1, reqs, status);

        for(unsigned i = 0; i < nbp - 1; i ++){
            cout << "holis " << i + 1 << " r: " << nbDartsRecv[i] << endl;
            nbDarts += nbDartsRecv[i];
        }

        double ratio = double ( nbDarts )/ double ( nbSamples );
        cout << "ratio: " << ratio << endl;
        return ratio;
    }



	for ( unsigned sample = 0; sample < nbSamples/(nbp-1) ; ++ sample ) {
        double x = distribution ( generator );
        double y = distribution ( generator );
        if ( x*x+y*y <=1 ) nbDarts ++;
    }

    MPI_Send(&nbDarts, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    cout << rank << " - " << "nbDarts: " << nbDarts << endl;
    return -1;
}

int main( int argc, char* argv[] )
{

	MPI_Init(&argc, &argv);
    const double pi = 4 * approximate_pi(1000000);
    MPI_Finalize();
    
    if(pi > 0){
        cout << "pi: " << pi << endl;
    }
    return 0;
}
