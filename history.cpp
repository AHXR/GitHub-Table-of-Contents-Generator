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
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "global.h"
#include "history.h"
//-----------------------------------------------------------------
static std::fstream f_history;

void addHistory(std::string path) {

	// Variable declaration
	std::string s_tmp;
	std::vector< std::string > s_data;
	int 
		i_count = 0;
	bool
		b_dup;

	/*
		I'm closing the f_history stream just in case I left it open somewhere.
		Even if there is no file stream, it's better safe than sorry. 
	*/
	f_history.close();

	/*
		Here we open the file stream to read line by line. Each line that is read is 
		stored inside of the s_data vector and i_count proceeds to add up.
	*/
	f_history.open(FILE_HISTORY, std::ios::in);

	while (std::getline(f_history, s_tmp)) {
		s_data.push_back(s_tmp);
		i_count++;
	}

	// Inserting a new element to the history list and deleting the oldest row.
	if (i_count == 10) {
		s_data.emplace(s_data.begin(), path);
		s_data.erase(s_data.end() - 1);
	}
	else
		s_data.push_back(path);

	// Closing the file so we can open it again in another mode.
	f_history.close();
	f_history.open(FILE_HISTORY, std::ios::out);

	/*
		i_dont_copy is a variable that's going to store the index of each s_data index
		that is a potential duplicate. We don't want the program to add the same file when
		it's already in the history.
	*/
	std::vector< int > i_dont_copy;

	for (int i = 0; i <= i_count; i++) {

		// Checking for duplicates
		b_dup = false; // RESET
		for (int x = 0; x <= i_count; x++) {

			/*
				Starting off by checking if there is even real data inside of this vector index.
				After we are going to compare the current idx (i), with the match search idx (x).

				If we find something that might be a potential match, we store it in i_dont_copy.
			*/
			if (s_data[i].length() > 0 && s_data[x].length() > 0) {
				if (s_data[i] == s_data[x] && i!=x ) {
					i_dont_copy.push_back(x);
					break;
				}
			}
		}


		/*
			We're going to look through the i_dont_copy vector and if the current looped index (i)
			is found inside of i_don't_copy, it's a duplicate. Therefore we will not store it in the
			history file.
		*/
		for (size_t x = 0; x < i_dont_copy.size(); x++) {
			if (i_dont_copy[x] == i) {
				b_dup = true;
				break;
			}
		}

		if(!b_dup )
			f_history << s_data[i] << std::endl;
	}

	// Opening for reading once more.
	f_history.open(FILE_HISTORY, std::ios::in);
}

void initHistory() {

	// Checking if the history file (FILE_HISTORY) exists. If not, we create one.
	if (!fileExists(FILE_HISTORY)) {
		#ifdef DEBUG_MODE
			printf("History file does not exist. Creating one now.");
		#endif

		f_history.open(FILE_HISTORY, std::ios::out);
		f_history << std::flush;
		f_history.close();

		#ifdef DEBUG_MODE
			printf("History file created at \"%s\"", FILE_HISTORY);
		#endif
	}
}

std::fstream & fetchHistoryStream() {
	return f_history;
}

/*
	Checks if the file exists without the need of opening and closing it.
		Taken from: https://stackoverflow.com/a/6296808
*/
bool fileExists(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}