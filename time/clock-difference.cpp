#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    clock_t t1, t2;
    t1 = t2 = clock();

    // loop until t2 gets a different value
    while(t1 == t2)
        t2 = clock();

    // print resolution of clock()
    cout << (double)(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms.\n";

    return 0;
}
