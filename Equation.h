#include<iostream>
#include<string>
using namespace std;

class equation {
    private:
        string fomula  ;
        string description ;
        string tag ;
        double Displacement;
        double Velocity;
        double Time;

    public:
        void Motion(double,double,double);
        void Area(double,double,double);


};

void equation::Motion(double s,double v,double t){
    Displacement = s;
    Velocity = v;
    Time = t ;
    string fomula = "v = s / t" ;
    string description = "Use to find velocity";
    string tag = "Motion" ;
    
}

void equation::Area(double A,double r,double &Pi){
}

// class Area {
//     // private:
//     //    string AreaOfCricle = "A"; //พื้นที่วงกลม
//     //    string Radius = "r"; //รัศมี
//     //    string Pi = "3.14"; //ค่าPi
    
//     public:
//        string fomula = "Pi * r * r";
//        string description = "Use to find AreaOfCricle";
//        string tag = "Area";
// };



