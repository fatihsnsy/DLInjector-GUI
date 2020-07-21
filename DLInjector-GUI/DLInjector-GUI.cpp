#include "DLInjector-GUI.h"


using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	DLInjectorGUI::MyForm form;
	Application::Run(% form);

}

