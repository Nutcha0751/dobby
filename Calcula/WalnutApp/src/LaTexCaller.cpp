inline bool CheckFile(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

static unsigned Hashing(const std::string& name) {
	hash<std::string> hasher;
	return hasher(name);
}

static int CheckLaTex() {
	string command = "LaTex\\LaTex.exe";
	int k = system(command.c_str());
	return k;
}

static int CheckValid(const std::string& formula) {
	//cout << formula << endl;
	string cm = "\"check\"";
	string fl = " \"" + formula + "\"";
	string command = "LaTex\\LaTex.exe " + cm + fl;
	int k = system(command.c_str());
	return k;
}

static int GenarateImage(const std::string& formula, const std::string& fileName) {
	//cout << formula << endl;
	string cm = "\"gen\"";
	string fl = " \"" + formula + "\"";
	string fn = " \"" + fileName + ".png\"";
	string command = "LaTex\\LaTex.exe " + cm + fl + fn;
	int k = system(command.c_str());
	cout << k << endl;
	return k;
}

vector<string> greekAlphabet = {
	"alpha", "beta", "gamma", "Gamma", "delta", "Delta", "epsilon", "zeta", "theta", "Theta"
	,"iota", "kappa", "lambda", "Lambda", "mu", "nu", "xi", "Xi", "pi", "Pi", "rho", "sigma", "Sigma"
	, "tau", "upsilon", "Upsilon", "phi", "Phi", "chi", "psi", "Psi", "omega", "Omega", "eta"
};
static string ToLaTexFormat(const std::string& formula) {

	string result = formula;
	int i = result.find("c:pi");
	while (i < result.size()) {
		result.replace(i, 4, " pi ");
		i = result.find("c:pi");
	}

	i = result.find("c:e");
	while (i < result.size()) {
		result.replace(i, 3, " e ");
		i = result.find("c:e");
	}

	i = result.find_last_of("^") + 1;
	while (i < result.size() && i > 0) {
		int left = i + 1;
		cout << i << endl;
		int openParent = 0;
		int closeParent = 0;
		int openBrac = 0;
		int closeBrac = 0;
		int right;
		for (int k = i; k < result.size(); k++) {
			if (result[k] == '(') openParent++;
			if (result[k] == ')') closeParent++;
			if (result[k] == '{') openBrac++;
			if (result[k] == '}') closeBrac++;
			if (k == result.size() - 1) {
				right = k + 1;
				break;
			}
			if (openParent == closeParent && openBrac == closeBrac || k == result.size() - 1) {
				if (result[k] == '+' || result[k] == '-' || result[k] == '*' || result[k] == '/' || result[k] == '(') {
					right = k;
					break;
				}
			}
		}
		string replacer = "{" + result.substr(left, right - left) + "}";
		result.replace(left, right - left, replacer);
		i = result.find_last_of("^", i - 1);
	}

	i = result.find("*");
	while (i < result.size()) {
		result.replace(i, 1, " \\times ");
		i = result.find("*");
	}

	for (int k = 0; k < greekAlphabet.size(); k++) {
		i = result.find(greekAlphabet[k]);
		while (i < result.size()) {
			if (i > 0) {
				if (result[i - 1] == '(' ||result[i - 1] == ' ' ||((result[i - 1] >= '0' && (result[i - 1] <= '9')))) result.replace(i, greekAlphabet[k].size(), "\\" + greekAlphabet[k]);
			}else result.replace(i, greekAlphabet[k].size(), "\\" + greekAlphabet[k]);
			i = result.find(greekAlphabet[k],i + greekAlphabet[k].size());
		}
	}

	cout << "result LaTeX: " << result << endl;
	return result;
}