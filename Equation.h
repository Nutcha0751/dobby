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
        string description = "use to find velocity";
        string tag = "Motion";
        // string eq2 = "s = v * t";
        // string description = "use to find displacement";
        // string tag = "Motion";
};
