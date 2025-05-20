#pragma once
#include "DashboardForm.h"
#include "User.h"

namespace ExpenseTracker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	private:
		System::Collections::Generic::List<User^>^ users;
	public:
		LoginForm(void)
		{
			InitializeComponent();
			users = gcnew System::Collections::Generic::List<User^>();
		}
		bool UserExists(String^ username) {
			String^ filePath = "users.txt";
			if(!System::IO::File::Exists(filePath)) {
				return false;
			}
			array<String^>^ lines = System::IO::File::ReadAllLines(filePath);
			for each(String^ line in lines) {
				array<String^>^ parts = line->Split(',');
				if (parts->Length >= 2 && parts[0]->Equals(username)) {
					return true;
				}
			}
			return false;
		}
		void SaveUserToFile(User^ user) {
			String^ filePath = "users.txt";
			String^ userline = user->Username + "," + user->Password;
			System::IO::File::AppendAllText(filePath, userline + Environment::NewLine);
		}
		bool ValidateUser(String^ username, String^ password) {
			String^ filePath = "users.txt";
			if(!System::IO::File::Exists(filePath)) {
				return false;
			}
			array<String^>^ lines = System::IO::File::ReadAllLines(filePath);
			for each(String^ line in lines) {
				array<String^>^ parts = line->Split(',');
				if (parts->Length >= 2 && parts[0]->Equals(username) && parts[1]->Equals(password)) {
					return true;
				}
			}
			return false;
		}

	protected:
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ Usrlabel;
	private: System::Windows::Forms::Label^ Passlabel;
	protected:

	protected:

	private: System::Windows::Forms::TextBox^ userfeild;
	private: System::Windows::Forms::Button^ LoginBtn;


	private: System::Windows::Forms::Button^ RegisterBtn;

	private: System::Windows::Forms::TextBox^ passwordFeild;


	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->Usrlabel = (gcnew System::Windows::Forms::Label());
			this->Passlabel = (gcnew System::Windows::Forms::Label());
			this->userfeild = (gcnew System::Windows::Forms::TextBox());
			this->LoginBtn = (gcnew System::Windows::Forms::Button());
			this->RegisterBtn = (gcnew System::Windows::Forms::Button());
			this->passwordFeild = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// Usrlabel
			// 
			this->Usrlabel->AutoSize = true;
			this->Usrlabel->Location = System::Drawing::Point(100, 148);
			this->Usrlabel->Name = L"Usrlabel";
			this->Usrlabel->Size = System::Drawing::Size(83, 20);
			this->Usrlabel->TabIndex = 0;
			this->Usrlabel->Text = L"Username";
			this->Usrlabel->Click += gcnew System::EventHandler(this, &LoginForm::label1_Click);
			// 
			// Passlabel
			// 
			this->Passlabel->AutoSize = true;
			this->Passlabel->Location = System::Drawing::Point(105, 208);
			this->Passlabel->Name = L"Passlabel";
			this->Passlabel->Size = System::Drawing::Size(78, 20);
			this->Passlabel->TabIndex = 1;
			this->Passlabel->Text = L"Password";
			this->Passlabel->Click += gcnew System::EventHandler(this, &LoginForm::label2_Click);
			// 
			// userfeild
			// 
			this->userfeild->Location = System::Drawing::Point(241, 145);
			this->userfeild->Multiline = true;
			this->userfeild->Name = L"userfeild";
			this->userfeild->Size = System::Drawing::Size(417, 30);
			this->userfeild->TabIndex = 2;
			// 
			// LoginBtn
			// 
			this->LoginBtn->Location = System::Drawing::Point(471, 282);
			this->LoginBtn->Name = L"LoginBtn";
			this->LoginBtn->Size = System::Drawing::Size(187, 47);
			this->LoginBtn->TabIndex = 3;
			this->LoginBtn->Text = L"Login";
			this->LoginBtn->UseVisualStyleBackColor = true;
			this->LoginBtn->Click += gcnew System::EventHandler(this, &LoginForm::LoginBtn_Click);
			// 
			// RegisterBtn
			// 
			this->RegisterBtn->Location = System::Drawing::Point(241, 282);
			this->RegisterBtn->Name = L"RegisterBtn";
			this->RegisterBtn->Size = System::Drawing::Size(209, 47);
			this->RegisterBtn->TabIndex = 4;
			this->RegisterBtn->Text = L"Register";
			this->RegisterBtn->UseVisualStyleBackColor = true;
			this->RegisterBtn->Click += gcnew System::EventHandler(this, &LoginForm::RegisterBtn_Click);
			// 
			// passwordFeild
			// 
			this->passwordFeild->Location = System::Drawing::Point(241, 198);
			this->passwordFeild->Multiline = true;
			this->passwordFeild->Name = L"passwordFeild";
			this->passwordFeild->Size = System::Drawing::Size(417, 30);
			this->passwordFeild->TabIndex = 2;
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(869, 466);
			this->Controls->Add(this->RegisterBtn);
			this->Controls->Add(this->LoginBtn);
			this->Controls->Add(this->passwordFeild);
			this->Controls->Add(this->userfeild);
			this->Controls->Add(this->Passlabel);
			this->Controls->Add(this->Usrlabel);
			this->Name = L"LoginForm";
			this->Text = L"LoginForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}

//Login Button
private: System::Void LoginBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ username = userfeild->Text;
	String^ password = passwordFeild->Text;
	if(username->Length == 0 || password->Length == 0) {
		MessageBox::Show("Please fill in all fields.");
		return;
	}
	if (ValidateUser(username, password)) {
		MessageBox::Show("Login Successful!");
		DashboardForm^ dashbaord = gcnew DashboardForm(username);
		dashbaord->Show();
		this->Hide();
	}
	else {
		MessageBox::Show("Invalid Credentials!!!");
	}
}

//Register Button
private: System::Void RegisterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ username = userfeild->Text;
	String^ password = passwordFeild->Text;
	if(username->Length == 0 || password->Length == 0) {
		MessageBox::Show("Please fill in all fields.");
		return;
	}
	if (UserExists(username)) {
		MessageBox::Show("Username Already exist, Please Choose another name!");
		return;
	}
	User^ newUser = gcnew User(username, password);
	SaveUserToFile(newUser);
	MessageBox::Show("User Registered Successfully!");
}
};
}
