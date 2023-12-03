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

    unsigned long int num = strtoul(argv[1], nullptr, 10);
 
        cout << "Sequential code:" << endl;
        cout << "Prime numbers up to " << num << ":" << endl;
        for (unsigned long int i = 2; i <= num; i++) {
                if (isPrime(i)) {
                cout << i << " ";
                }
            }
        cout << endl;
    

    return 0;
}

