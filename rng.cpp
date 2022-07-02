#include <iostream>
#include <math.h>
#include <list>
#include <string>


using namespace std;


const uint32_t RANDOM_SEED = 424242;


list<uint32_t> randUnif(int n=1, int b=0, int a=65539, uint32_t c=pow(2,31));
list<double> rdn(int n=1, int lo=0, int hi=1);


int main(int argc, char* argv[])
{
    list<double> randNums = rdn(stoi(argv[1]), -100, 0);

    for(list<double>::iterator it = randNums.begin(); !(it == randNums.end()); it++)
    {
        cout << *it << "\n";
    }

    return 0;
}


list<double> rdn(int n, int lo, int hi)
{
    list<uint32_t> randNums = randUnif(n);
    list<double> randFloats;
    int magnitude = hi - lo;
    int size = randNums.size(); // must assign first then reference to avoid short circuit
    for(list<uint32_t>::iterator it = randNums.begin(); !(it == randNums.end()); it++)
    {
        randFloats.push_back((*it/pow(2,31)) * magnitude + lo);
    }
    return randFloats;
}


list<uint32_t> randUnif(int n, int b, int a, uint32_t c)
{
    int x0 = RANDOM_SEED;
    list<uint32_t> x;
    for(int i = 0; i < n; i++)
    {
        x.push_back((a*x0 + b) % c);
        x0 = x.back();
    }
    return x;
}