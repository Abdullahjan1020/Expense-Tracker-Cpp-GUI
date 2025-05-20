#pragma once
#include "Expense.h"
#include"InputDialog.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualBasic;
public ref class ViewExpensesForm : public Form {
private:
	DataGridView^ expenseGrid;
	List<Expense^>^ expenseList;
public:
	ViewExpensesForm(List<Expense^>^ expenses) {
		this->expenseList = expenses;
		InitializeComponent();
		LoadExpensesIntoGrid();
	}
private:
	void InitializeComponent() {
		this->Text = "View Expenses";
		this->Size = System::Drawing::Size(600, 400);

		expenseGrid = gcnew DataGridView();
		expenseGrid->Dock = DockStyle::Fill;
		expenseGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		expenseGrid->ReadOnly = true;
		expenseGrid->AllowUserToAddRows = false;
		expenseGrid->ColumnCount = 3;

		expenseGrid->Columns[0]->Name = "Category";
		expenseGrid->Columns[1]->Name = "Amount";
		expenseGrid->Columns[2]->Name = "Date";

		//Export Button
		Button^ exportBtn = gcnew Button();
		exportBtn->Text = "Export";
		exportBtn->Dock = DockStyle::Bottom;
		exportBtn->Click += gcnew EventHandler(this, &ViewExpensesForm::ExportButton_Click);

		//Add Button
		Button^ addBtn = gcnew Button();
		addBtn->Text = "Add Expense";
		addBtn->Dock = DockStyle::Bottom;
		addBtn->Click += gcnew EventHandler(this, &ViewExpensesForm::AddButton_Click);

		//Delete Button
		Button^ deleteBtn = gcnew Button();
		deleteBtn->Text = "Delete Selected";
		deleteBtn->Dock = DockStyle::Bottom;
		deleteBtn->Click += gcnew EventHandler(this, &ViewExpensesForm::DeleteButton_Click);

		this->Controls->Add(expenseGrid);
		this->Controls->Add(addBtn);
		this->Controls->Add(deleteBtn);
		this->Controls->Add(exportBtn);
	}
	void LoadExpensesIntoGrid() {
		for each (Expense ^ exp in expenseList) {
			expenseGrid->Rows->Add(exp->Category, exp->Amount.ToString("F2"), exp->Date.ToShortDateString());
		}
	}

	void ExportButton_Click(Object^ sender, EventArgs^ e) {
		SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
		saveDialog->Filter = "CSV files (*.csv)|*.csv|All files (*.*)|*.*";
		saveDialog->Title = "Exported_Expenses.csv";

		if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = saveDialog->FileName;
			try {
				System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(filePath);
				writer->WriteLine("Category,Amount,Date");
				for each(DataGridViewRow^ row in expenseGrid->Rows) {
					if (!row->IsNewRow) {
						String^ category = row->Cells[0]->Value->ToString();
						String^ amount = row->Cells[1]->Value->ToString();
						String^ date = row->Cells[2]->Value->ToString();
						writer->WriteLine(category + "," + amount + "," + date);
					}
				}
				writer->Close();
				MessageBox::Show("Expenses exported successfully!", "Export", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error exporting expenses: " + ex->Message, "Export Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
			
	}

	void AddButton_Click(Object^ sender, EventArgs^ e) {
		String^ category = "";
		String^ amountStr = "";
		DateTime selectedDate;

		InputDialog^ catDialog = gcnew InputDialog("Enter category:", "Add Expense");
		if (catDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			category = catDialog->InputText;

		InputDialog^ amtDialog = gcnew InputDialog("Enter amount:", "Add Expense");
		if (amtDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			amountStr = amtDialog->InputText;

		//Date Picker
		Form^ dateForm = gcnew Form();
		dateForm->Text = "Select Date";
		dateForm->Size = System::Drawing::Size(250, 150);

		DateTimePicker^ datePicker = gcnew DateTimePicker();
		datePicker->Format = DateTimePickerFormat::Short;
		datePicker->Location = System::Drawing::Point(30, 20);
		datePicker->Width = 150;

		Button^ okButton = gcnew Button();
		okButton->Text = "OK";
		okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		okButton->Location = System::Drawing::Point(80, 60);
		dateForm->AcceptButton = okButton;

		dateForm->Controls->Add(datePicker);
		dateForm->Controls->Add(okButton);

		if (dateForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			selectedDate = datePicker->Value;
		}
		else {
			return;
		}
		if (!String::IsNullOrEmpty(category) && !String::IsNullOrEmpty(amountStr)) {
			try {
				double amount = Convert::ToDouble(amountStr);
				Expense^ newExpense = gcnew Expense(category, amount, selectedDate);
				expenseList->Add(newExpense);
				expenseGrid->Rows->Add(newExpense->Category, newExpense->Amount.ToString("F2"), newExpense->Date.ToShortDateString());
			}
			catch (FormatException^ ex) {
				MessageBox::Show("Invalid amount format. Please enter a valid number.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	void DeleteButton_Click(Object^ sender, EventArgs^ e) {
		if (expenseGrid->SelectedRows->Count > 0) {
			for each (DataGridViewRow ^ row in expenseGrid->SelectedRows) {
				if (!row->IsNewRow) {
					int index = row->Index;
					expenseGrid->Rows->RemoveAt(index);
					if (index < expenseList->Count) {
						expenseList->RemoveAt(index);
					}
				}
			}
		}
		else {
			MessageBox::Show("Please select a row to delete.", "Delete Expense", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

};