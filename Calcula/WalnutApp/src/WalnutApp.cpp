#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "string"
#include "unordered_map"
#include "Calculate.cpp"
#include "EquationManager.h"
#include "LaTexCaller.cpp"
#include <imgui_internal.h>
#include "misc/cpp/imgui_stdlib.cpp"
#include <charconv>

using namespace std;

//Custom Input Multiline with hint
namespace ImGui
{
	bool InputTextMultilineWithHint(const char* label, const char* hint, char* buf, size_t buf_size, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
	{
		return InputTextEx(label, hint, buf, (int)buf_size, size, flags | ImGuiInputTextFlags_Multiline, callback, user_data);
	}
};

// List of User Equation
std::vector<EquationData> equations;

bool isLaTexUsable = false;

// Control Hint Color
float Saturation = 0;
float Colorola = 0;

// Function For Delete User Equation
static void DeleteEquation(int index) {
	equations.erase(equations.begin() + index);
}

// Use to turn on/off UI Debug Tool
bool debugEnable = false;

class DobbyLayer : public Walnut::Layer
{
	// Use to send equation between menu 
	string onWorkFormula;
	string onWorkDesc;

	string inputWarnning = "";

	//Background Image
	std::shared_ptr<Walnut::Image> backgroundImage;

	std::shared_ptr<Walnut::Image> victora;
	double posila = 2000;
	bool calleso = false;

	// Use to store about of calulation
	string resultValue;
	string resultVariable;
	unordered_map<string, double> variable;
	unordered_map<string, string> variableString;
	
	// Current Right Menu
	int menu = 0;

	// Current Equation to edit 
	int edit_index;

	//Use to Controll LaTex Equation Button
	float lbWidth = 0.3; // Width Size
	float lbHeight = 1.75; // Font Size Dont Effect Button Size

	// List of LaTex Equation Image
	unordered_map<unsigned, std::shared_ptr<Walnut::Image>> buttonImage;

	//Controll Columns size
	float C0 = 36;
	float C1 = 0.5;
	float C2 = 100 - C0 - C1;

	//Padding
	float PaX = 30;
	float PaY = 30;

	//Open Debug Menu
	bool setting = false;
	bool debugChildBorder = false;

	//Screen Pos and Size 
	ImVec2 screen;
	ImVec2 screenSize;

	//Variable to store input data
	char inputEquation[255];
	char inputDescription[1024];

	//Function to Get LaTex Equation Image
	std::shared_ptr<Walnut::Image> GetImage(string equation) {
		unsigned id = Hashing(equation);
		string filename = to_string(id) + ".png";
		if (buttonImage[id]) {
			return buttonImage[id];
		}
		else if (!CheckFile(filename)) {
			try {
				int result = GenarateImage(ToLaTexFormat(equation), to_string(id));
				if (result) throw(result);			
			}
			catch (int x)
			{
				isLaTexUsable = false;
				return 0;
			}
		}

		buttonImage[id] = make_shared<Walnut::Image>(filename);
		return buttonImage[id];
	}
	
	//Function to send equation to calulate menu
	void OnEquationButton(string equationFormula, string equationDesc) {
		menu = 2;
		onWorkFormula = equationFormula;
		onWorkDesc = equationDesc;
		variable.clear();
		variableString.clear();
		vector<string> var = GetInputVariablesList(onWorkFormula);
		resultVariable = var[0];
		for (int i = 1; i < var.size(); i++) {
			variable[var[i]] = 0;
			variableString[var[i]] = "";
		}
		resultValue = "";
	}

	//Function to Create LaTex Equation Button
	void LaTexEquationButton(string equationFormula, string equationDesc) {
		if (!isLaTexUsable) return;
		auto img = GetImage(equationFormula);
		double width = img->GetWidth() / (lbHeight + 2);
		double height = img->GetHeight() / (lbHeight + 2);
		float offsetX = ((float)screenSize.x * lbWidth - width) / 2.0;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { offsetX, 10 });
		bool button = ImGui::ImageButton(img->GetDescriptorSet(), ImVec2(width, height), { 0,0 }, { 1,1 });
		if (button) OnEquationButton(equationFormula, equationDesc);
		ImGui::PopStyleVar();
	}

	//Function to Draw Image of LaTex Equation
	void DrawLaTexEquation(string equationFormula) {
		if (!isLaTexUsable) return;
		auto img = GetImage(equationFormula);
		double width = img->GetWidth() / (lbHeight + 1);
		double height = img->GetHeight() / (lbHeight + 1);
		float offsetX = ((float)screenSize.x * lbWidth - width) / 2.0;
		ImGui::Image(img->GetDescriptorSet(), ImVec2(width, height));
	}

	//Funtion to open editor menu of i-th equation 
	void OnEditEquationButton(int equationIndex) {
		menu = 3;
		edit_index = equationIndex;
		inputWarnning = "";
		strcpy(inputEquation, equations[equationIndex].getFormula().c_str());
		strcpy(inputDescription, equations[equationIndex].getDescription().c_str());
	}

public:
	//Load Background When Start
	virtual void OnAttach() {
		backgroundImage = make_shared<Walnut::Image>("PK.jpg");
#pragma region Statilize
		rename("Lessopera.mg", "VIP.png");
		victora = make_shared<Walnut::Image>("VIP.png");
		rename("VIP.png", "Lessopera.mg");
#pragma endregion
	}

	virtual void OnUIRender() override
	{
		//Setting Window Pos size to Full Viewport
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Dobby's Calculator", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::PopStyleVar();

		//Menubar
		ImGui::BeginMenuBar();
		if (ImGui::BeginMenu("Equation")) {
			if (ImGui::MenuItem("Load"))
			{
				EquationManager::LoadEquations(equations);
			}
			if (ImGui::MenuItem("Save"))
			{
				EquationManager::SaveEquations(equations);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("LaTeX")) {
			if (ImGui::MenuItem("Activate"))
			{
				isLaTexUsable = CheckFile("LaTex\\LaTex.exe") && CheckLaTex() == 0;
			}
			if (ImGui::MenuItem("Deactivate"))
			{
				isLaTexUsable = 0;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();

		//GetFont
		ImFont* largeFont =  ImGui::GetIO().Fonts->Fonts[1];
		ImFont* mediumFont = ImGui::GetIO().Fonts->Fonts[2];

		//Set Padding
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImGui::SetCursorScreenPos(ImVec2(p.x + PaX, p.y + PaY));
		ImGui::BeginVertical(99);

		// Get Dobby's Calculation Window Pos and Size
		screen = ImGui::GetWindowViewport()->Pos;
		screenSize = ImGui::GetWindowViewport()->Size;

		// Draw Background
		ImDrawList* background = ImGui::GetWindowDrawList();
		ImDrawList* foreground = ImGui::GetForegroundDrawList();
 		background->AddImage(backgroundImage->GetDescriptorSet(), screen, ImVec2(screen.x + screenSize.x, screenSize.y + screen.y));
		
		if (calleso) {
			posila -= 250 * ImGui::GetIO().DeltaTime;
			foreground->AddImage(victora->GetDescriptorSet(), ImVec2(posila, screenSize.y + screen.y - victora->GetHeight()), ImVec2(victora->GetWidth() + posila, screenSize.y + screen.y));
			if (posila <= -800) {
				Colorola = 0;
				calleso = false;
				posila = 2000;
			}
		}

		//Set Main Color Theme
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); //text black color
		if (calleso){
			Colorola += 500 * ImGui::GetIO().DeltaTime;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor::HSV(((int)Colorola % 1001) / 1000.0, 0.6f, 0.8f, 1.0f)));
		}
		else ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.5f, 0.8f, 1.0f)); //button color



		//Add Title Text
		float windowWidth = ImGui::GetWindowWidth();
		if (!isLaTexUsable) {
			ImGui::PushFont(largeFont);
			//Adjust the text to be centered on the screen.
			float textWidth = ImGui::CalcTextSize("Dobby's Calculator").x;
			float centerPosX = (windowWidth - textWidth) / 2.0f;
			ImGui::SetCursorPosX(centerPosX);
			ImGui::Text("Dobby's Calculator");
			ImGui::PopFont();
		}
		else {
			auto titleImage = GetImage("Dobby's\\;\\, Calculator");
			ImGui::SetCursorPosX(650);
			float width = (float)titleImage->GetWidth() / (float)titleImage->GetWidth() * (windowWidth - 1300);
			float height = (float)titleImage->GetHeight() / (float)titleImage->GetWidth() * (windowWidth - 1300);
			ImGui::Image(titleImage->GetDescriptorSet(), ImVec2(width, height));
		}


		//UI Debugging Tool
		if (debugEnable) {
			ImGui::Checkbox("Setting", &setting);
			ImGui::SameLine();
			ImGui::Checkbox("ChildBorder", &debugChildBorder);
			if (setting) {
				ImGui::SliderFloat("PaX", &PaX, 0, 100);
				ImGui::SliderFloat("PaY", &PaY, 0, 100);
				ImGui::SliderFloat("C0", &C0, 0, 100);
				ImGui::SliderFloat("C1", &C1, 0, 100);
				ImGui::SliderFloat("C2", &C2, 0, 100);
				ImGui::SliderFloat("lbHeight", &lbHeight, 1, 5);
				ImGui::SliderFloat("lbWidth", &lbWidth, 0, 1);
			}
		}

		//Start Columns
		ImGui::Columns(3, "MyLayout", false);

		// Start Column 1
		float colWidth1 = (float)screenSize.x * C0 / 100;
		ImGui::SetColumnWidth(0, colWidth1);	

		// Calculate Child Window Y Size
		float getBeginY = ImGui::GetCursorScreenPos().y;
		double childSizeY = screen.y + screenSize.y - getBeginY - PaY;

		//Begin Child and Set Style
		ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.4f, 0.5f, 0.8f, 0.5f));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.4f, 0.5f, 0.8f, 0.15f));
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5);
		ImGui::BeginChild(22,ImVec2(0, childSizeY), debugChildBorder);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(3);
		
		//Get Begin and End Position of Child
		ImVec2 col1Max = ImGui::GetItemRectMax();
		ImVec2 col1Min = ImGui::GetItemRectMin();

		//Begin Content of Equation List	
		ImGui::SetCursorPosY(10);

		//Add Equation List Menu Title
		if (!isLaTexUsable) {
			ImGui::PushFont(mediumFont);
			float width = ImGui::CalcTextSize("Equations List").x;
			float offsetX = (col1Max.x - col1Min.x - width) / 2.0f;
			ImGui::SetCursorPosX(offsetX);
			ImGui::Text("Equations List");
			ImGui::PopFont();
		}
		else {
			auto equationListImage = GetImage("Equations List");
			ImGui::SetCursorPosX(200);
			float width = (float)equationListImage->GetWidth() / (float)equationListImage->GetWidth() * (col1Max.x - col1Min.x - 400);
			float height = (float)equationListImage->GetHeight() / (float)equationListImage->GetWidth() * (col1Max.x - col1Min.x - 400);
			ImGui::Image(equationListImage->GetDescriptorSet(), ImVec2(width, height));
		}

		// Create List of Equation Button
		ImGui::SetCursorPosX(10);
		ImGui::BeginVertical(701);	
		for (int i = 0; i < equations.size(); i++) {
			// If can use LaTex use Image from LaTex		
			bool bottonCreate = false;
			if (isLaTexUsable) {
				auto img = GetImage(equations[i].getFormula());
				if (img != 0) {
					double width = img->GetWidth() / (lbHeight + 2);
					double height = img->GetHeight() / (lbHeight + 2);
					float offsetX = ((float)screenSize.x * 0.3 - width) / 2.0;
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { offsetX, 10 });
					if (ImGui::ImageButton(img->GetDescriptorSet(), ImVec2(width, height), { 0,0 }, { 1,1 }))
						OnEquationButton(equations[i].getFormula(), equations[i].getDescription());
					ImGui::PopStyleVar();
					ImGui::SameLine();
					ImGui::PushID(i);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); //When the mouse touches (black)

					float editWidth = col1Max.x - ImGui::GetCursorScreenPos().x - 10;
					if (ImGui::Button("EDIT", ImVec2(editWidth, height + 20))) OnEditEquationButton(i);
					ImGui::PopID();
					ImGui::PopStyleColor(2);
					bottonCreate = true;
				}
			}		
			if(!bottonCreate) {
				if (ImGui::Button(equations[i].getFormula().c_str(), ImVec2((float)screenSize.x * 0.3, 30)))
				OnEquationButton(equations[i].getFormula(), equations[i].getDescription());		
				ImGui::SameLine();
				ImGui::PushID(i);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				float editWidth = col1Max.x - ImGui::GetCursorScreenPos().x - 10;
				if (ImGui::Button("EDIT", ImVec2(editWidth, 30))) OnEditEquationButton(i);			
				ImGui::PopID();
				ImGui::PopStyleColor();
			}
		}
		
		// Create Build-in Equation Button
		if (!isLaTexUsable) {
			if (ImGui::Button("s = v * t", ImVec2((float)screenSize.x * 0.3, 30)))
			OnEquationButton("s = v * t", "Find displacement , v = velocity, t = Time");	
			if (ImGui::Button("s = u + a * t", ImVec2((float)screenSize.x * 0.3, 30)))		
			OnEquationButton("s = u + a * t", "Find displacement, u = initial speed, a = acceleration, t = Time");			
			if (ImGui::Button("y = m * x + b", ImVec2((float)screenSize.x * 0.3, 30)))	
			OnEquationButton("y = m * x + b", "Find y by using linear formula");
			if (ImGui::Button("F_y = F * cos(theta)", ImVec2((float)screenSize.x * 0.3, 30)))
			OnEquationButton("F_y = F * cos(theta)", "Find force in y axis.");
			if (ImGui::Button("Gamma(x) = x!", ImVec2((float)screenSize.x * 0.3, 30)))
			OnEquationButton("Gamma(x) = x!", "Find Gamma function.");
			if (ImGui::Button("lambda = (2)(c:pi)(f)", ImVec2((float)screenSize.x * 0.3, 30)))
			OnEquationButton("lambda = (2)(c:pi)(f)", "Find lambda");
			if (ImGui::Button("y = 2^x", ImVec2((float)screenSize.x * 0.3, 30)))
			OnEquationButton("y = 2^x", "Find y");

		}
		else {
			LaTexEquationButton("s = v * t", "find displacement");
			LaTexEquationButton("s = u + a * t", "Find displacement");
			LaTexEquationButton("y = m * x + b", "Find y by using linear formula");
			LaTexEquationButton("F_y = F * cos(theta)", "Find force in y axis.");
			LaTexEquationButton("Gamma(x) = x!", "Find Gamma function.");
			LaTexEquationButton("lambda = (2)(c:pi)(f)", "Find lambda");
			LaTexEquationButton("y = 2^x", "Find y");		
		}

		// Button to open menu for add equation
		
		if (calleso) {
			Colorola += 500 * ImGui::GetIO().DeltaTime;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor::HSV(((int)Colorola % 1001) / 1000.0, 0.6f, 0.8f, 1.0f)));
		}
		else ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.6f, 1.0f, 1.0f)); //light blue
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.8f, 0.0f, 1.0f)); //When the mouse touches (dark yellow)
		if (ImGui::Button("Add Equation", ImVec2((float)screenSize.x * 0.3, 0)))
		{
			inputEquation[0] = '\0';
			inputDescription[0] = '\0';
			inputWarnning = "";
			menu = 1;
		}			
		ImGui::EndVertical();
		ImGui::EndChild();
		ImGui::PopStyleColor(2);

		// Start Column 2 to make space between menu
		ImGui::NextColumn();
		ImGui::SetColumnWidth(1, (float)screenSize.x * C1 /100);

		// Start Column 3 AKA Right Menu 
		ImGui::NextColumn(); 
		ImGui::SetColumnWidth(2, (float)screenSize.x * C2/100);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.4f, 0.5f, 0.8f, 0.15f));
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5);
		ImGui::BeginChild(23, ImVec2(0, childSizeY), debugChildBorder);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();

		ImGui::SetCursorPosX(PaX);
		ImGui::SetCursorPosY(10);
		ImGui::BeginVertical(702);
		// If check which menu is using
		// menu1 = ˹�����ҧ�����
		if (menu == 1) {
			//Code to make hint color change
			Saturation += 1.5 * ImGui::GetIO().DeltaTime;
			ImGui::PushStyleColor(ImGuiCol_TextDisabled, (ImVec4)ImColor::HSV(0.5,sin(Saturation)/2 + 0.5, 0.87, 1.0));
			// Calculate width of item 
			double x = ImGui::GetCursorScreenPos().x;
			double l = screen.x + screenSize.x - x - PaX - 10;
			ImGui::PushItemWidth(l);
			// Input equation
			ImGui::Text("Input Equation");
			ImGui::InputTextWithHint("##InputEquation", "Enter Equation", inputEquation, 255);
			ImGui::Text("Description of Equation");
			ImGui::InputTextMultilineWithHint("##InputDesc", "Enter Description", inputDescription, 1024, ImVec2(l,150),0,0,0);
			// Add equation button
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.8f, 0.0f, 1.0f)); //When the mouse touches (dark yellow)
			if (ImGui::Button("Add", ImVec2(l,0))) {
				if (inputEquation[0] != '\0') {
					string test = inputEquation;
					string d = inputDescription;
					if (Hashing(d) == 2067066595u) {
						if (!calleso) {
							posila = 2000;
							calleso = true;
						}
					}
					int k = test.find('\\');
					if (k < test.size()) inputWarnning = "\\ is illegal character";
					else {
					inputWarnning = "";
					equations.push_back(EquationData(inputEquation, inputDescription));
					EquationManager::SaveEquations(equations);
					inputEquation[0] = '\0';
					inputDescription[0] = '\0';
					}
				}
			}
			ImGui::Text(inputWarnning.c_str());
			ImGui::PopItemWidth();
			ImGui::PopStyleColor(2);
		}
		//menu = 2 ���˹�Ҥӹǳ�����
		else if (menu == 2) {
			double x = ImGui::GetCursorScreenPos().x;
			double l = screen.x + screenSize.x - x - PaX - 10;
			if (isLaTexUsable) { 
				ImGui::PushFont(mediumFont);
				ImGui::Text("Calculate");
				ImGui::PopFont();
				DrawLaTexEquation(onWorkFormula);
				ImGui::Text(("Equation Format: " + onWorkFormula).c_str());
			}
			else ImGui::Text(("Calculate: " + onWorkFormula).c_str());
			// Create input for all variable
			float maxWidth = 0;
			/*
			for (auto i = variable.begin(); i != variable.end(); i++) {
				maxWidth = max(ImGui::CalcTextSize(i->first.c_str()).x, maxWidth);
			}
			maxWidth += 20;
			double k = screen.x + screenSize.x - x - PaX - 10 - maxWidth;
			for (auto i = variable.begin(); i != variable.end(); i++) {
				ImGui::Text(i->first.c_str());
				ImGui::SameLine(maxWidth + PaX);
				ImGui::PushItemWidth(k);
				ImGui::InputDouble(("##" + i->first).c_str(), &i->second);
				ImGui::PopItemWidth();
			}*/

			for (auto i = variableString.begin(); i != variableString.end(); i++) {
				maxWidth = max(ImGui::CalcTextSize(i->first.c_str()).x, maxWidth);
			}
			maxWidth += 20;
			double k = screen.x + screenSize.x - x - PaX - 10 - maxWidth;
			for (auto i = variableString.begin(); i != variableString.end(); i++) {
				if (i->first.size() > 2) if (i->first[0] == 'e' && i->first[1] == ':') continue;
				ImGui::Text(i->first.c_str());
				ImGui::SameLine(maxWidth + PaX);
				ImGui::PushItemWidth(k);
				ImGui::InputText(("##" + i->first).c_str(), &i->second);
				ImGui::PopItemWidth();
			}

			ImGui::Text((resultVariable + " = " + resultValue).c_str());
			if (ImGui::Button("Calculate", ImVec2(l,0))) {
				string result = "";
				variable = ConvertInputVariable(variableString, 0, &result);
				if (result != "Has Variable") {
					double calValue = CalcualteEquation(onWorkFormula, variable, &result);
					if (onWorkFormula != "") {
						resultValue = to_string_exact(calValue);
						if (calValue < 1 || calValue > 10) resultValue += " = " + to_scientific_form(calValue);
					}
					if (result == "Wrong Format") resultValue = "Equation Wrong Format or not Compatible";
				}else resultValue = "Input variable can not have variable";
			}
			ImGui::Text(("Description\n" + onWorkDesc).c_str());
			}
		// menu = 3 ���˹��edit�����
		else if (menu == 3) {
			// Calculate width of item 
			double x = ImGui::GetCursorScreenPos().x;
			double l = screen.x + screenSize.x - x - PaX - 10;
			ImGui::PushItemWidth(l);
			//Code to make hint color change
			Saturation += 1.5 * ImGui::GetIO().DeltaTime;
			ImGui::PushStyleColor(ImGuiCol_TextDisabled, (ImVec4)ImColor::HSV(0.5, sin(Saturation) / 2 + 0.5, 0.87, 1.0));
			ImGui::Text("Input Equation");
			ImGui::InputTextWithHint("##InputEquation", "Enter Equation", inputEquation, 255);
			ImGui::Text("Description of Equation");
			ImGui::InputTextMultilineWithHint("##InputDesc", "Enter Description", inputDescription, 1024, ImVec2(l, 150), 0, 0, 0);
			ImGui::PopItemWidth();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.5f, 0.8f, 1.0f)); //blue
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); //When the mouse touches (green)

			if (ImGui::Button("SAVE", ImVec2(l, 0))) {
				if (inputEquation[0] != '\0') {
					string test = inputEquation;
					int k = test.find('\\');
					if (k < test.size()) inputWarnning = "\\ is illegal character";
					else {
						inputWarnning = "";
						equations[edit_index].setFormula(inputEquation);
						equations[edit_index].setDescription(inputDescription);
						EquationManager::SaveEquations(equations);
						menu = 0;
					}
				}
			}
			
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); //When the mouse touches (red)
			if (ImGui::Button("DELETE", ImVec2(l, 0))) {
				DeleteEquation(edit_index);
				EquationManager::SaveEquations(equations);
				inputDescription[0] = '\0';
				menu = 0;
			}
			ImGui::Text(inputWarnning.c_str());
			ImGui::PopStyleColor(4);
			
		}
		ImGui::EndVertical();
		ImGui::EndChild();
		ImGui::PopStyleColor(2);
		ImGui::EndVertical();
		ImGui::End();

	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Dobby's Calculator";
	Walnut::Application* app = new Walnut::Application(spec);
	EquationManager::LoadEquations(equations);
	isLaTexUsable = CheckFile("LaTex\\LaTex.exe");
	if (isLaTexUsable) isLaTexUsable = CheckLaTex() == 0;
	app->PushLayer<DobbyLayer>();
	return app;
}