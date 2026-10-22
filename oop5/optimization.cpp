#include<iostream>
#include<string>

using namespace std;
enum class ResourceType{
    
    Compute =0,
    Serverless,
    Storage,
    Database,
    Container,
    Network
};
class Compute{
protected :
    float cpu[100];
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
}
    virtual ResourceType getResourceType() const = 0;
    virtual ~Compute() = default;

   

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
virtual ResourceType getResourceType() const = 0;

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
virtual ResourceType getResourceType() const = 0;
};
class Discount{
    protected:
    float discount[100];
    float MaxDiscount[100];
    int month[100];
    string type[100];
    int OrderOfType[100];
    ResourceType ResourceKind[100];
    bool isApplicable[100];
    bool Spot[100];
    bool Workload[100];
    int Count;
    int chosen;
    double applyChosen(double price) const{
        if(chosen<0) return price;
        return price * (1.0 - discount[chosen]);
    }

    public : 
    Discount(){
        for (int i=0; i<100; i++){
            discount[i] = 0.0;
            month[i] = 0;
            type[i] = "";
            OrderOfType[i] = 0;
            ResourceKind[i] = ResourceType::Compute;
            
            isApplicable[i] = false;
            MaxDiscount[i] = 0.0;
            Spot[i] = false;
            Workload[i] = false;
        }
        Count = 0;
        chosen = -1;
    }
    void add(string discountType, float discountValue, int month, ResourceType resourceType, bool isApplicable, int orderOfType, bool Spot, bool Workload, float MaxDiscount){
        for(int i=0;i<100;i++){
            if(type[i] == ""){
                type[i] = discountType;
                discount[i] = discountValue;

                this-> MaxDiscount[i] = MaxDiscount;
                
                this->month[i] = month;
                ResourceKind[i] = resourceType;
                this->isApplicable[i] = isApplicable;
                OrderOfType[i] = orderOfType;
                this->Spot[i] = Spot;
                this->Workload[i] = Workload;
                Count++;
                break;
            }
        }
    }
    int FindBestDiscount(ResourceType resourceType, int CommitMonth, bool allowSpot, bool stableWorkload){
        chosen = -1;
        for(int i =0; i<Count; i++){
            if(!isApplicable[i])  continue;
            if(ResourceKind[i] != resourceType) continue;
            if(Spot[i] &&  !allowSpot)  continue;
            if(Workload[i] &&  !stableWorkload) continue;
            if(month[i] > 0 && CommitMonth<month[i] ) continue;
            if(chosen ==-1 || discount[i] > discount[chosen]) chosen = i;
    }
    return chosen;

}
    virtual double calculateDiscount(double price) = 0;

    virtual ~Discount() = default;
};

class Requirement{
    protected : 
float cpu;
    double ram;
    
    double capacity;
   
    double dataTransfer;
  
    float importanceCPU;
    float importanceRam;
    float importancecapacity;
    float importanceDataTranfer;
    int CommitMonth;
    bool AllowSpot;
    bool StableWorkload;

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
    cout <<"Enter month";
    cin >> CommitMonth;
    cout <<"Is it a spot instance? (1 for yes, 0 for no)";
    cin >> AllowSpot;
    cout <<"Is it a workload instance? (1 for yes, 0 for no)";
    cin >> StableWorkload;

    float sum;
    while(true){
    cout<<"Enter your percentage of importance for CPU";
    cin >>importanceCPU;
    cout<<"Enter your percentage of importance for Ram";
    cin >>importanceRam;

    cout<<"Enter your percentage of importance for Capacity";
    cin >>importancecapacity;

    cout<<"Enter your percentage of importance for Data Transfer";
    cin >>importanceDataTranfer;
    sum = importanceCPU + importanceRam + importancecapacity + importanceDataTranfer;
    if(sum == 100) break;
    cout<<"Please retype again. The percentage has to be equal to 100, please retype because yor sum is equal to "<< sum <<"\n";
    }
}
int getMonth() const{return CommitMonth;}
bool getSpot() const{return AllowSpot;}
bool getWorkload() const{ return StableWorkload;}
};

class CloudFactory {
public : 
    virtual Compute* createCompute()= 0;
    virtual Storage* createStorage() = 0;
    virtual Network* createNetwork() = 0; 
    virtual Discount* createDiscount() = 0;
    virtual ~CloudFactory() = default;



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
    ResourceType getResourceType() const override {
        return ResourceType::Compute;
    }

    

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
    ResourceType getResourceType() const override{
        return ResourceType::Storage;
    }
};

class AWSDiscount : public Discount{
    public :
    AWSDiscount(){
        add("On Demand", 0.00f, 0, ResourceType::Compute,true,1, false, false, 0.00f);
        add("Compute SP 3yr", 0.55f, 36,   ResourceType::Compute,true,2, false, true, 0.66f);
        add("Compute SP 1yr", 0.35f, 12,   ResourceType::Compute,true,3, false, true, 0.66f);
        add("EC2 Instance SP 3yr", 0.55f, 36,   ResourceType::Compute,true,4, false, true, 0.66f);
        add("Standard RI 3yr", 0.55f, 36, ResourceType::Compute, true, 5, false, true, 0.72f);
        add("Convertible RI 3yr", 0.48f, 36, ResourceType::Compute, true, 6, false, true, 0.66f);
        add("Database SP 1yr", 0.25f, 12, ResourceType::Database,true,7, false, true, 0.35f);
        add("RDS RI 3yr",   0.45f, 36,     ResourceType::Database,true,8, false, true, 0.60f);
        add("Spot",           0.65f, 0,      ResourceType::Compute,true,9, true, false, 0.90f);
        add("EDP",            0.15f, 0,      ResourceType::Compute,true,10, false, false, 0.20f);
        
    }
    double calculateDiscount(double price) override {
        return applyChosen(price);
    }
   
};
class AWSNetwork : public Network{
    public :
    AWSNetwork(){
        dataTransfer[0] = 1.0;
        pricePerGB[0] = 0.09;
        dataTransfer[1] = 10.0;
        pricePerGB[1] = 0.09;
        dataTransfer[2] = 100.0;
        pricePerGB[2] = 0.09;
        dataTransfer[3] = 1000.0;
        pricePerGB[3] = 0.09;
    }
    ResourceType getResourceType() const override {return ResourceType::Network;}
};  

class GCPCompute : public Compute{
    public:
    GCPCompute(){
        type[0] = "c3-highcpu-4";
        cpu[0] = 4;
        ram[0] = 8.0;
        pricePerHour[0] = 0.1701;

        type[1] = "c3-highcpu-8";
        cpu[1] = 8;
        ram[1] = 16.0;
        pricePerHour[1] = 0.3402;

        type[2] = "c3-highcpu-16";
        cpu[2] = 16;
        ram[2] = 32.0;
        pricePerHour[2] = 0.6804;

        type[3] = "c3-highcpu-22";
        cpu[3] = 22;
        ram[3] = 44.0;
        pricePerHour[3] = 0.9356;

        type[4] = "c3-highcpu-44";
        cpu[4] = 44;
        ram[4] = 88.0;
        pricePerHour[4] = 1.8711;

        type[5] = "e2-standard-2";
        cpu[5] = 2;
        ram[5] = 8.0;
        pricePerHour[5] = 0.0670;

        type[6] = "e2-standard-4";
        cpu[6] = 4;
        ram[6] = 16.0;
        pricePerHour[6] = 0.1340;

        type[7] = "e2-standard-8";
        cpu[7] = 8;
        ram[7] = 32.0;
        pricePerHour[7] = 0.2680;

        type[8] = "e2-standard-16";
        cpu[8] = 16;
        ram[8] = 64.0;
        pricePerHour[8] = 0.5361;

        type[9] = "e2-standard-32";
        cpu[9] = 32;
        ram[9] = 128.0;
        pricePerHour[9] = 1.0722;

        type[10] = "n2-highmem-2";
        cpu[10] = 2;
        ram[10] = 16.0;
        pricePerHour[10] = 0.1701;

        type[11] = "n2-highmem-4";
        cpu[11] = 4;
        ram[11] = 32.0;
        pricePerHour[11] = 0.3402;

        type[12] = "n2-highmem-8";
        cpu[12] = 8;
        ram[12] = 64.0;
        pricePerHour[12] = 0.6804;

        type[13] = "n2-highmem-16";
        cpu[13] = 16;
        ram[13] = 128.0;
        pricePerHour[13] = 1.3608;

        type[14] = "n2-highmem-32";
        cpu[14] = 32;
        ram[14] = 256.0;
        pricePerHour[14] = 2.7217;
    }
    ResourceType getResourceType() const override {
        return ResourceType::Compute;
    }
};

class GCPStorage : public Storage{
    public:
    GCPStorage(){
        type[0] = "pd-standard";
        capacity[0] = 50;
        pricePerGB[0] = 0.040;

        type[1] = "pd-standard";
        capacity[1] = 100;
        pricePerGB[1] = 0.040;

        type[2] = "pd-standard";
        capacity[2] = 500;
        pricePerGB[2] = 0.040;

        type[3] = "pd-standard";
        capacity[3] = 1024;
        pricePerGB[3] = 0.040;

        type[4] = "pd-balanced";
        capacity[4] = 50;
        pricePerGB[4] = 0.100;

        type[5] = "pd-balanced";
        capacity[5] = 100;
        pricePerGB[5] = 0.100;

        type[6] = "pd-balanced";
        capacity[6] = 500;
        pricePerGB[6] = 0.100;

        type[7] = "pd-balanced";
        capacity[7] = 1024;
        pricePerGB[7] = 0.100;

        type[8] = "pd-ssd";
        capacity[8] = 50;
        pricePerGB[8] = 0.170;

        type[9] = "pd-ssd";
        capacity[9] = 1024;
        pricePerGB[9] = 0.170;
    }
    ResourceType getResourceType() const override {
        return ResourceType::Storage;
    }
};

class GCPNetwork : public Network{
    public:
    GCPNetwork(){
        dataTransfer[0] = 1.0;
        pricePerGB[0] = 0.12;
        dataTransfer[1] = 10.0;
        pricePerGB[1] = 0.12;
        dataTransfer[2] = 100.0;
        pricePerGB[2] = 0.12;
        dataTransfer[3] = 1000.0;
        pricePerGB[3] = 0.12;
    }
    ResourceType getResourceType() const override {
        return ResourceType::Network;
    }
};

class GCPDiscount : public Discount{
    public :
    GCPDiscount(){
        add("On Demand",        0.00f,  0, ResourceType::Compute,  true, 1, false, false, 0.00f);
        add("Resource CUD 3yr", 0.55f, 36, ResourceType::Compute,  true, 2, false, true,  0.57f);
        add("Resource CUD 1yr", 0.37f, 12, ResourceType::Compute,  true, 3, false, true,  0.57f);
        add("Spend CUD 3yr",    0.28f, 36, ResourceType::Compute,  true, 4, false, true,  0.28f);
        add("SUD",              0.30f,  0, ResourceType::Compute,  true, 5, false, false, 0.30f);
        add("Spot",             0.40f,  0, ResourceType::Compute,  true, 6, true,  false, 0.60f);
        add("Database CUD 1yr", 0.25f, 12, ResourceType::Database, true, 7, false, true,  0.35f);
        add("Database CUD 3yr", 0.45f, 36, ResourceType::Database, true, 8, false, true,  0.60f);
    }
    double calculateDiscount(double price) override {
        return applyChosen(price);
    }
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
   
};

   

class GCPFactory : public CloudFactory{


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
    

};

class AzureCompute : public Compute{
    public:
    AzureCompute(){
        type[0] = "F2s_v2";
        cpu[0] = 2;
        ram[0] = 4.0;
        pricePerHour[0] = 0.0846;

        type[1] = "F4s_v2";
        cpu[1] = 4;
        ram[1] = 8.0;
        pricePerHour[1] = 0.1690;

        type[2] = "F8s_v2";
        cpu[2] = 8;
        ram[2] = 16.0;
        pricePerHour[2] = 0.3380;

        type[3] = "F16s_v2";
        cpu[3] = 16;
        ram[3] = 32.0;
        pricePerHour[3] = 0.6770;

        type[4] = "F32s_v2";
        cpu[4] = 32;
        ram[4] = 64.0;
        pricePerHour[4] = 1.3530;

        type[5] = "D2s_v5";
        cpu[5] = 2;
        ram[5] = 8.0;
        pricePerHour[5] = 0.0960;

        type[6] = "D4s_v5";
        cpu[6] = 4;
        ram[6] = 16.0;
        pricePerHour[6] = 0.1920;

        type[7] = "D8s_v5";
        cpu[7] = 8;
        ram[7] = 32.0;
        pricePerHour[7] = 0.3840;

        type[8] = "D16s_v5";
        cpu[8] = 16;
        ram[8] = 64.0;
        pricePerHour[8] = 0.7680;

        type[9] = "D32s_v5";
        cpu[9] = 32;
        ram[9] = 128.0;
        pricePerHour[9] = 1.5360;

        type[10] = "E2s_v5";
        cpu[10] = 2;
        ram[10] = 16.0;
        pricePerHour[10] = 0.1260;

        type[11] = "E4s_v5";
        cpu[11] = 4;
        ram[11] = 32.0;
        pricePerHour[11] = 0.2520;

        type[12] = "E8s_v5";
        cpu[12] = 8;
        ram[12] = 64.0;
        pricePerHour[12] = 0.5040;

        type[13] = "E16s_v5";
        cpu[13] = 16;
        ram[13] = 128.0;
        pricePerHour[13] = 1.0080;

        type[14] = "E32s_v5";
        cpu[14] = 32;
        ram[14] = 256.0;
        pricePerHour[14] = 2.0160;
    }
    ResourceType getResourceType() const override{
        return ResourceType:: Compute;
    }
};

class AzureStorage : public Storage{
    public:
    AzureStorage(){
        type[0] = "Standard HDD";
        capacity[0] = 128;
        pricePerGB[0] = 0.040;

        type[1] = "Standard HDD";
        capacity[1] = 256;
        pricePerGB[1] = 0.040;

        type[2] = "Standard HDD";
        capacity[2] = 512;
        pricePerGB[2] = 0.040;

        type[3] = "Standard HDD";
        capacity[3] = 1024;
        pricePerGB[3] = 0.040;

        type[4] = "Standard SSD";
        capacity[4] = 128;
        pricePerGB[4] = 0.075;

        type[5] = "Standard SSD";
        capacity[5] = 256;
        pricePerGB[5] = 0.075;

        type[6] = "Standard SSD";
        capacity[6] = 512;
        pricePerGB[6] = 0.075;

        type[7] = "Standard SSD";
        capacity[7] = 1024;
        pricePerGB[7] = 0.075;

        type[8] = "Premium SSD";
        capacity[8] = 128;
        pricePerGB[8] = 0.154;

        type[9] = "Premium SSD";
        capacity[9] = 1024;
        pricePerGB[9] = 0.132;
    }
    ResourceType getResourceType() const override {
        return ResourceType::Storage;
    }
};

class AzureNetwork : public Network{
    public:
    AzureNetwork(){
        dataTransfer[0] = 1.0;
        pricePerGB[0] = 0.087;
        dataTransfer[1] = 10.0;
        pricePerGB[1] = 0.087;
        dataTransfer[2] = 100.0;
        pricePerGB[2] = 0.087;
        dataTransfer[3] = 1000.0;
        pricePerGB[3] = 0.087;
    }
    ResourceType getResourceType() const override {
        return ResourceType::Network;
    }
};

class AzureDiscount : public Discount{
    public :
    AzureDiscount(){
        add("On Demand",          0.00f,  0, ResourceType::Compute,  true, 1, false, false, 0.00f);
        add("Savings Plan 3yr",   0.54f, 36, ResourceType::Compute,  true, 2, false, true,  0.65f);
        add("Savings Plan 1yr",   0.31f, 12, ResourceType::Compute,  true, 3, false, true,  0.65f);
        add("Reserved 3yr",       0.61f, 36, ResourceType::Compute,  true, 4, false, true,  0.72f);
        add("Reserved 1yr",       0.38f, 12, ResourceType::Compute,  true, 5, false, true,  0.72f);
        add("Spot",               0.79f,  0, ResourceType::Compute,  true, 6, true,  false, 0.90f);
        add("SQL DB Reserved 1yr",0.30f, 12, ResourceType::Database, true, 7, false, true,  0.40f);
        add("SQL DB Reserved 3yr",0.50f, 36, ResourceType::Database, true, 8, false, true,  0.60f);
    }
    double calculateDiscount(double price) override {
        return applyChosen(price);
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
   
};



    




int main(){
    return 0;
}