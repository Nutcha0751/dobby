#pragma once
#include "fstream"
#include "vector"
#include "string"
#include "cstdlib"
#include "EquationData.h"
using namespace std;

static class EquationManager {
public:
	static void LoadEquations(vector<EquationData>& equations) {
		equations.clear();
		ifstream file("equation.txt");
		string equation;
		string formula;
		string description;
		while (getline(file, equation) ){
			sscanf(equation.c_str(), "%[^,],%[^,]", formula.c_str(), description.c_str());
			cout << "Load " << formula.c_str() << "size: " << strlen(formula.c_str());
			equations.push_back(EquationData(formula.c_str(), description.c_str()));
		}
	}

	static void SaveEquations(vector<EquationData>& equations) {
		ofstream file;
		file.open("equation.txt");
		for (int i = 0; i < equations.size(); i++) {
			cout << "Save " << equations[i].getFormula() << "size: " << equations[i].getFormula().size();
			file <<  equations[i].getFormula() << "," << equations[i].getDescription() << endl;
		}
	}
};