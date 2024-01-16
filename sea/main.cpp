/*
*
* Author: Mason Swarr <mason.e.swarr@gmail.com
*
* Main file. Entry point for the software engineer assessment.
*
*/

#include "spacecraft.h"
#include <iostream>
#include <vector>
#include <regex>

int main() {
	// Planet location coordinate map as defined in assessment. "0" and "1" denote "-" or "+" repectively.
	const sea::PLANET_MAP PLANET_LOCATIONS{
		{sea::CoordinateDir{0,0,0}, "SEBAS"},
		{sea::CoordinateDir{0,0,1}, "TURK"},
		{sea::CoordinateDir{0,1,0}, "MROW"},
		{sea::CoordinateDir{0,1,1}, "WIEM"},
		{sea::CoordinateDir{1,0,0}, "MIG"},
		{sea::CoordinateDir{1,0,1}, "BRAY"},
		{sea::CoordinateDir{1,1,0}, "PRICE"},
		{sea::CoordinateDir{1,1,1}, "GRACE"}
	};

	sea::spacecraft sc(PLANET_LOCATIONS);
	std::string in;
	std::vector<std::string> out;

	std::regex coord_patt("-?\\d+\\s+-?\\d+\\s+-?\\d+");
	// Infinite loop for user input. Breaks if "exit" is entered by the user.
	while (true) {
		getline(std::cin, in);
		if (in != "exit") {
			// Checks input format. Prints error if incorrect format.
			if (std::regex_match(in, coord_patt)) {
				try {
					out = sc.attitude_input(in);
					std::cout << "Pointing Towards: " << out[1] << " at " << out[0] << std::endl;
				}
				catch (std::exception& exc) {
					std::cerr << exc.what() << std::endl;
				}
			}
			else {
				std::cerr << "Invalid input: " << in << "\nProper format is \"%d %d %d\"" << std::endl;
			}
		}
		else {
			break;
		}
	}
	return 0;
}
