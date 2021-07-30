#include <deque>
#include <iostream>
#include <math.h>
#include <map>

using namespace std;

#define DEFAULT_SEED 42

deque<uint32_t> congruentialRNG(uint32_t a, uint32_t b, uint32_t c, uint32_t n, uint32_t x);
deque<double> rdn(int n, int x = DEFAULT_SEED);
deque<int> sample(int n, deque<double> prob = {0.5}, int x = DEFAULT_SEED);
template <class numeric>
void printFrequencyTable(deque<numeric> list);
template <class numeric>
deque<int> discretizeList(deque<numeric> list, deque<double> partition);


int main(int argc, char **argv)
{
    deque<int> rngStream;
    if(argc == 2)
    {
        rngStream = sample(atoi(argv[1]), {0.25, 0.5, 0.75});
    }
    if(argc == 3)
    {
        rngStream = sample(atoi(argv[1]), {0.25, 0.5, 0.75}, atoi(argv[2]));
    }

    printFrequencyTable(rngStream);

    return 0;
}


deque<uint32_t> congruentialRNG(uint32_t a, uint32_t b, uint32_t c, uint32_t n, uint32_t seed)
{
    deque<uint32_t> CRNGStream (1, seed);
    for(int i = 1; i < n; i++) //the zeroth entry is the seed
    {
        uint32_t nextElement = ((a*CRNGStream.front())+b) % c;
        CRNGStream.push_front(nextElement);
    }
    return CRNGStream;
}


deque<double> rdn(int n, int seed)
{
    //These are the parameters on the IBM System 360's RNG
    uint32_t a = pow(7,5);
    uint32_t c = pow(2,31)-1;
    deque<uint32_t> CRNGStream = congruentialRNG(a, 0, c, n, seed);

    deque<double> RNGStream;

    for(int element: CRNGStream)
    {
        RNGStream.push_front(((double) element)/c);
    }
    return RNGStream;
}


deque<int> sample(int n, deque<double> prob, int seed)
{
    deque<double> RNGStream = rdn(n, seed);
    prob.push_front(0);
    prob.push_back(1); //put endcaps on the probability vector

    deque<int> sampleStream = discretizeList(RNGStream, prob);
    return sampleStream;
} 


template <class numeric>
deque<int> discretizeList(deque<numeric> list, deque<double> partition)
{
    deque<int> outputList;
    for(numeric element: list)
    {
        for(int i = 0; i < partition.size(); i++)
        {
            if(partition.at(i) <= element && partition.at(i+1) > element)
            {
                outputList.push_front(i);
            }
        }
    }
    return outputList;
}


template <class numeric>
void printFrequencyTable(deque<numeric> list)
{
    map<numeric, int> table;
    for(numeric item: list)
    {
        if(table.find(item) != table.end())
        {
            table.at(item)++;
        }
        else
        {
            table.insert(pair<numeric, int>(item, 1));
        }
    }
    for(auto& item: table)
    {
        cout << item.first << ": " << item.second << "\n";
    }
}