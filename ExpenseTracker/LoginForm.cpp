#include "LoginForm.h"
#include "User.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ExpenseTracker::LoginForm form;
	Application::Run(%form);
	return 0;
}