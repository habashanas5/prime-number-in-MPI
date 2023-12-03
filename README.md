explane each file and result 
---------------------------

prime.cpp 
   number is read through command 
   have a Sequential code
   
   command:
   anas@anas-HP:~/assignment2-parallel$ mpic++ prime.cpp -o prime 
   anas@anas-HP:~/assignment2-parallel$ ./prime 32

    
primenum.cpp
   - First, the number is read through command 
   - Secondly, doing a function that calculate  all prime numbers for that number readed through command (Sequential code)
   - Third, the operations were distributed to processes for odd numbers up to number
   - used  MPI_Barrier(MPI_COMM_WORLD);

   command:
   anas@anas-HP:~/assignment2-parallel$ mpic++ primenum.cpp -o primenum
   anas@anas-HP:~/assignment2-parallel$ mpirun -np 3 ./primenum 32


mpiprime.cpp
   - in this part to check for primality in parallel way and calculate the execution time through ( GetWallTime and MPI_Wtime )
   - used  MPI_Barrier(MPI_COMM_WORLD);
  
   command:
   anas@anas-HP:~/assignment2-parallel$ mpic++ mpiprime.cpp -o mpiprime
   anas@anas-HP:~/assignment2-parallel$ mpirun -np 3 ./mpiprime 32


mpiruncyclic.cpp
    - load imbalance
    - the operations were distributed to processes for odd numbers up to number
    - used  MPI_Barrier(MPI_COMM_WORLD);
    
    command:
    anas@anas-HP:~/assignment2-parallel$ mpic++ mpiruncyclic.cpp -o mpiruncyclic 
    anas@anas-HP:~/assignment2-parallel$ mpirun -np 3 ./mpiruncyclic 32
    
    
mpiprimecyclic.cpp

   -rewrite the mpiprime program using cyclic distribution
   
   command:
   anas@anas-HP:~/assignment2-parallel$ mpic++ mpiprimecyclic.cpp -o mpiprimecyclic
   anas@anas-HP:~/assignment2-parallel$ mpirun -np 3 ./mpiprimecyclic 32

   

		file name                                           				   result 
		---------                                                    ---------- 
		
		prime.cpp                                               Sequential code:
													                                  Prime numbers up to 32:
													                                  2 3 5 7 11 13 17 19 23 29 31 
		
		
		primenum.cpp                                            Parallel code:
                      																		  Process 0: 3 5 7 9 11 
                      																		  Parallel code:
                      																	    Process 1: 13 15 17 19 21 
                      																      Parallel code:
                      																		  Process 2: 23 25 27 29 31 

                        																	  Sequential code:
                        																	  Prime numbers up to 32:
                        																	  2 3 5 7 11 13 17 19 23 29 31 
																	    
		
		mpiprime.cpp                                            Parallel code:
                        																		Process 2: 23 29 31 
                        																		Parallel code:
                        																		Process 0: 2 3 5 7 11 
                        																		Parallel code:
                        																		Process 1: 13 17 19 
                        																		Process 0: Elapsed time (seconds) using GetWallTime = 0.000207186
                        																		Elapsed time(seconds) using MPI_Wtime = 0.000234857
                        																		Process 1: Elapsed time (seconds) using GetWallTime = 0.000200987
                        																		Process 2: Elapsed time (seconds) using GetWallTime = 0.000259876


    mpiruncyclic.cpp 				                        				Parallel code:
                        																		Process 0: 3 9 15 21 27 
                        																		Parallel code:
                        																		Process 1: 5 11 17 23 29 
                        																		Parallel code:
                        																		Process 2: 7 13 19 25 31 

		
		mpiprimecyclic.cpp            							        		Process 2: 7 13 19 31 
                        																		Process 0: 3 
                        																		Process 1: 5 11 17 23 29 
                        																		Process 1: Elapsed time (seconds) using GetWallTime = 0.000236988
                        																		Process 2: Elapsed time (seconds) using GetWallTime = 0.000226974
                        																		Process 0: Elapsed time (seconds) using GetWallTime = 0.000181913
                        																		Elapsed time (seconds) using MPI_Wtime = 0.000227558

-----------------------------------------------------------
q2: Why the algorithms checks only up to sqrt(n) not up to N?

Checking up to the square root of n is a significant optimization because it reduces the number of iterations required to determine primality. If you were to check up to N, where N is a very large number, it would be significantly less efficient in terms of computational effort.

---------------------------------------------------------

q3: pseudocode for the mpiprime.cpp code, the pseudocode should just explain how did you make the assignments of the iterations to process :

1. Initialize MPI and get the world size and rank for each process.
2. obtain the value of "num," which represents the range of numbers to check for primality.
3. Start a timer (startT) using GetWallTime and MPI timer (ls) using MPI_Wtime to measure the overall execution time.
4. Calculate the range of iterations to be processed by each process:n
    b. Distribute the iterations among processes by dividing the range (2 to num) into approximately equal segments.
5. If the current process is the last one (worldRank == worldSize - 1), adjust the "end" value to ensure all iterations are covered.
6. Output a message indicating the start of the parallel code.
7. Iterate through the range of numbers assigned to the current process:
    a. Check if each number is prime using the "isPrime" function.
    b. Print the prime numbers found by each process.
8. Synchronize all processes using MPI_Barrier to ensure they complete their work.
9. Stop the timers (finish and lf) to measure the overall elapsed time and the local elapsed time using GetWallTime and MPI_Wtime, respectively.
10. Calculate the elapsed time for the current process using GetWallTime and MPI_Wtime.
11. If the current process is the root process (rank 0), reduce the local elapsed times from all processes to find the maximum elapsed time using MPI_Reduce.
12. The root process prints the maximum elapsed time and the elapsed time calculated using GetWallTime.
13. Finalize MPI and exit.

---------------------------------------------------------

q4: pseudocode for the mpiprimecyclic.cpp code, the pseudocode should just explain how did you make the cyclic assignments of the iterations to process

1. Initialize MPI and get the world size and rank for each process.
2. Calculate the range of numbers to be checked for primality for the current process:
   - Calculate 'start' as 3 + (worldRank * 2), which ensures that processes start from different initial numbers. (For example, process 0 starts from 3, process 1 starts from 5, etc.)
   - Calculate 'end' as 'num', which is the upper limit of the range.
3. Use a barrier to synchronize all processes before proceeding. This ensures that no process starts its computation before all processes have finished printing their assigned ranges.
4. Finalize MPI and terminate the program.
