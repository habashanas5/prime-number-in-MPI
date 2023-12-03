#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <sys/time.h>

using namespace std;

double GetWallTime() {
    struct timeval tp;
    int rtn = gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (1.e-6) * tp.tv_usec);
}

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

    double elapsed;
    double startT = GetWallTime();
    double ls = MPI_Wtime();

    unsigned long int start = 3 + (worldRank * 2);
    unsigned long int end = num;
    unsigned long int step = worldSize*2;

    cout << "Process " << worldRank << ": ";
    for (unsigned long int i = start; i <= end; i += step) {
        if (isPrime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    double finish = GetWallTime();
    double lf = MPI_Wtime();
    double Elapsed_time = finish - startT;
    double le = lf - ls;

    cout << "Process " << worldRank << ": Elapsed time (seconds) using GetWallTime = " << Elapsed_time << endl;

    MPI_Reduce(&le, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (worldRank == 0) {
        cout << "Elapsed time (seconds) using MPI_Wtime = " << elapsed << endl;
    }

    MPI_Finalize();

    return 0;
}

