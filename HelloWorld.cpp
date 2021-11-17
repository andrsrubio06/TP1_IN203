# include <iostream>
# include <cstdlib>
# include <mpi.h>
# include <sstream>
# include <fstream>

int main( int nargs, char* argv[] )
{
    MPI_Init(&nargs, &argv);
    int numero_du_processus, nombre_de_processus;

    MPI_Comm_rank(MPI_COMM_WORLD,
                  &numero_du_processus);
    MPI_Comm_size(MPI_COMM_WORLD, 
                  &nombre_de_processus);
    
    std::stringstream file_name;
    file_name << "Output" 
              << numero_du_processus << ".txt"; // on donne un nom de fichier txt pour l'écriture
    std::ofstream fich(file_name.str()); // écrit vers le fichier file_name.str() de nom de var fich
    fich << "Hello world from " 
         << numero_du_processus << " in "
         << nombre_de_processus << " executed" 
         << std::endl; // on écrit dans le fichier
    fich.close(); // on ferme écriture

/*  output in console commented
    std::cout << "Bonjour, je suis  la tache n° " 
              << numero_du_processus << " sur "
              << nombre_de_processus << " taches" 
              << std::endl;*/
    MPI_Finalize();
    return EXIT_SUCCESS;
}
