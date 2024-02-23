#include<iostream>
#include<string>
using namespace std;

class RectilinearMotion {
    private:
        string Displacement = "s"; //การกระจัด
        string Velocity = "v"; //ความเร็ว
        string Time = "t"; //เวลา

    public:
        string fomula = "v = s / t";
        string description = "Use to find velocity";
        string tag = "Motion";
};

class Area {
    private:
       string AreaOfCricle = "A"; //พื้นที่วงกลม
       string Radius = "r"; //รัศมี
       string Pi = "3.14"; //ค่าPi
    
    public:
       string fomula = "Pi * r * r";
       string description = "Use to find AreaOfCricle";
       string tag = "Area";
};


