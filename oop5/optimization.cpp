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
public : 
Storage(){
    capacity = 0.0;
    pricePerGB = 0.0;
}

};
class Network{
protected :
    double dataTransfer;
    double pricePerGB;
public :
Network(){
    dataTransfer = 0.0;
    pricePerGB = 0.0;
}
};

class Requirement{
private : 
int cpu;
    double ram;
    double pricePerHour;
    double capacity;
    double pricePerGB;
    double dataTransfer;
    double pricePerGB;
public : 
void input(){
    cout<<"Enter CPU :";
    cin >> cpu;
    cout<<"Enter ram";
    cin >> ram;
    cout <<"Enter capaccity";
    cin >> capacity;
    cout <<"Enter Data Tranfer";
    cin >> dataTransfer;
}
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