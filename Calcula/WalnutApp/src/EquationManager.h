#pragma once
#include "fstream"
#include "vector"
#include "string"
#include "cstdlib"
using namespace std;

static class EquationManager {
public:
	static vector<string> LoadEquations() {
		ifstream file("equation.txt");
		vector<string> equations;
		string formula;
		string description;
		string tag;
		while (getline(file, formula, ',') && getline(file, description, ',') && getline(file, tag)) {
			equations.push_back(formula);
			equations.push_back(description);
			equations.push_back(tag);
		}
		return equations;
	}

	static void SaveEquations(vector<string>& formula, vector<string>& description, vector<string>& tag) {
		ofstream file;
		file.open("equation.txt");
		for (int i = 0; i < formula.size(); i++) {
			file << "Formula: " << formula[i] << endl;
			if (i < description.size()) {
				file << "Description: " << description[i] << endl;
			}
			if (i < tag.size()) {
				file << "Tag: " << tag[i] << endl;
			}
			file << endl << endl;
		}
	}
};

