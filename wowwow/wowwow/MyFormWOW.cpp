#include "MyFormWOW.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	wowwow::MyFormWOW form;
		Application::Run(% form);
}