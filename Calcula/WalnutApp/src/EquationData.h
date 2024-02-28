#include<iostream>
#include <string>
using namespace std;

class EquationData
{
private:
    string formula;
    string description;

public:
    EquationData(string _formula, string _description)
        : formula(_formula), description(_description) {
    }

    // Setter functions
    void setFormula(string _formula) {
        formula = _formula;
    }

    void setDescription(string _description) {
        description = _description;
    }

    // Getter functions
    string getFormula() {
        return formula;
    }

    string getDescription() {
        return description;
    }
};
