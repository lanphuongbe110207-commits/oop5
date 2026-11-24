#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
using namespace std;
class EMPLOYEE {
protected :
string Emp_ID;
string Full_Name;
double Salary;
static int total;
public:
EMPLOYEE(string ID, string Name, double money ) :
Emp_ID(ID), Full_Name(Name), Salary(money){total++;}
EMPLOYEE() : Emp_ID(""), Full_Name(""), Salary(0.0){total++;} 
// default constructor : ten_class() : field1(gtmd), field2(gtmd)...{}
virtual ~EMPLOYEE(){total--;}

virtual void input(){
    cout<<"Enter ID: ";
    getline(cin>>ws,Emp_ID);
    cout<<"Full name: ";
    getline(cin>>ws, Full_Name);
    
}// virtual dong y cho lop con ghi de

virtual double calculateSalary() =0;

bool operator <(const EMPLOYEE& o ) const {
    return Salary>o.Salary;
}

void display(int no){
    cout<<left<<setw(6)<<no
        <<setw(12)<< Emp_ID
        <<setw(25)<<Full_Name
        <<fixed<<setprecision(2)<<Salary<<endl;
        // in ra so thuc, setprecison de lam tron den 2 chu so sau dau phay
}

static int getTotal(){
    return total;
}


};
int EMPLOYEE :: total =0;

class FULL_TIME_EMPLOYEE : public EMPLOYEE
{
    protected:
    int Allowance_Index;
    double Coefficients_Salary;
    double Base_Salary;
    public :
    FULL_TIME_EMPLOYEE(string ID, string Name, double money,int index, double coe, double base)
    :EMPLOYEE(ID, Name,money), Allowance_Index(index), Coefficients_Salary(coe), Base_Salary(base){}
// initialized list

    FULL_TIME_EMPLOYEE() : EMPLOYEE(), Allowance_Index(0), Coefficients_Salary(0.0), Base_Salary(0.0){}//default
    virtual ~FULL_TIME_EMPLOYEE(){}
    void input() override{
        EMPLOYEE::input();
        cout<<"Coefficient Salary";
        cin>>Coefficients_Salary;
        cout<<"Base Salary: ";
        cin>>Base_Salary;
        cout<<"Allowance Index: ";
        cin>> Allowance_Index;
        calculateSalary();
    }
    double calculateSalary() override{
        return Salary = (Coefficients_Salary + Allowance_Index) * Base_Salary;
    }



};

class Part_Time_Employee : public EMPLOYEE {
    protected:
    double Working_Hours;
    double Hourly_Rate;
    public:
    Part_Time_Employee(string ID, string Name, double money, double hours, double rate)
    : EMPLOYEE(ID, Name, money), Working_Hours(hours), Hourly_Rate(rate){}
    Part_Time_Employee() : 
    EMPLOYEE(), Working_Hours(0.0), Hourly_Rate(0.0){}
    virtual ~Part_Time_Employee(){}
    void input() override{
        EMPLOYEE::input();
        cout<<"Working Hours: ";
        cin>>Working_Hours;
        cout<<"Hour: ";
        cin>>Hourly_Rate;
        calculateSalary();
    
    }
    
    double calculateSalary()override {
        return Salary = Working_Hours * Hourly_Rate;
    } 
};

struct Node{
    EMPLOYEE* data; // mỗi node có 1 biến data, con trỏ troe tới employee
    Node* next; // con trỏ trỏ tới node tiếp theo
    Node(EMPLOYEE* e) : data(e), next(nullptr){}
    // constructor, khi tạo Node, nhận vào 1 trỏ nhân viên e
    // next = nullptr,ko lam gì thêm
};


class Employeelist {
    private:
    Node*head;
    public:
    Employeelist() : head(nullptr){};
    ~Employeelist(){
        while(head){
            Node*t = head;
            head= head->next;
            delete t->data;// xoa di nvien
            delete t; // xoa di con tro
        }
    }
    void addTail(EMPLOYEE*e){
        Node*n = new Node(e);
        // tao node moi tro vao nhan vien moi
        // n la con tro giu dia chi cua node moi do
        // luc nay node moi ch nam trong list
        if(!head){
            head = n;
            return;
        }

        Node*cur = head;
        while (cur->next)
        {
            cur = cur->next;
            // chay tu dau den dit
        }

            cur->next = n;
            // gan node moi vao dit
        
    }
    void SortDesc (){
        while(!head)return;
        for(Node*i = head; i; i = i->next){
            for(Node*j = head; j->next; j = j->next){
                if (*j->next->data < *j->data)
                swap(j->data, j->next->data);
                
            }
        }}
    

    void input(){
        int n;
        cout<<"The number of Employees : ";
        cin >> n;
        for(int i =0; i<n; i++){
            int type;
            cout<<"1.Full Time"<<endl;
            cout<<"2.Part Time"<<endl;
            cin>>type;
            EMPLOYEE* e = (type == 1) ? 
            (EMPLOYEE*) new FULL_TIME_EMPLOYEE():
            (EMPLOYEE*) new Part_Time_Employee();
        
        e->input();
        addTail(e);

    }
 } 
    void display() const {
        cout << left << setw(6) << "no"
             << setw(12) << "Emp_ID"
             << setw(25) << "Full_Name"
             << fixed << setprecision(2) << "Salary" << endl;
             int no = 1;
             for(Node*p = head; p; p = p->next){
                p->data->display(no++);
             }
             cout<<"Total Employeess : " << EMPLOYEE::getTotal()<<endl;



    }



};
int main(){
    Employeelist list;
    list.input();
    list.SortDesc();
    cout<<endl;
    list.display();
    return 0;
    

    return 0;
}