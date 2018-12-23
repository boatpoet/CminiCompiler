#include <string>
using namespace std;
class Quaternion
{
public:
    string *quat; //Quaternion
    int quatNum; //Number of Quaternion - 1
    int stringNum; //stringNum = (quatNum+1)*4
    int blockNum; //Number of base blocks
    int *blockMarkPoint; //Marker for the begin and end of each base block
    bool *flag; //Mark whether this quaternion should be optimized
    string *newQuat; //New Quaternion
    int newQuatNum; //Nember of NewQuaternion
    Quaternion(string fileName);
    ~Quaternion();
    void readFromFile(string fileName);
    void devideBasicBlock();
    bool stringIsOpera(string str);
    void dag();
    int registerVariableLink(int head, int tail);
    void updateFourFormula();
};