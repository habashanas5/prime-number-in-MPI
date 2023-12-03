#include <iostream>
#include <cstdlib>
#include <mpi.h>

using namespace std;

bool isPrime(unsigned long int n) {
    if (n <= 1)
        return false;

    for (unsigned long int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <N>" << endl;
        return 1;
    }

    MPI_Init(&argc, &argv);

    int worldSize, worldRank;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

    unsigned long int num = strtoul(argv[1], nullptr, 10);

    unsigned long int start = 3 + worldRank * 2; 
    unsigned long int end = num;

    cout << "Parallel code:" << endl;
    cout << "Process " << worldRank << ": ";
    for (unsigned long int i = start; i <= end; i += worldSize * 2) {
        cout << i << " ";
    }
    cout << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

    return 0;
}

