#include <vector>

using namespace std;

class StatsVector: protected vector<double>
{
    public:
        StatsVector(int x, int y);

        int front()
        {
            return (int) this->at(0);
        }
};