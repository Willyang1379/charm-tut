#include <vector>
#include <cstdlib>
#include <utility>
#include "primality.decl.h"
using namespace std;

CProxy_Main mainProxy;
CProxy_Primality primeProxy;
int numChares; 
int primeNums;
double startTime;
double endTime;

class Main : public CBase_Main
{
public:
  Main(CkArgMsg* m)
  {
    //fire up main chare and subchares, also create storage array
    mainProxy = thisProxy;
    primeNums = atoi(m->argv[1]);
    numChares = primeNums/4;
    primeProxy = CProxy_Primality::ckNew(numChares);
    stepCount = 0;
    startTime = CkTimer();

    //loop through K times and add to prime number array, once the array is full, let subchare compute primality
    int count = 0;
    vector <int> section;
    for (int i = 0; i < primeNums; i++) {
        int number = rand();
        section.push_back(number);
        if (section.size() % numChares == 0) {
          primeProxy[count++].sendData(section);
          section.clear();
        }
    primeProxy.isPrime(); 
    }
  };

  void done()
  {
    // Finish computation
    CkPrintf("All done.\n");
    CkExit();
  };

  void checkIn() {
    stepCount++;
    if (stepCount == numChares) {
      endTime = CkTimer();
      done();
    }
  }
};


class Primality : public CBase_Primality {
  public:
    Primality() {}

  void isPrime() {
    // calculate whether the number sent is prime, then check in with main proxy
    vector <pair<int, const char*>> finalArray;
    for (int i = 0; i < primeNum.size(); i++) {
      int isPrime = 1;
      if(primeNum[i]<=1) {
        isPrime = 0;
      }

      for(int i=2; i<primeNum[i]; i++)
      {
        if (0 == primeNum[i]%i)
        isPrime = 0;
      }
      if (isPrime == 1) {
        finalArray.push_back(pair<int, const char*>(primeNum[i], "True"));
      } else {
        finalArray.push_back(pair<int, const char*>(primeNum[i], "False"));
      }
    }
    for (int i = 0; i < finalArray.size(); i++) {
        CkPrintf("Integer %d is Prime: %s.\n", finalArray[i].first, finalArray[i].second);
    }
    mainProxy.checkIn();
  }

  void sendData(vector<int> section) {
    primeNum = section;
  }

};

#include "primality.def.h"