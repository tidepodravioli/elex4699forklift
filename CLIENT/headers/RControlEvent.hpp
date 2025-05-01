#include "../../headers/RControl.hpp"
#include <vector>

using namespace std;

class RControlEvent
{
    protected:

    public:
    RControlEvent(DATA_TYPE type, int value);
    RControlEvent(DATA_TYPE type, vector<int> values);

    
};