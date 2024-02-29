#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "string"
#include "unordered_map"
#include "Calculate.cpp"
#include "EquationManager.h"
#include "LaTexCaller.cpp"
#include <imgui_internal.h>

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

// Function For Delete User Equation
static void DeleteEquation(int index) {
	equations.erase(equations.begin() + index);
}

// Use to turn on/off UI Debug Tool
bool debugEnable = true;

class ExampleLayer : public Walnut::Layer
{
	// Use to send equation between menu 
	string onWorkFormula;
	string onWorkDesc;

	string inputWarnning = "";

	//Background Image
	std::shared_ptr<Walnut::Image> backgroundImage;

	// Use to store about of calulation
	string resultValue;
	string resultVariable;
	unordered_map<string, double> variable;
	
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
		vector<string> var = GetInputVariablesList(onWorkFormula);
		resultVariable = var[0];
		for (int i = 1; i < var.size(); i++) {
			variable[var[i]] = 0;
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

	void DrawLaTexEquation(string equationFormula) {
		if (!isLaTexUsable) return;
		auto img = GetImage(equationFormula);
		double width = img->GetWidth() / (lbHeight + 1);
		double height = img->GetHeight() / (lbHeight + 1);
		float offsetX = ((float)screenSize.x * lbWidth - width) / 2.0;
		ImGui::Image(img->GetDescriptorSet(), ImVec2(width, height));
	}

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
	}

	virtual void OnUIRender() override
	{
		//Setting Window Pos size to Full Viewport
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Dobby's Calculator", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar );
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

		ImFont* k =  ImGui::GetIO().Fonts->Fonts[1];

		//Set Padding
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImGui::SetCursorScreenPos(ImVec2(p.x + PaX, p.y + PaY));
		ImGui::BeginVertical(99);

		// Get Dobby's Calculation Window Pos and Size
		screen = ImGui::GetWindowViewport()->Pos;
		screenSize = ImGui::GetWindowViewport()->Size;

		// Draw Background
		ImDrawList* background = ImGui::GetWindowDrawList();
 		background->AddImage(backgroundImage->GetDescriptorSet(), screen, ImVec2(screen.x + screenSize.x, screenSize.y + screen.y));
		
		//Set Main Color Theme
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); //text black color
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.5f, 0.8f, 1.0f)); //button color

		ImGui::PushFont(k);
		//Adjust the text to be centered on the screen.
		float textWidth = ImGui::CalcTextSize("Dobby's Calculator").x;
		float windowWidth = ImGui::GetWindowWidth();
		float centerPosX = (windowWidth - textWidth) / 2.0f;
		ImGui::SetCursorPosX(centerPosX);
		ImGui::Text("Dobby's Calculator");
		ImGui::PopFont();                                                                  

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
		ImGui::SetColumnWidth(0, (float)screenSize.x * C0 / 100);
		ImGui::Text("Equations List");

		// Calculate Child Window Y Size
		float getBeginY = ImGui::GetCursorScreenPos().y;
		double childSizeY = screen.y + screenSize.y - getBeginY - PaY;

		//Begin Child and Set Slider color
		ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.4f, 0.5f, 0.8f, 0.5f));
		ImGui::BeginChild(22,ImVec2(0, childSizeY), debugChildBorder);
		ImGui::PopStyleColor(2);

		// Create List of Equation Button
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
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); //When the button is pressed (grey)
					if (ImGui::Button("EDIT", ImVec2(50, height + 20)))
						OnEditEquationButton(i);
					ImGui::PopID();
					ImGui::PopStyleColor(3);
					bottonCreate = true;
				}
			}
			
			if(!bottonCreate) {
				if (ImGui::Button(equations[i].getFormula().c_str(), ImVec2((float)screenSize.x * 0.3, 30)))
				OnEquationButton(equations[i].getFormula(), equations[i].getDescription());		
				ImGui::SameLine();
				ImGui::PushID(i);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				if (ImGui::Button("EDIT", ImVec2(50, 30))) 
				OnEditEquationButton(i);			
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
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.6f, 1.0f, 1.0f)); //light blue
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.8f, 0.0f, 1.0f)); //When the mouse touches (dark yellow)
		
		if (ImGui::Button("Add Equation", ImVec2((float)screenSize.x * 0.3, 30)))
		{
			inputEquation[0] = '\0';
			inputDescription[0] = '\0';
			inputWarnning = "";
			menu = 1;
		}			
		ImGui::EndChild();
		ImGui::PopStyleColor(2);

		// Start Column 2 to make space between menu
		ImGui::NextColumn();
		ImGui::SetColumnWidth(1, (float)screenSize.x * C1 /100);

		// Start Column 3 AKA Right Menu 
		ImGui::NextColumn(); 
		ImGui::SetColumnWidth(2, (float)screenSize.x * C2/100);
		ImGui::BeginChild(23, ImVec2(0, childSizeY), debugChildBorder);
		// If check which menu is using
		// menu1 = หน้าสร้างสมการ
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
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); //When the button is pressed (grey)
			if (ImGui::Button("Add", ImVec2((2*l)/3,0))) {
				if (inputEquation[0] != '\0') {
					string test = inputEquation;
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
			ImGui::PopStyleColor(3);
		}
		//menu = 2 คือหน้าคำนวณสมการ
		else if (menu == 2) {
			if (isLaTexUsable) { 
				ImGui::Text("Equation");
				DrawLaTexEquation(onWorkFormula);
				ImGui::Text(("Input Format: " + onWorkFormula).c_str());
			}
			else ImGui::Text(("Equation: " + onWorkFormula).c_str());
			// Create input for all variable
			for (auto i = variable.begin(); i != variable.end(); i++) {
					ImGui::Text(i->first.c_str());
					ImGui::SameLine();
					ImGui::InputDouble(("##" + i->first).c_str(), &i->second);
			}
			ImGui::Text((resultVariable + " = " + resultValue).c_str());
			if (ImGui::Button("Calculate")) {
				string result = "";
				if (onWorkFormula != "") resultValue = to_string(CalcualteEquation(onWorkFormula, variable, &result));
				if (result == "Wrong Format") resultValue = "Equation Wrong Format or not Compatible";
			}
			ImGui::Text(("Description\n" + onWorkDesc).c_str());
			}
		// menu = 3 คือหน้าeditสมการ
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
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); //When the button is pressed (grey)

			if (ImGui::Button("SAVE", ImVec2(l, 0))) {
				if (inputEquation[0] != '\0') {
					string test = inputEquation;
					int k = test.find('\\');
					if (k < test.size()) inputWarnning = "\\ is illegal character";
					else {
						inputWarnning = "";
						equations[edit_index].setFormula(inputEquation);
						equations[edit_index].setFormula(inputDescription);
						EquationManager::SaveEquations(equations);
						menu = 0;
					}
				}
			}
			

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); //When the mouse touches (red)
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); //When the button is pressed (grey)

			if (ImGui::Button("DELETE", ImVec2(l, 0))) {
				DeleteEquation(edit_index);
				EquationManager::SaveEquations(equations);
				inputDescription[0] = '\0';
				menu = 0;
			}
			ImGui::Text(inputWarnning.c_str());
			ImGui::PopStyleColor(6);
			
		}

		ImGui::EndChild();
		ImGui::PopStyleColor(2);
		ImGui::EndVertical();
		ImGui::End();

	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";
	Walnut::Application* app = new Walnut::Application(spec);

	isLaTexUsable = CheckFile("LaTex\\LaTex.exe");
	if (isLaTexUsable) isLaTexUsable = CheckLaTex() == 0;
	app->PushLayer<ExampleLayer>();
	return app;
}