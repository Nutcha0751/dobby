inline bool CheckFile(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

static unsigned Hashing(const std::string& name) {
	hash<std::string> hasher;
	return hasher(name);
}

static int GenarateImage(const std::string& formula, const std::string& fileName) {
	cout << formula << endl;
	string fl = "\"" + formula + "\"";
	string fn = " \"" + fileName + ".png\"";
	string command = "LaTex\\LaTex.exe " + fl + fn;
	int k = system(command.c_str());
	cout << k << endl;
	return k;
}

static string ToLaTexFormat(const std::string& formula) {
	string result = formula;
	int i = result.find("c:pi");
	while (i < result.size()) {
		result.replace(i, 4, " \\pi ");
		i = result.find("c:pi");
	}

	i = result.find("c:e");
	while (i < result.size()) {
		result.replace(i, 3, " e ");
		i = result.find("c:e");
	}

	i = result.find("*");
	while (i < result.size()) {
		result.replace(i, 1, " \\times ");
		i = result.find("*");
	}


	return result;
}