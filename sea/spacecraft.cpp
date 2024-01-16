/*
*
* Author: Mason Swarr <mason.e.swarr@gmail.com
*
* Implementation for the spacecraft class.
*
*/

#include "spacecraft.h"
#include <sstream>
#include <vector>
#include <regex>

// namespace for "software engineer assessment"
namespace sea {

	/*
	* Takes x, y, and z coordinates and changes cur_attitude accordingly.
	* 
	* Parameters:
	*	att_x	: const int&	: Coordinate value for x axis
	*	att_y	: const int&	: Coordinate value for y axis
	*	att_z	: const int&	: Coordinate value for z axis
	* 
	* Returns: None
	* 
	* Throws: None
	* 
	*/
	void spacecraft::change_attitude(const int& att_x, const int& att_y, const int& att_z) {
		cur_attitude[0] += att_x;
		cur_attitude[1] += att_y;
		cur_attitude[2] += att_z;
	}

	/*
	* Uses cur_attitude to determine which planet is being pointed at and updates cur_planet depending on the values in pm.
	* Intended to be used after change_attitude().
	*
	* Parameters: None
	* 
	* Returns: None
	* 
	* Throws: None
	* 
	*/
	void spacecraft::determine_planet() {
		// Convert cur_attitude coordinates to +/- directions
		auto determine_sign = [](const int& i) -> const bool {return i > -1; }; // '0' is considered positive for simplicity
		CoordinateDir converted_att = { determine_sign(cur_attitude[0]), determine_sign(cur_attitude[1]), determine_sign(cur_attitude[2]) };

		cur_planet = planet_map.at(converted_att);
	}

	/*
	* Default constructor.
	* 
	* Parameters:
	*	pm		: const sea::PLANET_MAP&	: Planet location coordinate map
	*	att_x	: const int&				: Coordinate value for x axis. Default 0.
	*	att_y	: const int&				: Coordinate value for y axis. Default 0.
	*	att_z	: const int&				: Coordinate value for z axis. Default 0.
	* 
	* Returns: None
	* 
	* Throws: None
	* 
	*/
	spacecraft::spacecraft(const PLANET_MAP& pm, const int& att_x, const int& att_y, const int& att_z) {
		planet_map = pm;
		cur_attitude[0] = att_x;
		cur_attitude[1] = att_y;
		cur_attitude[2] = att_z;
	}

	/*
	* Class destructor:
	* Does nothing as there are no resources to cleanup or release.
	*
	* Parameters: None
	* 
	* Returns: None
	* 
	* Throws: None
	* 
	*/
	spacecraft::~spacecraft(){}

	/*
	* Returns the name of which planet is currently pointed at.
	*
	* Parameters: None
	* 
	* Returns:
	*	const string&	: Name of planet the spacecraft is currently pointing towards.
	* 
	* Throws: None
	* 
	*/
	const string& spacecraft::get_current_planet() {
		return cur_planet;
	}

	/*
	* Returns the current attitude as a three element array.
	*
	* Parameters: None
	* 
	* Returns:
	*	const int*	: Three element array representing the current attitude. Index 0 as 'x', index 1 as 'y', and index 2 as 'z' coordinates.
	* 
	* Throws: None
	* 
	*/
	const int* spacecraft::get_current_attitude() {
		return cur_attitude;
	}

	/*
	* Takes a space separated coordinate position string, splits the coordinates, and calls change_attitude() and determine_planet().
	*
	* Parameters:
	*	attitude_adj				: const string&	: Space separated coordinate position
	* 
	* Returns:
	*	std::vector<std::string>	: Contains two elements; index 0 as the current attitude with the format of "%d,%d,%d"
	*								  and index 1 as the name of the planet the spacecraft is pointing towards.
	* 
	* Throws:
	*	std::invalid_argument		: If attitude_adj is the wrong format.
	* 
	*/
	const vector<string> spacecraft::attitude_input(const string& attitude_adj) {
		// Use regex to check input format. Throw exception if incorrect format.
		std::smatch m;
		const std::regex coord_patt("(-?\\d+)\\s+(-?\\d+)\\s+(-?\\d+)");

		if (std::regex_search(attitude_adj, m, coord_patt)) {
			change_attitude(stoi(m.str(1)), stoi(m.str(2)), stoi(m.str(3)));
			determine_planet();

			return vector<string>{ std::to_string(cur_attitude[0]) + "," + std::to_string(cur_attitude[1]) + "," + std::to_string(cur_attitude[2]), cur_planet };
		}
		else {
			string err_msg = "Invalid attitude input format: " + attitude_adj + "\nProper format is \"%d %d %d\"";
			throw std::invalid_argument(err_msg);
		}
	}
}// namespacce
