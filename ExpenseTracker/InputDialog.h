#pragma once

using namespace System;
using namespace System::Windows::Forms;

public ref class InputDialog : public Form {
private:
    TextBox^ inputBox;
    Button^ okButton;
    Label^ promptLabel;

public:
    String^ InputText;

    InputDialog(String^ prompt, String^ title) {
        this->Text = title;
        this->Width = 300;
        this->Height = 150;
        this->StartPosition = FormStartPosition::CenterParent;

        promptLabel = gcnew Label();
        promptLabel->Text = prompt;
        promptLabel->Top = 10;
        promptLabel->Left = 10;
        promptLabel->Width = 260;
        this->Controls->Add(promptLabel);

        inputBox = gcnew TextBox();
        inputBox->Top = 35;
        inputBox->Left = 10;
        inputBox->Width = 260;
        this->Controls->Add(inputBox);

        okButton = gcnew Button();
        okButton->Text = "OK";
        okButton->Top = 70;
        okButton->Left = 200;
        okButton->Click += gcnew EventHandler(this, &InputDialog::OkButton_Click);
        this->Controls->Add(okButton);
    }

private:
    void OkButton_Click(Object^ sender, EventArgs^ e) {
        this->InputText = inputBox->Text;
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }
};
