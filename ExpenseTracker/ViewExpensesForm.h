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
		String^ dateStr = "";

		InputDialog^ catDialog = gcnew InputDialog("Enter category:", "Add Expense");
		if (catDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			category = catDialog->InputText;

		InputDialog^ amtDialog = gcnew InputDialog("Enter amount:", "Add Expense");
		if (amtDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			amountStr = amtDialog->InputText;

		InputDialog^ dateDialog = gcnew InputDialog("Enter date (YYYY-MM-DD):", "Add Expense");
		if (dateDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			dateStr = dateDialog->InputText;


		if(!String::IsNullOrEmpty(category)&&!String::IsNullOrEmpty(amountStr)&&!String::IsNullOrEmpty(dateStr)) {
			try {
				double amount = Convert::ToDouble(amountStr);
				DateTime date = DateTime::Parse(dateStr);
				Expense^ newExpense = gcnew Expense(category, amount, date);
			
				expenseList->Add(newExpense);
				expenseGrid->Rows->Add(newExpense->Category, newExpense->Amount.ToString("F2"), newExpense->Date.ToShortDateString());
			}
			catch (FormatException^ ex) {
				MessageBox::Show("Invalid input format. Please try again.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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