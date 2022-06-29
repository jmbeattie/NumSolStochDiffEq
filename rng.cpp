#include <iostream>
#include <math.h>
#include <list>

using namespace std;

list<uint32_t> randUnif(int seed, int b, int n, int a=65539, uint32_t c=pow(2,31));


int main()
{
    list<uint32_t> randNums = randUnif(5, 0, 10);

    for(list<uint32_t>::iterator it = randNums.begin(); !(it == randNums.end()); it++)
    {
        cout << *it << "\n";
    }

    return 0;
}


list<uint32_t> randUnif(int seed, int b, int n, int a, uint32_t c)
{
    int x0 = seed;
    list<uint32_t> x;
    for(int i = 0; i < n; i++)
    {
        x.push_front((a*x0 + b) % c);
        x0 = x.front();
    }
    return x;
}