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
#ifndef G_GLOBAL
#define G_GLOBAL

// #define SETTINGS_START_MESSAGE
// #define DEBUG_MODE

#define MAX_HEADER_COUNT 7
#define HEADER_ONE_IDX 0
#define HEADER_TWO_IDX 1
#define HEADER_THREE_IDX 2
#define HEADER_FOUR_IDX 3
#define HEADER_FIVE_IDX 4
#define HEADER_SIX_IDX 5
#define START_MESSAGE "Here are all the lines we're assuming that you want to be listed in your table of contents: \r\n\r\n"

#include <string>

extern std::string s_file;
extern bool b_numbers;
extern std::string getFilePath();
extern void toggleNumberBullets();
extern bool getNumberBullets();
#endif