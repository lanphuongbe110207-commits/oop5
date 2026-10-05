#include<iostream>
using namespace std;
class Compute{
protected :
    int cpu[100];
    double ram[100];
    
public:
Compute(){
    for(int i=0;i<100;i++){
        cpu[i] = 0;
        ram[i] = 0.0;
        
    }
   
};

class Price{
    protected :
    double ComputepriceperHour[100];
    double StoragepricePerGB[100];
    double NetworkpricePerGB[100];
    public :
    Price(){
        for(int i =0; i<100;i++){
            ComputepriceperHour[i] = 0.0;
            StoragepricePerGB[i] = 0.0;
            NetworkpricePerGB[i] = 0.0;
        }
    }

virtual ~Compute() = default;

};
class Storage{
protected :
    double capacity[100];
    
public : 
Storage(){
    for(int i=0;i<100;i++){
        capacity[i] = 0.0;
        
    }
}

virtual ~Storage() = default;

};
class Network{
protected :
    double dataTransfer[100];
    
public : 
Network(){
    for(int i=0;i<100;i++){
        dataTransfer[i] = 0.0;
        
    }
}
virtual ~Network() = default;
};
class Discount{
    protected:
    float discount[100];
    int month[100];
    string type[100];
    int OrderOfType[100];
    
    
    public : 
    Discount(){
        discount[0] = 0.0;
        month[0] = 0;
        type[0] = "";
        OrderOfType[0] = 0;
    
    }
    virtual double calculateDiscount(double price) = 0;

    virtual ~Discount() = default;
};

class Requirement{
    protected : 
int cpu[100];
    double ram[100];
    
    double capacity[100];
   
    double dataTransfer[100];
  
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
    virtual Compute* createCompute()= 0;
    virtual Storage* createStorage() = 0;
    virtual Network* createNetwork() = 0; 
    virtual Discount* createDiscount() = 0;



};
class AWSFactory : public CloudFactory{
    public : 
    Compute* createCompute() override {
        return new AWSCompute();
        

    }
    Storage* createStorage() override{
        return new AWSStorage();
    }

    Network* createNetwork() override{
        return new AWSNetwork();

    }

    Discount* createDiscount() override{
        return new AWSDiscount();

    }
    Price* createPrice() override{
        return new AWSPrice();
    }
};

class AWSCompute : public Compute{
    public:
    AWSCompute(){
        cpu[0] = 2;
        ram[0] = 4.0;

        cpu[1] = 4;
        ram[1] = 8.0;

        cpu[2] = 8;
        ram[2] = 16.0;

        cpu[3] = 16;
        ram[3] = 32.0;

        cpu[4] = 32;
        ram[4] = 64.0;
    }

};

class AWSDiscount : public Discount{
    public :
    AWSDiscount(){
        type[0] = "On Demand";
        discount[0] = 0.0;
        OrderOfType[0]   = 1;

        type[1] ="Saving Plan";
        discount[1] = 0.0;
        OrderOfType[1] = 2;

        type[2]= "Reversed Instances";
        discount[2] = 0.0;
        OrderOfType[2] = 3;

        type[3] ="Spot";
        discount[3] = 0.0;
        OrderOfType[3] = 4;
    }
};      

class GCPFACTORY: public CloudFactory{
    public:
    Compute* createCompute()override {
        return new GCPCompute();
    }

    Storage* createStorage() override {
        return new GCPStorage();
    }

    Network* createNetwork()override {
        return new GCPNetwork();
    }

    Discount* createDiscount()override {
        return new GCPDiscount();
    }
    Price* createPrice() override{
        return new GCPPrice();
    }

};

class AzureFactory : public CloudFactory{
    public:
    Compute* createCompute() override {
        return new AzureCompute();
    }
    Storage* createStorage() override {
        return new AzureStorage();
    }
    Network* createNetwork() override{
        return new AzureNetwork();
    }

    Discount* createDiscount()override {
        return new AzureDiscount();
    }
    Price* createPrice() override{
        return new AzurePrice();
    }
};

class 

    




int main(){
    return 0;
}