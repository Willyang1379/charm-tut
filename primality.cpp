#include <vector>
#include <cstdlib>
#include <utility>
#include "primality.decl.h"
using namespace std;

//ask about the purpose of main proxy, *know it is a way for system to recognize and track chares, is
// it necessary when we only have the main chare being deployed?
/*readonly*/ CProxy_Main mainProxy; 
/*readonly*/ int numChares; 
/*readonly*/ CProxy_Primer primeArray; 
int chareCount;
vector <pair<int, const char*>> finArr;

class Main : public CBase_Main
{
public:
  Main(CkArgMsg* m)
  {

    //fire up main chare and subchares, also create storage array
    chareCount = 0;
    mainProxy = thisProxy;
    int num = atoi(m->argv[1]);
    numChares = num;
    CProxy_Primer primeProxy = CProxy_Primer::ckNew(num);

    //loop through K times and call check prime method
    for (int i = 0; i < num; i++) {
        int num = rand();
        primeProxy[i].isPrime(num, i);
    }
  };

  void done()
  {
    // Finish computation
    CkPrintf("All done.\n");
    CkExit();
  };

  void checkIn(int isPrime, int id, int number) {
    chareCount += 1;
    if (isPrime == 1) {
      finArr.push_back(pair<int, const char*>(number, "True"));
    } else {
      finArr.push_back(pair<int, const char*>(number, "False"));
    }
    if (chareCount == numChares) { 
        //array should be filled, print and terminate main chare
      for (int i = 0; i < numChares; i++) {
        CkPrintf("Integer %d is Prime: %s.\n", finArr[i].first, finArr[i].second);
      }
      mainProxy.done(); }
  }
};

class Primer : public CBase_Primer {
  public:
    Primer() {}

  void isPrime(int number, int id) {
    // calculate whether the number sent is prime, then check in with main proxy
    int chareID = id;
    int isPrime = 1;

    if(number<=1) {
      isPrime = 0;
    }

    for(int i=2; i<number; i++)
    {
      if (0 == number%i)
      isPrime = 0;
    }
    mainProxy.checkIn(isPrime, chareID, number);
  }

};

#include "primality.def.h"