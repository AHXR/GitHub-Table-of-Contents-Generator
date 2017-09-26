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
#include "fileMarkdown.h"
#include "global.h"
#include <fstream>
#include <string>
#include <sstream>
#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;

std::vector< std::string > s_stored;
int getLineHeaderIndex(std::string s_line);
int i_header_count[MAX_HEADER_COUNT];
//-----------------------------------------------------------------
void readFileMarkdown(System::String^ projectName, System::String^ username) {
	// Resetting variables.
	s_stored.clear();
	for (int i = 0; i < MAX_HEADER_COUNT; i++) i_header_count[i] = 0;

	// Declaring
	std::string s_line;
	int i_idx;

	// Reading the file line by line.
	std::ifstream
		ss_file(getFilePath());

	for (s_line; getline(ss_file, s_line); ) {
		if (s_line[0] == '#') {

			// Storing the related lines into an array.
			s_stored.push_back(s_line);

			// Getting the type of header and placing it on the counter.
			i_idx = getLineHeaderIndex(s_line);
#ifdef DEBUG_MODE
			printf("%s - %i\r\n", s_line.c_str(), i_idx);
#endif
			if (i_idx != -1)
				i_header_count[i_idx] ++;
		}
	}

	/*
		Now we're going to slim down on the README file so we can get an accurate calculation
		of what actually needs to be in the Table of Contents.

		Here we are checking and deleting any lines that seem to not be related to table of contents.
	*/
	for (size_t i = 0; i < MAX_HEADER_COUNT; i++) {
		if (i_header_count[i] < 2) {

			/*
				Once we discovered a header that has appeared less than twice (assuming it's not being used for a header)
				The program looks through the s_stored string and finds any lines that fall under that header then
				deletes the line accordingly.
			*/
			for (size_t x = 0; x < s_stored.size(); x++) {
				if (getLineHeaderIndex(s_stored.at(x)) == i) {

#ifdef DEBUG_MODE
					printf("DELETE LINE: %s - %i (IDX: %i)\r\n", s_stored.at(i).c_str(), i_header_count[i], i);
#endif
					// Deleting the index
					s_stored.erase(s_stored.begin() + i);
				}
			}
		}
	}

	/*
		Adding the list markdown code for the Table of Contents.
		But first we need to get rid of those hashtags. This was a very
		stressful process for me. After a countless hours, I finally got it
		to work.
	*/
	std::vector< std::string > s_old = s_stored; // For later usage.
	std::string s_tmp;
	int i_pos;

	// Looping through the original s_stored string.
	for (size_t i = 0; i < s_stored.size(); i++) {
		i_pos = 0;

		/*
			My ideal plan was to use substr to completely cut off any hashtags
			that started off the line. So what I did was, I looped through the starting
			characters of the string exacting to the amount of possible header hashtags.

			Each time the condition found a hashtag or a space, it added more to the counter.
			This gave me the perfect position to substring what was stored at the element cell.
		*/
		for (size_t x = 0; x < MAX_HEADER_COUNT; x++) {
			if (s_stored.at(i)[x] != '#' && s_stored.at(i)[x] != ' ')
				break;
			i_pos++;
		}
		s_tmp = s_stored.at(i).substr(i_pos);


		/*
			The second to last clean-up code block was a little forced, but I was able
			to get it to work. This check-up basically formats the URL of the GitHub link.

			I noticed how GitHub formats the Table of Content tags differently from a regular
			URL.
		*/
		std::string
			s_format = s_tmp;
		bool
			b_check = false;

		// Looping through the strength and finding any illegal characters.
		for (size_t i = 0; i < s_format.length(); i++) {

			/*
				I thought this would be much easier because I can just use string::replace on the illegal
				characters, however ... GitHub urls seems to avoid using triple dashes. With that being said
				I had to manually search through the loop index to make sure that didn't happen. Triple+ dashes occur
				in this situation:

				"Hello + World" 
				"Video - Pictures"

				As you can see from those examples, there are 3 illegal characters. The 3 spaces between the words and 
				there is also a symbol being used. Simply replacing all of those with dashes won't work with the URL.
			*/
			if (i > 2 && s_format[i - 1] == '-' && s_format[i - 2] == '-')
				b_check = true;
			else
				b_check = false;

			if (!b_check) {
				if (s_format[i] == ' ') // All spaces are changed to dashes.
					s_format[i] = '-';
				else if ((!isalnum(s_format[i]) && s_format[i] != '-')) // All illegal characters that aren't dashes are changed.
					s_format.replace(i, 1, "-");
			}
			else  // If there is a triple dash, fine. We need to take a step back and overwrite 2 of the characters ahead of time.
				s_format.replace(i-1, 2, "-");
		}

		
		std::transform(s_format.begin(), s_format.end(), s_format.begin(), ::tolower); // The URL format is always in lowercase.
		s_tmp.insert(0, "["); s_tmp += "](https://github.com/" + marshal_as< std::string >(username) + "/" + marshal_as< std::string >(projectName) + "#" + s_format + ")";
		s_stored.at(i).assign("* " + s_tmp); // Adding the asterick while I'm at it.
	}

	/*
		After all the clean-up is done, now we're going to have to organize the code based off of 
		the type of headers listed. This was a bit draining as well. All this block of code does is 
		sort the list based off of header index.
	*/
	bool
		i_cont = false;
	for (size_t i = 0; i < s_old.size() - 1; i++) {
		if (!i_cont) {
			if (getLineHeaderIndex(s_old.at(i)) > getLineHeaderIndex(s_old.at(i + 1))) {
				s_stored.at(i).insert(0, "  ");
				i_cont = true;
			}
			else if (getLineHeaderIndex(s_old.at(i)) < getLineHeaderIndex(s_old.at(i + 1))) {
				s_stored.at(i+1).insert(0, "  ");
				i_cont = true;
			}
		}
		else {
			if (getLineHeaderIndex(s_old.at(i)) == getLineHeaderIndex(s_old.at(i + 1)))
				s_stored.at(i + 1).insert(0, "  ");
			else 
				i_cont = false;
		}
	}

	if (getNumberBullets())
		numberFileMarkdown();
}

int getLineHeaderIndex(std::string s_line ) {
	if (s_line[0] == '#' && s_line[1] != '#') // H1
		return HEADER_ONE_IDX;
	else
		if (s_line[2] != '#') // H2
			return HEADER_TWO_IDX;
		else
			if (s_line[3] != '#') // H3
				return HEADER_THREE_IDX;
			else
				if (s_line[4] != '#') // H4
					return HEADER_FOUR_IDX;
				else
					if (s_line[5] != '#') // H5
						return HEADER_FIVE_IDX;
					else
						if (s_line[6] != '#') // H6
							return HEADER_SIX_IDX;

	return -1;
}

bool numberFileMarkdown() {
	if (s_stored.size() <= 0)
		return false;

	// Creating the needed variables to properly sort the lists.
	int i_list_spot[2] = { 0, 0 };
	bool b_sublisting;

	for (size_t i = 0; i < s_stored.size(); i++) {
		if (s_stored.at(i)[0] == '*') { // Outside List
			
			/* 
				If we recently started listing a sublist, we need to reset the counter. This is so
				listing doesn't occur like:

				1. A
				2. B
					3. C
					4. D
				5. E
			*/
			if (b_sublisting) {
				i_list_spot[1] = 0;
				b_sublisting = false;
			}
			i_list_spot[0] ++;

			/*
				There are several ways to do this. Streaming works too. But I wanted to just simplify this
				and format it through sprintf. 
			*/
			char c_tmp[3];
			sprintf(c_tmp, "%d", i_list_spot[ 0 ]);

			// Clearing out the beginning of the strong to write down the numbers.
			s_stored.at(i).replace(0, 1, c_tmp);
			s_stored.at(i).insert(s_stored.at(i).begin() + strlen(c_tmp), '.');
		}
		else if( s_stored.at(i)[0] == ' ') { // Sublist

			i_list_spot[1] ++;

			char c_tmp[5];
			sprintf(c_tmp, "  %d", i_list_spot[1]);

			s_stored.at(i).replace(0, 3, c_tmp);
			s_stored.at(i).insert(s_stored.at(i).begin() + strlen(c_tmp), '.');
			
			b_sublisting = true;
		}
	}

	return true;
}

std::vector< std::string > getFileMarkdown() {
	return s_stored;
}