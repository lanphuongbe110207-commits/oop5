#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<cstdlib>

using namespace std;


int readInt(const string& prompt, int lo, int hi){
    int x;
    while(true){
        cout << prompt;
        if(cin >> x && x >= lo && x <= hi) return x;
        if(cin.eof()){
            cout << "\n  -> Out of input, end this program\n";
            exit(0);
        }
        cout << "  -> Enter the positive integer [" << lo << ", " << hi << "]\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

double readDouble(const string& prompt, double lo){
    double x;
    while(true){
        cout << prompt;
        if(cin >> x && x >= lo) return x;
        if(cin.eof()){
            cout << "\n  -> Run out of storage memmory to input, end this program\n";
            exit(0);
        }
        cout << "  -> Enter the number >= " << lo << "\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

int readCommitMonth(){
    int m;
    while(true){
        cout << "Commit month (0 = on-demand, 12, 36): ";
        if(cin >> m && (m == 0 || m == 12 || m == 36)) return m;
        if(cin.eof()){
            cout << "\n  -> Run out of storage memmory to input, end this program \n";
            exit(0);
        }
        cout << "  -> Just accept 0, 12 hoac 36\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

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
    int getCount() const{
        int Count = 0;
        while(Count<100 && type[Count] != "") Count++;
        return Count;
    }
    float getCPU(int i) const{ return cpu[i];}
    double getRam(int i) const{ return ram[i];}
    double getPricePerHour(int i) const{ return pricePerHour[i];}
    string getType(int i) const{ return type[i];}
    double calculatePrice(int i, double hours = 730.0) const{
        return pricePerHour[i] * hours;
    }
    

   

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
int getCount() const{
    int Count =0;
    while(Count<100 && type[Count] != "") Count++;
    return Count;
}
double getCapacity(int i) const{ return capacity[i];}
string getType(int i) const{ return type[i];}
double getPricePerGB(int i) const{return pricePerGB[i];}
double calculateStorageCost(int i, double gb) const{
    return pricePerGB[i] * gb;
}
};


class Network{
protected :
    double dataTransfer[100];
    double pricePerGB[100];
    string type[100];
    
public : 
Network(){
    for(int i=0;i<100;i++){
        dataTransfer[i] = 0.0;
        pricePerGB[i] = 0.0;
        type[i] ="";
        
    }
}
virtual ~Network() = default;
virtual ResourceType getResourceType() const = 0;

int getCount() const{
        int Count = 0;
        while(Count<100 && type[Count] != "") Count++;
        return Count;
    }

    double getDataTransfer(int i) const{return dataTransfer[i]; }
    double getPricePerGB (int i) const{return pricePerGB[i];}
    string getType(int i) const {return type[i];}


    double transferCost(double gb) const{
        if(gb<=0) return 0.0;
        double cost = 0.0;
        double prev =0.0;
        int n = getCount();
        for(int i=0; i< n; i++){
            double upper = getDataTransfer(i);
            double part;
            if(i== n-1) part = gb - prev;
            else part =(gb<upper ? gb : upper)-prev;
            if(part>0) cost+= part*getPricePerGB(i);
            prev = upper;
            if(i<n-1&&gb<=upper) break;

        }
        return cost;
    }


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
    double effectiveDiscount(int i) const{
        return (discount[i] < MaxDiscount[i] ? discount[i] : MaxDiscount[i]);
    }
    double applyChosen(double price) const{
        if(chosen<0) return price;
        return price * (1.0 - effectiveDiscount(chosen));
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
            if(chosen ==-1 || effectiveDiscount(i) > effectiveDiscount(chosen)) chosen = i;
    }
    return chosen;

}
double optimize(double price, ResourceType resourceType, int CommitMonth, bool allowSpot, bool stableWorkload){
    FindBestDiscount(resourceType, CommitMonth, allowSpot, stableWorkload);
    return calculateDiscount(price);
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
  
    int CommitMonth;
    bool AllowSpot;
    bool StableWorkload;

public : 
void input(){
    cpu            = readDouble("CPU (>=1): ", 1);
    ram            = readDouble("RAM GB (>=1): ", 1);
    capacity       = readDouble("Storage GB (>=1): ", 1);
    dataTransfer   = readDouble("Data transfer GB (>=0): ", 0);
    CommitMonth    = readCommitMonth();
    AllowSpot      = readInt("Spot instance? (1=yes, 0=no): ", 0, 1);
    StableWorkload = readInt("Stable workload? (1=yes, 0=no): ", 0, 1);
}
int getMonth() const{return CommitMonth;}
bool getSpot() const{return AllowSpot;}
bool getWorkload() const{ return StableWorkload;}
float getCPU() const { return cpu;}
double getRam() const {return ram;}
double getCapacity() const{return capacity;}
double getDataTransfer() const{return dataTransfer;}
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
        // Nguon: https://aws.amazon.com/ec2/pricing/on-demand/ (us-east-1, 23/10/2026)
        // Nguong luong ke, don vi GB.
        type[0] = "0-100GB";
        dataTransfer[0] = 100;
        pricePerGB[0] = 0.000;

        type[1] = "100GB-10TB";
        dataTransfer[1] = 10240;
        pricePerGB[1] = 0.090;

        type[2] = "10-50TB";
        dataTransfer[2] = 51200;
        pricePerGB[2] = 0.085;

        type[3] = "50-150TB";
        dataTransfer[3] = 153600;
        pricePerGB[3] = 0.070;

        type[4] = "150TB+";
        dataTransfer[4] = 512000;
        pricePerGB[4] = 0.050;
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
        // Nguon: https://cloud.google.com/vpc/network-pricing (Premium Tier, us-central1, 23/10/2026)
        type[0] = "0-1GB";
        dataTransfer[0] = 1;
        pricePerGB[0] = 0.000;

        type[1] = "1GB-1TB";
        dataTransfer[1] = 1024;
        pricePerGB[1] = 0.120;

        type[2] = "1-10TB";
        dataTransfer[2] = 10240;
        pricePerGB[2] = 0.110;

        type[3] = "10TB+";
        dataTransfer[3] = 512000;
        pricePerGB[3] = 0.080;
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
        // Nguon: https://azure.microsoft.com/en-us/pricing/details/bandwidth/
        // (Internet Egress, North America/Europe, 23/10/2026). 1 TB = 1000 GB.
        type[0] = "0-100GB";
        dataTransfer[0] = 100;
        pricePerGB[0] = 0.000;

        type[1] = "100GB-10TB";
        dataTransfer[1] = 10100;
        pricePerGB[1] = 0.087;

        type[2] = "10-50TB";
        dataTransfer[2] = 51000;
        pricePerGB[2] = 0.083;

        type[3] = "50-150TB";
        dataTransfer[3] = 151000;
        pricePerGB[3] = 0.070;

        type[4] = "150TB+";
        dataTransfer[4] = 501000;
        pricePerGB[4] = 0.050;
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

struct cloudPlan{
    string cloud;
    string instance;
    int instanceCount = 0;
    string disk;
    int diskCount = 0;
    double rawCompute = 0.0;
    double computeCost = 0.0;
    double storageCost = 0.0;
    double networkCost = 0.0;
    double totalCost = 0.0;
    bool feasible = false;
};


// Scale out: 1 ycau co the duoc dap ung boi NHIEU may nho
// (tong CPU / RAM cua cac may >= yeu cau), chu khong can bat buoc nua
// phai co mot may don le du lon.
// ycau nay dc dung phong truong hop gb qua lon o tung class

struct ComputePlan{
    int cnt[100];       
    int total;          
    double rawCost;    
    bool found;

    ComputePlan(){
        for(int i = 0; i < 100; i++) cnt[i] = 0;
        total = 0;
        rawCost = 0.0;
        found = false;
    }
};
// tim ra to hop may re nhat, duyet so luong may i r ket hop voi may j de bo sung cho truong hop cin thieu
// da so voi bai nay thi cpu, ram la  bi rang buoc nen thuong dung 2 loai may

ComputePlan findCheapestMix(const Compute* c, double needCpu, double needRam){
    ComputePlan best;
    int m = c->getCount();
    if(m == 0) return best;

    for(int i = 0; i < m; i++){
        double cpuI = c->getCPU(i);
        double ramI = c->getRam(i);
        if(cpuI <= 0 || ramI <= 0) continue;

        
        double coverI = max(needCpu / cpuI, needRam / ramI);
        long long nmax = (long long)ceil(coverI < 0 ? 0.0 : coverI);
        if(nmax > 20000) nmax = 20000;      // ngan dlieu phi ly
        for(long long k = 0; k <= nmax; k++){
            double remCpu = needCpu - k * cpuI;
            double remRam = needRam - k * ramI;

            for(int j = 0; j < m; j++){
                double cpuJ = c->getCPU(j);
                double ramJ = c->getRam(j);
                if(cpuJ <= 0 || ramJ <= 0) continue;

                long long nj = 0;
                if(remCpu > 0) nj = max(nj, (long long)ceil(remCpu / cpuJ));
                if(remRam > 0) nj = max(nj, (long long)ceil(remRam / ramJ));

                long long total = k + nj;
                if(total <= 0) continue;

                double cost = k * c->getPricePerHour(i) + nj * c->getPricePerHour(j);

                bool better = !best.found
                           || cost < best.rawCost - 1e-9
                           || (fabs(cost - best.rawCost) <= 1e-9 && total < best.total);
                if(better){
                    best.found = true;
                    best.rawCost = cost;
                    best.total = (int)total;
                    for(int t = 0; t < 100; t++) best.cnt[t] = 0;
                    best.cnt[i] += (int)k;
                    best.cnt[j] += (int)nj;
                }
            }
        }
    }
    return best;
}

string describeInstances(const Compute* c, const ComputePlan& plan){
    string s;
    for(int i = 0; i < c->getCount(); i++){
        if(plan.cnt[i] <= 0) continue;
        if(!s.empty()) s += " + ";
        s += c->getType(i);
        if(plan.cnt[i] > 1) s += " x" + to_string(plan.cnt[i]);
    }
    if(s.empty()) s = "-";
    return s;
}

cloudPlan evaluate(CloudFactory* f, const Requirement& req, const string& cloudName){
    cloudPlan p;
    p.cloud = cloudName;

    Compute* c = f->createCompute();
    Storage* s = f->createStorage();
    Network* n = f->createNetwork();
    Discount* d = f->createDiscount();

    ComputePlan mix = findCheapestMix(c, req.getCPU(), req.getRam());
    if(!mix.found){
        p.feasible = false;
        delete c; delete s; delete n; delete d;
        return p;
    }
    p.instance = describeInstances(c, mix);
    p.instanceCount = mix.total;
// tim loai dia re nhat, neu ko du dung thi lay them nhieu dia cung loai (van uu tien chi phi)
    
    int bestS = -1;
    for(int i = 0; i < s->getCount(); i++){
        if(bestS == -1
           || s->getPricePerGB(i) < s->getPricePerGB(bestS) - 1e-12
           || (fabs(s->getPricePerGB(i) - s->getPricePerGB(bestS)) <= 1e-12
               && s->getCapacity(i) > s->getCapacity(bestS))){
            bestS = i;
        }
    }
    if(bestS == -1){
        p.feasible = false;
        delete c; delete s; delete n; delete d;
        return p;
    }

    double diskCap = s->getCapacity(bestS);
    int diskCount = diskCap > 0 ? (int)ceil(req.getCapacity() / diskCap) : 1;
    if(diskCount < 1) diskCount = 1;

    p.disk = s->getType(bestS);
    if(diskCount > 1) p.disk += " x" + to_string(diskCount);
    p.diskCount = diskCount;

    double RawCompute = mix.rawCost * 730.0;
    p.computeCost = d->optimize(RawCompute, ResourceType:: Compute, req.getMonth(),req.getSpot(), req.getWorkload());
    p.rawCompute = RawCompute;
    p.storageCost = s->calculateStorageCost(bestS, req.getCapacity());
    p.networkCost = n-> transferCost(req.getDataTransfer());
    p.totalCost = p.computeCost + p.storageCost + p.networkCost;
    p.feasible = true;

    delete c; delete s; delete n; delete d;
    return p;
}

void printPlans(const cloudPlan plans[], int n){
    int wInst = 18;
    for(int i = 0; i < n; i++){
        if(plans[i].feasible && (int)plans[i].instance.size() + 2 > wInst)
            wInst = (int)plans[i].instance.size() + 2;
    }

    cout << "\n" << left
         << setw(8)  << "Cloud"
         << setw(wInst) << "Instance"
         << setw(5)  << "Qty"
         << setw(18) << "Disk"
         << right
         << setw(10) << "Compute"
         << setw(10) << "Storage"
         << setw(10) << "Network"
         << setw(10) << "Saving"
         << setw(10) << "TOTAL" << "\n";

    for(int i = 0; i < n; i++){
        if(!plans[i].feasible){
            cout << left << setw(8) << plans[i].cloud
                 << "There is not configuration to satisfy you\n";
            continue;
        }
        cout << left  << setw(8)  << plans[i].cloud
             << setw(wInst) << plans[i].instance
             << setw(5)  << plans[i].instanceCount
             << setw(18) << plans[i].disk
             << right << fixed << setprecision(2)
             << setw(10) << plans[i].computeCost
             << setw(10) << plans[i].storageCost
             << setw(10) << plans[i].networkCost
             << setw(10) << (plans[i].rawCompute - plans[i].computeCost)
             << setw(10) << plans[i].totalCost << "\n";
    }
}

int main(){
    AWSFactory aws;
    GCPFactory gcp;
    AzureFactory azure;

    while(true){
        cout << "\n===== CLOUD COST OPTIMIZER =====\n"
             << "1. Find the best optimized option\n"
             << "0. out\n"
             << "choose: ";

        int choice;
        if(!(cin >> choice)){
            if(cin.eof()) break;
            cout << "  -> Enter 1 or 0\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        if(choice == 0) break;
        if(choice != 1){
            cout << "  -> Just 1 or 0\n";
            continue;
        }

        Requirement req;
        req.input();

        cloudPlan plans[3] = {
            evaluate(&aws,   req, "AWS"),
            evaluate(&gcp,   req, "GCP"),
            evaluate(&azure, req, "Azure")
        };

        printPlans(plans, 3);

        int best = -1;
        for(int i = 0; i < 3; i++){
            if(!plans[i].feasible) continue;
            if(best == -1 || plans[i].totalCost < plans[best].totalCost) best = i;
        }

        if(best == -1){
            cout << "\nThere is not cloud to satisfy you\n";
        } else {
            double save = plans[best].rawCompute - plans[best].computeCost;
            double pct  = plans[best].rawCompute > 0 ? save / plans[best].rawCompute * 100.0 : 0.0;
            cout << "\n-> Should be chosen: " << plans[best].cloud
                 << " (" << plans[best].instance << ")\n"
                 << "   The number of Computer: " << plans[best].instanceCount << "\n"
                 << "   Total: " << fixed << setprecision(2) << plans[best].totalCost << " USD/month\n"
                 << "   Amount of compute saving: " << save << " USD ("
                 << setprecision(1) << pct << "%)\n";
        }
    }

    cout << "Bye aem\n";
    return 0;
}
