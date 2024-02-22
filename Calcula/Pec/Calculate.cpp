#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

double Calculate(string problem)
{
    vector<string> oparationList;
    vector<double> numList;
    string oparation = problem;
    string alphabet = "";

    for (int i = 0; i < oparation.size(); i++)
    {
        if (oparation[i] != ' ')
        {
            if (oparation[i] == '(')
            {
                i++;
                string subProblem = "";
                while (oparation[i] != ')')
                {
                    subProblem += oparation[i];
                    i++;
                }
                numList.push_back(Calculate(subProblem));
                continue;
            }
            alphabet += oparation[i];
        }

        if (oparation[i] == ' ' || i == oparation.size() - 1)
        {
            if (alphabet.size() > 0)
            {
                if (alphabet[0] >= '0' && alphabet[0] <= '9')
                    numList.push_back(stod(alphabet));
                else
                    oparationList.push_back(alphabet);
                alphabet = "";
            }
        }
    }

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        if (oparationList[i] == "^")
        {
            double op = pow(numList[i], numList[i + 1]);
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
    }

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        if (oparationList[i] == "*")
        {
            double op = numList[i] * numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
        else if (oparationList[i] == "/")
        {
            double op = numList[i] / numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
    }

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        if (oparationList[i] == "+")
        {
            double op = numList[i] + numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
        else if (oparationList[i] == "-")
        {
            double op = numList[i] - numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
    }

    return numList[0];
}

static vector<string> GetInputVariablesList(string formula) {
    vector<string> variables;
    string var = "";
    for (auto i : formula) {
        if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')) {
            var += i;
        }

        if (i == ' ' || i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == ')' || i == '(') {
            if (var != "")
                variables.push_back(var);
            var = "";
        }
    }
    if (var != "") variables.push_back(var);
    return variables;
}
 
static double CalcualteEquation(string formula, unordered_map<string, float> variables) {
    formula = formula.substr(formula.find("=") + 1);
    string var = "";
    cout << formula << endl;
    for (int i = 0; i < formula.size(); i++) {
        if ((formula[i] >= 'a' && formula[i] <= 'z') || (formula[i] >= 'A' && formula[i] <= 'Z')) {
            var += formula[i];
        }

        if (formula[i] == ' ' || formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^' || formula[i] == ')' || formula[i] == '(') {
            if (var != "") {
                cout << var << endl;
                formula.replace(i - var.size(), var.size(), to_string(variables[var]));
                cout << formula << endl;
            }
            var = "";
        }
    }
    if (var != "") {
        cout << var << endl;
        formula.replace(formula.size() - var.size(), var.size(), to_string(variables[var]));
        cout << formula << endl;
    }
    double value = Calculate(formula);
    return value;
}