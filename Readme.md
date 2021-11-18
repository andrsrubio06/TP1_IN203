# Answers of the TP 1

## Un hello World parallèle

### Tester le programme avec 1 à 16 processus. Que constatez-vous ?

when using a single process, I noticed that its the same as sequential programming, and when switching to 16 processes, I could notice that the rank of the processes did not follow an order to execute.

### Notes of the modification in hello world
The idea of having the different documents, it is more convenient because we can see in a more orderly way which is the rank that performed a certain task. We can have a more user-friendly visualization of the tasks.

## Envoi bloquant et non bloquant

### Envoi bloquant
    myvar = 0;
    for ( i = 1; i < numtasks , ++i ) {
      task = i;
        MPI_Send (& myvar ,... ,... , task ,...) ;
        myvar = myvar + 2;
        // Do some works
    }

In the blocking type of sending we can ensure that the processes will wait for things to happen in order, without the problem of a process receiving a message that has not yet been sent.

### Envoi non bloquant
    
    myvar = 0;
    for ( i = 1; i < numtasks , ++i ) {
      task = i;
        MPI_ISend (& myvar ,... ,... , task ,...) ;
        myvar = myvar + 2;
        // Do some works
        ...
        MPI_Wait (...) ;
    }
in this other type of sending, we do not have an order restriction, we have an action that is performed by the first process to arrive, running the risk of receiving messages that have not been sent and creating problems with lost information, having to add a wait to the processes, the corresponding wait according to the step, so we can ensure that the processes will not make mistakes by accessing non-existent or erroneous information.

### Circulation d’un jeton dans un anneau 
  