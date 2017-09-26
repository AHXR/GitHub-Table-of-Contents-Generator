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
void loadMarkdownGUI(System::String ^ s_path = "");
void loadHistory();

#include <msclr\marshal_cppstd.h>
#include <fstream>
#include "global.h"
#include "fileMarkdown.h"
#include "frmMain.h"
#include "history.h"
#include "global.h"

using namespace System;
using namespace System::Windows::Forms;

ref class G_HIST {
	public: static System::Collections::Generic::List<System::Windows::Forms::ToolStripMenuItem^>^ m_history = gcnew System::Collections::Generic::List<System::Windows::Forms::ToolStripMenuItem^>();
};

//-----------------------------------------------------------------
void loadHistory() {

	// Variable declaration
	std::string
		s_line;
	int
		i_idx = 0;
	char
		c_name[13];

	/*
		Opening up our file stream in read mode. If the file cannot be opened,
		we run the initHistory function (history.cpp). This will reset the whole
		file stream.
	*/
	std::fstream f_history(FILE_HISTORY, std::ios::in);
	if (!f_history.is_open())
		initHistory();

	/*
		The program now loops through the history file, line by line.
		Each line of text that is found inside of the history file is added
		to frmMain's GUI as a ToolStripMenuItem. 

		After all of this is completed, we close the stream.
	*/
	while (std::getline(f_history, s_line)) {
		G_HIST::m_history->Add( gcnew System::Windows::Forms::ToolStripMenuItem() );
		GitHubToCMarkdownGenerator::frmMain::historyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { G_HIST::m_history[i_idx] });
		
		sprintf(c_name, "menuHistory%i", i_idx);
		System::String ^ s_s_name = gcnew String(c_name);
		System::String ^ s_s_path = gcnew String(s_line.c_str());

		G_HIST::m_history[i_idx]->Name = s_s_name;
		G_HIST::m_history[i_idx]->Size = System::Drawing::Size(152, 22);
		G_HIST::m_history[i_idx]->Text = s_s_path;

		i_idx++;
	}
	f_history.close();
}

void loadMarkdownGUI( System::String ^ s_path ) {

#ifdef SETTINGS_START_MESSAGE
	std::string s_output = START_MESSAGE;
#else
	std::string s_output;
#endif

	// Translating the openFileDialog string into a standard string, then loading it into readFileMarkdown.
	if (s_path->Length <= 0) {
		s_file = msclr::interop::marshal_as< std::string >(GitHubToCMarkdownGenerator::frmMain::openFileDialog->FileName);
		s_path = GitHubToCMarkdownGenerator::frmMain::openFileDialog->FileName;
	}
	else
		s_file = msclr::interop::marshal_as< std::string >(s_path);

	readFileMarkdown(GitHubToCMarkdownGenerator::frmMain::txtProjectName->Text, GitHubToCMarkdownGenerator::frmMain::txtUsername->Text);

	std::vector< std::string >
		s_fetch = getFileMarkdown();

	// Adding line by line into the output then printing it into txtCode.
	for (size_t i = 0; i < s_fetch.size(); i++) {
		s_output += s_fetch.at(i) + "\r\n";
	}

	GitHubToCMarkdownGenerator::frmMain::txtCode->Text = gcnew String(s_output.c_str());

	// Once we a GitHub markdown has been added, we are going to also add it to the history file. Then we reset the ToolStrip list.
	addHistory( msclr::interop::marshal_as< std::string >( s_path ) );
	loadHistory();
}
//-----------------------------------------------------------------
[STAThread]
void main(array<String^>^ args) {
	initHistory();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GitHubToCMarkdownGenerator::frmMain frm;
	Application::Run(%frm);
}
