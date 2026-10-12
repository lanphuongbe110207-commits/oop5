#include<iostream>
using namespace std;
class Compute{
protected :
    int cpu[100];
    double ram[100];
    double pricePerHour[100];
    string type[100];
    
public:
Compute(){
    for(int i=0;i<100;i++){
        cpu[i] = 0;
        ram[i] = 0.0;
        pricePerHour[i] = 0.0;
        type[i] = "";
        
    }
    virtual ~Compute() = default;
   
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

virtual ~Price() = default;

};
class Storage{
protected :
    double capacity[100];
    string type[100];
    double pricePerGB[100];
    
public : 
Storage(){
    for(int i=0;i<100;i++){
        capacity[i] = 0.0;
        type[i] = "";
        pricePerGB[i] = 0.0;
    }
}

virtual ~Storage() = default;

};
class Network{
protected :
    double dataTransfer[100];
    double pricePerGB[100];
    
public : 
Network(){
    for(int i=0;i<100;i++){
        dataTransfer[i] = 0.0;
        pricePerGB[i] = 0.0;
        
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
        type[0] = "c6i.large";
        cpu[0] = 2;
        ram[0] = 4.0;
        pricePerHour[0] = 0.085;
        
        type[1] = "c6i.xlarge";
        cpu[1] = 4;
        ram[1] = 8.0;
        pricePerHour[1] = 0.170;

        type[2] = "c6i.2xlarge";
        cpu[2] = 8;
        ram[2] = 16.0;
        pricePerHour[2] = 0.340;

        type[3] = "c6i.4xlarge";
        cpu[3] = 16;
        ram[3] = 32.0;
        pricePerHour[3] = 0.680;

        type[4] = "c6i.8xlarge";
        cpu[4] = 32;
        ram[4] = 64.0;
        pricePerHour[4] = 1.360;

        type[5] ="m6i.large";
        cpu[5] = 2;
        ram[5] = 8.0;
        pricePerHour[5] = 0.096;

        type[6] = "m6i.xlarge";
        cpu[6] = 4;
        ram[6] = 16.0;
        pricePerHour[6] = 0.192;

        type[7] = "m6i.2xlarge";
        cpu[7] = 8;
        ram[7] = 32.0;
        pricePerHour[7] = 0.384;

        type[8] = "m6i.4xlarge";
        cpu[8] = 16;
        ram[8] = 64.0;
        pricePerHour[8] = 0.768;

        type[9] = "m6i.8xlarge";
        cpu[9] = 32;
        ram[9] = 128.0;
        pricePerHour[9] = 1.536;

        type[10] = "r6i.large";
        cpu[10] = 2;
        ram[10] = 16.0;
        pricePerHour[10] = 0.126;

        type[11] = "r6i.xlarge";
        cpu[11] = 4;
        ram[11] = 32.0;
        pricePerHour[11] = 0.252;

        type[12] = "r6i.2xlarge";
        cpu[12] = 8;
        ram[12] = 64.0;
        pricePerHour[12] = 0.504;

        type[13] = "r6i.4xlarge";
        cpu[13] = 16;
        ram[13] = 128.0;
        pricePerHour[13] = 1.008;

        type[14] = "r6i.8xlarge";
        cpu[14] = 32;
        ram[14] = 256.0;
        pricePerHour[14] = 2.016;
    }
    // cac gia tren duoc xac dinh theo quy mo, dua vao instance, muc on-demand duoc aws cong bo

};

class AWSStorage : public Storage{
    public :
    AWSStorage(){
type[0] = "gp3";
capacity[0] = 50;
pricePerGB[0] = 0.08;

type[1] = "gp3";
capacity[1] = 100;
pricePerGB[1] = 0.08;

type[2] = "gp3";
capacity[2] = 500;
pricePerGB[2] = 0.08;

type[3] = "gp3";
capacity[3] = 1024;
pricePerGB[3] = 0.08;

type[4] = "gp2";
capacity[4] = 50;
pricePerGB[4] = 0.10;

type[5] = "gp2";
capacity[5] = 100;
pricePerGB[5] = 0.10;

type[6] = "gp2";
capacity[6] = 500;
pricePerGB[6] = 0.10;

type[7] = "gp2";
capacity[7] = 1024;   
pricePerGB[7] = 0.10;

type[8] = "io2";
capacity[8] = 50;
pricePerGB[8] = 0.125;


type[9] = "io2";
capacity[9] = 1024;  
pricePerGB[9] = 0.125; 
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
class AWSNetwork : public Network{
    public :
    AWSNetwork(){
        dataTransfer[0] = 1.0;
        dataTransfer[1] = 10.0;
        dataTransfer[2] = 100.0;
        dataTransfer[3] = 1000.0;
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