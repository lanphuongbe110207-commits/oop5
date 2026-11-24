// De bai: CUSTOMER (Customer ID, Business Name, CPS) + Large/Small
// Input format (moi dong 1 gia tri):
//   n
//   type(1=Large,2=Small)
//   CustomerID
//   BusinessName
//   scale      cooperation     (neu type = 1)
//   demand     financial       (neu type = 2)
//   ... lap lai n lan
//
// Vi du:
//   3
//   1 CU001 "ABC Corp" 10 8
//   2 CU002 "XYZ Ltd" 7 9
//   1 CU003 "Big Co" 5 6
// (moi gia tri tren 1 dong, ten cong ty doc ca dong)

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// ===================== Q1 + Q2 + Q3: lop co so =====================
class CUSTOMER {
protected:
    string CustomerID;
    string BusinessName;
    double CPS;
    static int member;              // so khach hang dang ton tai

public:
    CUSTOMER() : CustomerID(""), BusinessName(""), CPS(0.0) { member++; }
    CUSTOMER(string id, string name)
        : CustomerID(id), BusinessName(name), CPS(0.0) { member++; }

    virtual ~CUSTOMER() { member--; }   // phai virtual: xoa qua con tro base

    // Q1: nhap ID + ten. Virtual de lop con mo rong (them tham so rieng)
    virtual void input() {
        getline(cin >> ws, CustomerID);
        getline(cin >> ws, BusinessName);
    }

    // Q1: xuat ID + ten (cot CPS in rieng de can phai)
    void display() const {
        cout << left << setw(16) << CustomerID << setw(28) << BusinessName;
    }

    // Q4: moi lop con tu tinh CPS
    virtual double calculateCPS() = 0;

    double getCPS() const { return CPS; }

    // Q3: so sanh 2 khach hang theo CPS (dat o base => so duoc Large voi Small)
    bool operator<(const CUSTOMER& other) const { return CPS < other.CPS; }

    // Q2: trung binh CPS cua ca danh sach
    static double averageCPS(CUSTOMER* ds[], int n) {
        if (n <= 0) return 0.0;
        double sum = 0.0;
        for (int i = 0; i < n; i++) sum += ds[i]->getCPS();
        return sum / n;
    }

    static int getCount() { return member; }
};

int CUSTOMER::member = 0;

// ===================== Q4: khach hang lon =====================
class Large : public CUSTOMER {
protected:
    double scale;
    double cooperation;

public:
    Large() : CUSTOMER(), scale(0.0), cooperation(0.0) {}
    Large(string id, string name, double s, double c)
        : CUSTOMER(id, name), scale(s), cooperation(c) {}

    void input() override {
        CUSTOMER::input();
        cin >> scale >> cooperation;
    }

    double calculateCPS() override {
        CPS = 0.7 * scale + 0.3 * cooperation;
        return CPS;
    }
};

// ===================== Q4: khach hang nho =====================
class Small : public CUSTOMER {
protected:
    double demand;
    double financial;

public:
    Small() : CUSTOMER(), demand(0.0), financial(0.0) {}
    Small(string id, string name, double d, double f)
        : CUSTOMER(id, name), demand(d), financial(f) {}

    void input() override {
        CUSTOMER::input();
        cin >> demand >> financial;
    }

    double calculateCPS() override {
        CPS = 0.5 * demand + 0.5 * financial;
        return CPS;
    }
};

// ===================== Q5: danh sach + sap xep + in =====================
int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        cout << "n must be a positive integer\n";
        return 0;
    }

    // mang n con tro base, khoi tao nullptr
    CUSTOMER** ds = new CUSTOMER*[n]();

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;

        if (type == 1) ds[i] = new Large();
        else           ds[i] = new Small();

        ds[i]->input();          // virtual -> chay input cua lop con
        ds[i]->calculateCPS();   // tinh va luu CPS
    }

    // giam dan theo CPS: dao nguoc operator<
    sort(ds, ds + n, [](CUSTOMER* a, CUSTOMER* b) { return *b < *a; });

    cout << "\n" << left
         << setw(5)  << "No."
         << setw(16) << "Customer ID"
         << setw(28) << "Company Name"
         << "Potential Score\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(5) << i + 1;
        ds[i]->display();
        cout << right << fixed << setprecision(2)
             << setw(16) << ds[i]->getCPS() << "\n";
    }

    cout << "\nAverage potential score: "
         << fixed << setprecision(2) << CUSTOMER::averageCPS(ds, n) << "\n";

    for (int i = 0; i < n; i++) delete ds[i];   // xoa tung object
    delete[] ds;                                // xoa mang con tro

    return 0;
}
