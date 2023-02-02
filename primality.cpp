#include <vector>
#include <cstdlib>
#include <utility>
using namespace std;

//ask about the purpose of main proxy, *know it is a way for system to recognize and track chares, is
// it necessary when we only have the main chare being deployed?
/*readonly*/ CProxy_Main mainProxy;
typedef vector <pair<int,bool>> storage;

class Main : public CBase_Main
{
public:
  Main(CkArgMsg* m)
  {
    mainProxy = thisProxy;
    // create K integers, create a pair(int,bool), have chare check primality, add to array
    storage array;
    pair<int,bool> integer;
    for (int i = 0, i < m; i++) {
        int num = rand();
        integer.first = num;
        if primer.check(num) {
          integer.second = true;
        } else {
          integer.second = false;
        }
        array.push_back(integer)
        // append onto array
    }
    //array should be filles, print and terminate main chare
    for (int i = 0; i < m; i++) {
      CkPrintf("Integer %d is Prime: %d.\n", array[i].first, array[i].second);
    }
    mainProxy.done();
  };

  void done()
  {
    // Finish computation
    CkPrintf("All done.\n");
    CkExit();
  };
};

class Primer : public CBase_Primer
{
  public:
    Primer() {}

  int isPrime(const long number) {
    if(number<=1) return 0;
    for(int i=2; i<number; i++)
    {
      if(0 == number%i)
      return 0;
    }
    return 1;
  }
};
