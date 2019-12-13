#include "config.h"

//Populates Centroids from config.txt files, gets points.txt filename
bool Config::parse_config() {
	bool isfile;  // Stores whether the file exists, skips functionality in main.cpp if false
	std::ifstream infile;  // Stores the config.txt file
	std::string infilename;  // Stores the config.txt filename
	std::string pointsfile;  // Stores the points.txt filename
	int min_clusters;  // Stores the minimum number of clusters
	int max_clusters;  // Stores the maximum number of clusters

	std::cout << "Enter config filename\n";  //Gets config.txt filename
	getline(std::cin, infilename);		 //
	infile.open(infilename);  // Assignes infile to the config.txt filename specified by the user
	if(infile.is_open()) {  //Checks for if the file entered by the user exists
		isfile = true;  // Allows functionality in main.cpp to continue if true
		std::string str;  // Temporary string used to store text from infile
		
		//Gets input:<filename> from infile
		getline(infile, str, ':');
		infile >> pointsfile;
		this->pointsfile = pointsfile;
		
		//Gets k-mean min:<minimum number of clusters> from infile
		getline(infile, str, ':');
		infile >> min_clusters;
		this->min_clusters = min_clusters;
		
		//Gets k-mean max:<maximum number of clusters> from infile
		getline(infile, str, ':');
		infile >> max_clusters;
		this->max_clusters = max_clusters;
		
		//Gets the number of clusters and placement of said clusters i.e. 2: 11 24
		while(infile.peek() != EOF) {
			Centroid centroid;
			std::stringstream sstr;  // Stores one line of infile at a time for processing
			int place;

			infile >> centroid.num_clusters;
			getline(infile, str);
			sstr << str;
			while(sstr.peek() != EOF) {
				sstr >> str;
				if(std::stringstream(str) >> place) {
					centroid.place.push_back(place);
				}
			}
			this->get_centroid_list().push_back(centroid);
		}
		std::cout << "Total number of k-values to be tested: " << this->get_centroid_list().size() << std::endl;
	}
	else {
		isfile = false;  // Prevents functionality in main.cpp from continuing if false
	}
	return isfile;
};  // parse_config

//Populates Points from points.txt files
void Config::parse_points() {
	std::ifstream infile;  // Stores points.txt file
	int id;  // Stores the unique ID of a Point
	float x, y;  // Stores the coordinates of a Point
	
	infile.open(this->get_pointsfile());  // Puts data from the points.txt file into infile
	if(infile.is_open()) {
		//Populates data for each Point
		while(infile >> id >> x >> y) {
			Point point;
			point.id = id;
			point.x = x;
			point.y = y;
			this->get_point_list().push_back(point);
		}
	}
	std::cout << "Total number of points: " << this->get_point_list().back().id << std::endl;
};  // parse_points

//Returns the points.txt filename
std::string Config::get_pointsfile() {
	return this->pointsfile;
};  // get_file

//Returns the minimum number of clusters
int Config::get_min_clusters() {
	return this->min_clusters;
};  // get_min_clusters

//Returns the maximum number of clusters
int Config::get_max_clusters() {
	return this->max_clusters;
};  // get_max_clusters

//Returns a vector of all Centroids
std::vector<Centroid>& Config::get_centroid_list() {
	return this->centroid_list;
};  // get_centroid_list

//Returns a vector of all Points
std::vector<Point>& Config::get_point_list() {
	return this->point_list;
};  // get_point_list
