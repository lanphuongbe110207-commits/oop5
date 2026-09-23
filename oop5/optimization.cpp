#include<iostream>
using namespace std;
class compute{
protected :
    int cpu;
    double ram;
    double pricePerHour;
public:
compute(){
    cpu = 0;
    ram =0.0;
    pricePerHour = 0.0;
};

};
class Storage{
protected :
    double capacity;
    double pricePerGB;

};
class Network{
protected :
    double dataTransfer;
    double pricePerGB;
public :
};

class CloudFactory {
public : 
    virtual compute* createCompute()= 0;
    virtual Storage* createStorage() = 0;
    virtual Network* createNetwork() = 0; 



};
class AWSFactory : public CloudFactory{
    public : 
    compute* createCompute() override {
        

    }
};
    




int main(){
}