/*
* GitHub Table of Contents Markdown Generator - Simple tool used to generate a ToC.
* Copyright (C) 2017 AHXR
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//-----------------------------------------------------------------
#pragma once

namespace GitHubToCMarkdownGenerator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmMain
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnOpen;
	public: static System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private:

	private:

	private:
	protected:

	private: System::Windows::Forms::GroupBox^  grpBoxCode;
	public: static System::Windows::Forms::RichTextBox^  txtCode;
	private:

	private:

	private: System::Windows::Forms::Button^  btnNumbersBullets;
	public: static System::Windows::Forms::TextBox^  txtProjectName;
	private:
	public: static System::Windows::Forms::TextBox^  txtUsername;

	private:



	private: System::Windows::Forms::Label^  lblAuthor;
	private: System::Windows::Forms::Button^  btnRefresh;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMain::typeid));
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->grpBoxCode = (gcnew System::Windows::Forms::GroupBox());
			this->txtCode = (gcnew System::Windows::Forms::RichTextBox());
			this->btnNumbersBullets = (gcnew System::Windows::Forms::Button());
			this->txtProjectName = (gcnew System::Windows::Forms::TextBox());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->lblAuthor = (gcnew System::Windows::Forms::Label());
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->grpBoxCode->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(13, 13);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(518, 47);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Open README.md File";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &frmMain::btnOpen_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"md";
			this->openFileDialog->FileName = L"README";
			this->openFileDialog->Filter = L"Markdown Files|*.md";
			this->openFileDialog->Title = L"Open README.md file";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &frmMain::openFileDialog_FileOk);
			// 
			// grpBoxCode
			// 
			this->grpBoxCode->Controls->Add(this->txtCode);
			this->grpBoxCode->Location = System::Drawing::Point(13, 66);
			this->grpBoxCode->Name = L"grpBoxCode";
			this->grpBoxCode->Size = System::Drawing::Size(518, 232);
			this->grpBoxCode->TabIndex = 1;
			this->grpBoxCode->TabStop = false;
			this->grpBoxCode->Text = L"Code";
			// 
			// txtCode
			// 
			this->txtCode->Location = System::Drawing::Point(6, 19);
			this->txtCode->Name = L"txtCode";
			this->txtCode->Size = System::Drawing::Size(506, 207);
			this->txtCode->TabIndex = 0;
			this->txtCode->Text = L"";
			// 
			// btnNumbersBullets
			// 
			this->btnNumbersBullets->Location = System::Drawing::Point(13, 305);
			this->btnNumbersBullets->Name = L"btnNumbersBullets";
			this->btnNumbersBullets->Size = System::Drawing::Size(59, 41);
			this->btnNumbersBullets->TabIndex = 2;
			this->btnNumbersBullets->Text = L"Numbers";
			this->btnNumbersBullets->UseVisualStyleBackColor = true;
			this->btnNumbersBullets->Click += gcnew System::EventHandler(this, &frmMain::btnNumbersBullets_Click);
			// 
			// txtProjectName
			// 
			this->txtProjectName->Location = System::Drawing::Point(163, 304);
			this->txtProjectName->Name = L"txtProjectName";
			this->txtProjectName->Size = System::Drawing::Size(362, 20);
			this->txtProjectName->TabIndex = 3;
			this->txtProjectName->Text = L"Project Name";
			// 
			// txtUsername
			// 
			this->txtUsername->Location = System::Drawing::Point(163, 330);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(207, 20);
			this->txtUsername->TabIndex = 4;
			this->txtUsername->Text = L"Username";
			// 
			// lblAuthor
			// 
			this->lblAuthor->AutoSize = true;
			this->lblAuthor->Location = System::Drawing::Point(431, 330);
			this->lblAuthor->Name = L"lblAuthor";
			this->lblAuthor->Size = System::Drawing::Size(94, 13);
			this->lblAuthor->TabIndex = 5;
			this->lblAuthor->Text = L"github.com/AHXR";
			// 
			// btnRefresh
			// 
			this->btnRefresh->Location = System::Drawing::Point(78, 305);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(60, 41);
			this->btnRefresh->TabIndex = 6;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->UseVisualStyleBackColor = true;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &frmMain::btnRefresh_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(543, 358);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->lblAuthor);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->txtProjectName);
			this->Controls->Add(this->btnNumbersBullets);
			this->Controls->Add(this->grpBoxCode);
			this->Controls->Add(this->btnOpen);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"frmMain";
			this->Text = L"GitHub Table of Contents Markdown Generator";
			this->grpBoxCode->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		this->openFileDialog->ShowDialog();
	}
	private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		loadMarkdownGUI();
	}
	private: System::Void btnRefresh_Click(System::Object^  sender, System::EventArgs^  e) {
		loadMarkdownGUI();
	}
private: System::Void btnNumbersBullets_Click(System::Object^  sender, System::EventArgs^  e) {
		toggleNumberBullets();
		loadMarkdownGUI();

		if (getNumberBullets())
			this->btnNumbersBullets->Text = "Bullets";
		else
			this->btnNumbersBullets->Text = "Numbers";
	}
};
}
