class Main: public CBase_Main {
    private: 
    int stepCount;

    public:
        Main(CkArgMsg* msg);
        void done();
        void checkIn();

};

class Primality: public CBase_Primality{
    private: 
    std::vector<int> primeNum;

    public:  
        Primer();
        void isPrime();
        void sendData(std::vector<int> sec);
        
};