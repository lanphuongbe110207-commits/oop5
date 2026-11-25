#include<bits/stdc++.h>
using namespace std;

class VEHICLE{
    protected:
    string License_Plate;
    string Brand;
    double Rental_Fee;
    static int Total;
    public:
    VEHICLE(string p, string b, double f):
    License_Plate(p), Brand(b), Rental_Fee(f){Total++;}
    VEHICLE():
    License_Plate(""), Brand(""), Rental_Fee(0.00){Total++;}
    ~VEHICLE(){Total--;}
    virtual void input(){
        cout<<"Enter License Plate: ";
        getline(cin>>ws,License_Plate);
        cout<<"Enter the Brand: ";
        getline(cin>>ws, Brand);
        
    }

    bool operator >(const VEHICLE& o) const {
        return Rental_Fee > o.Rental_Fee;
    }

    virtual double calculateRental() = 0;
    static int getTotal(){
        return Total;
    }



};
int VEHICLE :: Total = 0;
// kieu tra ve- toan tu pham vi - ten bien - gia tri gan

class Tourist: public VEHICLE{
    protected:
    int Seat_Count;
    double Service_Factor;
    double Base_Rate;
    public:
    Tourist(string p, string b, double f, int c, double s, double r):
    VEHICLE(p, b, f),
    Seat_Count(c), Service_Factor(s), Base_Rate(r){}

    Tourist():
    VEHICLE(), Seat_Count(0), Service_Factor(0.00), Base_Rate(0.00){}

    virtual ~Tourist(){}


    double calculateRental() override{
        return Rental_Fee = (Seat_Count * Service_Factor) * Base_Rate;
    }
};

class Cargo : public VEHICLE{
    protected:
    double Tonnage;
    double Distance_Coefficient;
    double Base_Rate;
    public:
    Cargo(string p, string b, double f,double t, double d, double r):
    VEHICLE(p, b, f), Tonnage(t), Distance_Coefficient(d), Base_Rate(r){}

    Cargo():
    VEHICLE(), Tonnage(0.00), Distance_Coefficient(0.00), Base_Rate(0.00){}

    virtual ~Cargo(){}

    double calculateRental() override{
        return Rental_Fee = Tonnage * Distance_Coefficient * Base_Rate;
    }


};

struct Node{
    
}

class VehicleList {

}

int main(){

    return 0;
}