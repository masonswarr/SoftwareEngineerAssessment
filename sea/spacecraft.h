/*
* 
* Author: Mason Swarr <mason.e.swarr@gmail.com
* 
* Header file for the spacecraft class.
* 
*/

#ifndef spacecraft_h
#define spacecraft_h

#include <string>
#include <map>
#include <vector>

// namespace for "software engineer assessment"
namespace sea {
	using std::string;
	using std::map;
	using std::vector;

	/*
	* Struct to use as map keys. The members store the attitude values as "0" or "1", denoting "-" or "+" repectively. 
	*/
	struct CoordinateDir {
		bool x;
		bool y;
		bool z;
		
		// Operator overload to allow use as a map key
		bool operator<(const CoordinateDir & cd) const {
			return x < cd.x || x == cd.x && y < cd.y || x == cd.x && y == cd.y && z < cd.z;
		}

		// Operator overload to allow use as a map key
		bool operator==(const CoordinateDir& cd) const {
			return x == cd.x && y == cd.y && z == cd.z;
		}
	};

	using PLANET_MAP = map < CoordinateDir, string >;

	/*
	* Class representation of a spacecraft.
	* 
	* Responsible for tracking current attitude and which planet the spacecraft is pointing towards.
	* Also handles attitude change requests and processes them accordingly.
	*/
	class spacecraft {
		int cur_attitude[3]{ 0, 0, 0 }; // Current attitude
		string cur_planet{ "" }; // Current planet
		PLANET_MAP planet_map; // PLANET_MAP defining planet coordinates
		/* 
		* change_attitude():
		* Takes x, y, and z coordinates and changes cur_attitude accordingly.
		*/
		void change_attitude(const int& att_x, const int& att_y, const int& att_z);
		/* 
		* determine_planet():
		* Uses cur_attitude to determine which planet is being pointed at and updates cur_planet depending on the values in pm.
		* Intended to be used after change_attitude().
		*/
		void determine_planet();
	public:
		/* 
		* Default constructor:
		* Required sea::PLANET_MAP for determining planet directions.
		* Optional parameters used to set initial attitude using x, y, and z coordinates.
		*/
		spacecraft(const PLANET_MAP& pm, const int& att_x = 0, const int& att_y = 0, const int& att_z = 0);
		/*
		* Class destructor:
		* Does nothing as there are no resources to cleanup or release.
		*/
		~spacecraft();
		/* 
		* get_current_planet():
		* Returns the name of which planet is currently pointed at.
		*/
		const string& get_current_planet();
		/*
		* get_current_attitude():
		* Returns the current attitude as a three element array, index 0 as 'x', index 1 as 'y', and index 2 as 'z' coordinates.
		*/
		const int* get_current_attitude();
		/*
		* attitude_input():
		* Takes a space separated coordinate position string, splits the coordinates, and calls change_attitude() and determine_planet().
		* Returns a vector<string> containing two elements; index 0 as the current attitude with the format of "%d,%d,%d"
		* and index 1 as the name of the planet the spacecraft is pointing towards.
		*/
		const vector<string> attitude_input(const string& attitude_adj);
	};
}// namespace

#endif // end def spacecraft_h
