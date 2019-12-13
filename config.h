#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

//Centroid stores the number of centroids and placement of said centroids from config.txt files
struct Centroid {
	int num_clusters;  // Stores the number of clusters in a given Centroid
	std::vector<int> place;  // Stores the position of each centroid
};  // Centroid

//Point stores the ID and coordinates of points from points.txt files
struct Point {
	int id;  // Stores the unique ID for each point
	float x;  // Stores the x coordinate for each point
	float y;  // Stores the y coordinate for each point
};  // Point

//Config stores vectors for Centroids and Points, as well as the parse functions, which create and populate Centroids and Points
class Config {
    private:
	//DATA
	std::string pointsfile;  // Stores the filename of a points.txt file from a config.txt file
	int min_clusters;  // Stores the minimum number of clusters from a config.txt file
	int max_clusters;  // Stores the maximum number of clusters from a points.txt file
	std::vector<Centroid> centroid_list;  // Stores all Centroids from a config.txt file
	std::vector<Point> point_list;  // Stores all Points from a points.txt file
    public:
	//FUNCTIONS
	bool parse_config();  // Populates Centroids using config.txt files
	void parse_points();  // Populates Points using points.txt files

	//ACCESSORS
	std::string get_pointsfile();  // Returns name of points file from a config.txt file
	int get_min_clusters();  // Returns the minimum number of clusters from a config.txt file
	int get_max_clusters();  // Returns the maximum number of clusters from a config.txt file
	std::vector<Centroid>& get_centroid_list();  // Returns a vector of all Centroids from a config.txt file
	std::vector<Point>& get_point_list();  // Returns a vector of all Points from a points.txt file
};  // Config

#endif
