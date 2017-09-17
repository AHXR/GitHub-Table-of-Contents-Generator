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
void loadMarkdownGUI();

#include <msclr\marshal_cppstd.h>
#include "global.h"
#include "fileMarkdown.h"
#include "frmMain.h"

using namespace System;
using namespace System::Windows::Forms;
//-----------------------------------------------------------------
void loadMarkdownGUI() {

#ifdef SETTINGS_START_MESSAGE
	std::string s_output = START_MESSAGE;
#else
	std::string s_output;
#endif

	// Translating the openFileDialog string into a standard string, then loading it into readFileMarkdown.
	s_file = msclr::interop::marshal_as< std::string >(GitHubToCMarkdownGenerator::frmMain::openFileDialog->FileName);
	readFileMarkdown(GitHubToCMarkdownGenerator::frmMain::txtProjectName->Text, GitHubToCMarkdownGenerator::frmMain::txtUsername->Text);

	std::vector< std::string >
		s_fetch = getFileMarkdown();

	// Adding line by line into the output then printing it into txtCode.
	for (int i = 0; i < s_fetch.size(); i++) {
		s_output += s_fetch.at(i) + "\r\n";
	}

	GitHubToCMarkdownGenerator::frmMain::txtCode->Text = gcnew String(s_output.c_str());
}
//-----------------------------------------------------------------
[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GitHubToCMarkdownGenerator::frmMain frm;
	Application::Run(%frm);
}
