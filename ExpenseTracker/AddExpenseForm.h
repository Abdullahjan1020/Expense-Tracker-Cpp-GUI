#pragma once
#include "Expense.h"
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class AddExpenseForm : public System::Windows::Forms::Form {
	public:
		Expense^ NewExpense;
		AddExpenseForm() {
			InitializeComponent();
		}
private:
	System::Windows::Forms::TextBox^ categoryBox;
	System::Windows::Forms::TextBox^ amountBox;
	System::Windows::Forms::DateTimePicker^ datePicker;
	System::Windows::Forms::Button^ savBtn;

	void InitializeComponent() {
		this->categoryBox = (gcnew System::Windows::Forms::TextBox());
		this->amountBox = (gcnew System::Windows::Forms::TextBox());
		this->datePicker = (gcnew System::Windows::Forms::DateTimePicker());
		this->savBtn = (gcnew System::Windows::Forms::Button());

		this->Text = L"Add Expense";
		this->Size = System::Drawing::Size(400, 300);

		//Category Box
		categoryBox->Location = System::Drawing::Point(30, 30);
		categoryBox->Size = System::Drawing::Size(300, 30);
		auto catLabel = gcnew System::Windows::Forms::Label();
		catLabel->Text = L"Category:";
		catLabel->Location = System::Drawing::Point(30, 10);
		catLabel->Size = System::Drawing ::Size(100,20);
		this->Controls->Add(catLabel);

		//Amount Box
		auto amtLabel = gcnew System::Windows::Forms::Label();
		amtLabel->Text = L"Amount:";
		amtLabel->Location = System::Drawing::Point(30, 60);
		amountBox->Size = System::Drawing::Size(300, 30);
		this->Controls->Add(amtLabel);
		amountBox->Location = System::Drawing::Point(30, 80);
		amountBox->Size = System::Drawing::Size(300,30);

		//Date Picker
		datePicker->Location = System::Drawing::Point(30, 130);
		datePicker->Size = System::Drawing::Size(300, 30);

		//Save Button
		savBtn->Text = L"Save";
		savBtn->Location = System::Drawing::Point(30, 180);
		savBtn->Click += gcnew System::EventHandler(this, &AddExpenseForm::savBtn_Click);

		this->Controls->Add(categoryBox);
		this->Controls->Add(amountBox);
		this->Controls->Add(datePicker);
		this->Controls->Add(savBtn);
	}
private:
	void savBtn_Click(Object^ sender, EventArgs^ e) {
		String^ cat = categoryBox->Text;
		double amt;
		if(!Double::TryParse(amountBox->Text, System::Globalization::NumberStyles::Float,System::Globalization::CultureInfo::InvariantCulture,amt)) {
			MessageBox::Show("Invalid amount!");
			return;
		}
		if(amt<=0) {
			MessageBox::Show("Amount must be greater than 0!");
			return;
		}
		NewExpense = gcnew Expense(cat, amt, datePicker->Value);
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
};