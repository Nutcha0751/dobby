#include<iostream>
#include <string>
using namespace std;

namespace Pec {

    class EquationData
    {
    private:
        string formula;
        string description;

    public:
        EquationData(const string& _formula, const string& _description, const string& _tag)
            : formula(_formula), description(_description) {}

        // Setter functions
        void setFormula(const string& _formula) {
            formula = _formula;
        }

        void setDescription(const string& _description) {
            description = _description;
        }

        // Getter functions
        string getFormula() const {
            return formula;
        }

        string getDescription() const {
            return description;
        }
    };

}
