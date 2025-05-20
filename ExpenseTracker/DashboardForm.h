#pragma once
#include"Expense.h"
#include"AddExpenseForm.h"
#include"ViewExpensesForm.h"
namespace ExpenseTracker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for DashboardForm
	/// </summary>
	public ref class DashboardForm : public System::Windows::Forms::Form
	{
	private:
		String^ loggedInUser;
		List<Expense^>^ expenses; // List to store expenses for the logged-in user
	public:
		DashboardForm(String^ username)
		{
			InitializeComponent();
			loggedInUser = username;
			expenses = gcnew List<Expense^>(); // Initialize the list of expenses
			welcomeLabel->Text = "Welcome, " + username + "!";
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DashboardForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		//Form Controls
		Label^ welcomeLabel;
		Button^ addExpenseBtn;
		Button^ viewExpensesBtn;
		Button^ logoutBtn;
		
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->welcomeLabel = gcnew	System::Windows::Forms::Label();
			this->addExpenseBtn = gcnew Button();
			this->viewExpensesBtn = gcnew Button();
			this->logoutBtn = gcnew Button();
			this->SuspendLayout();

			//Welcome Label
			this->welcomeLabel->AutoSize = true;
			this->welcomeLabel->Location = System::Drawing::Point(50, 30);
			this->welcomeLabel->Size = System::Drawing::Size(200, 25);
			this->welcomeLabel->Font = gcnew Drawing::Font(L"Arial", 14, FontStyle::Bold);

			// Add Expense Button
			this->addExpenseBtn->Text = L"Add Expense";
			this->addExpenseBtn->Location = Drawing::Point(50, 100);
			this->addExpenseBtn->Size = Drawing::Size(150, 40);
			this->addExpenseBtn->Click += gcnew System::EventHandler(this, &DashboardForm::addExpenseBtn_Click);

			//View Expenses Button
			this->viewExpensesBtn->Text = L"View Expenses";
			this->viewExpensesBtn->Location = Drawing::Point(50, 160);
			this->viewExpensesBtn->Size = Drawing::Size(150, 40);
			this->viewExpensesBtn->Click += gcnew System::EventHandler(this, &DashboardForm::viewExpensesBtn_Click);

			//Logout Button
			this->logoutBtn->Text = L"Logout";
			this->logoutBtn->Location = Drawing::Point(50, 220);
			this->logoutBtn->Size = Drawing::Size(150, 40);
			this->logoutBtn->Click += gcnew System::EventHandler(this, &DashboardForm::logoutBtn_Click);

			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(757, 681);
			this->Name = L"DashboardForm";
			this->Text = L"DashboardForm";
			this->Load += gcnew System::EventHandler(this, &DashboardForm::DashboardForm_Load);
			this->Controls->Add(this->welcomeLabel);
			this->Controls->Add(this->addExpenseBtn);
			this->Controls->Add(this->viewExpensesBtn);
			this->Controls->Add(this->logoutBtn);
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void logoutBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit(); // Close the program
		}
	private: System::Void addExpenseBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		AddExpenseForm^ form = gcnew AddExpenseForm();
		if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			Expense^ newExp = form->NewExpense;
			expenses->Add(newExp);
			MessageBox::Show("Expense Added Succesfully!");
		}
	}
		   private: System::Void viewExpensesBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		ViewExpensesForm^ form = gcnew ViewExpensesForm(expenses);
		form->ShowDialog();
		   }
	private: System::Void DashboardForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
