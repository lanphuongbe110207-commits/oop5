#include<iostream>
using namespace std;
class Compute{
protected :
    int cpu;
    double ram;
    double pricePerHour;
public:
Compute(){
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
class Discount{
    protected:
    float Dicount;
    int month;
    int year;
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
    float importanceCPU;
    float importanceRam;
    float importancecapacity;
    float importanceDataTranfer;

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
    cout<<"Enter your percentage of importance for CPU";
    cin >>importanceCPU;
    cout<<"Enter your percentage of importance for Ram";
    cin >>importanceRam;

    cout<<"Enter your percentage of importance for Capacity";
    cin >>importancecapacity;

    cout<<"Enter your percentage of importance for Data Transfer";
    cin >>importanceDataTranfer;


}
};

class CloudFactory {
public : 
    virtual compute* createCompute()= 0;
    virtual Storage* createStorage() = 0;
    virtual Network* createNetwork() = 0; 
    virtual Discount* createDiscount() = 0;



};
class AWSFactory : public CloudFactory{
    public : 
    Compute* createCompute() override {
        return new AWSCompute();
        

    }
    compute* createStorage() override{
        return new AWSStorage();
    }
};
    




int main(){
}