#pragma once
#include "fstream"
#include "vector"
#include "string"
#include "cstdlib"
#include "EquationData.h"
using namespace std;

static class EquationManager {
public:
	static vector<EquationData> LoadEquations() {
		ifstream file("equation.txt");
		vector<EquationData> equations;
		string equation;
		string formula;
		string description;
		while (getline(file, equation) ){
			sscanf(equation.c_str(), "%[^,],%[^,]", formula.c_str(), description.c_str());
			equations.push_back(EquationData(formula, description));
		}
		return equations;
	}

	static void SaveEquations(vector<EquationData>& equations) {
		ofstream file;
		file.open("equation.txt");
		for (int i = 0; i < equations.size(); i++) {
			file <<  equations[i].getFormula() << "," << equations[i].getDescription() << endl;
		}
	}
};