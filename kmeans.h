#ifndef KMEANS_H_
#define KMEANS_H_
#include <iostream>
#include <map>


/*
Struct for one cluster.
clusterLabel(int) -   identifier for cluster 1 through k
kVal(int) 		 - 	  value of k for this cluster (how many clusters in clustering)
centroid(pair) 	 - 	  x/y coordinates of centroid
closestPoint(int) -	  id of point closest to centroid
pointsInCluster(map): point id as key and x/y coords as value

newCluster() - sets kVal, clusterLabel, and centroid with initial values retrieved from config file in part 1
*/
struct K_Cluster {
	bool pointChange = true;
	int clusterLabel;
	int kVal;
	int numPoints = 0;
	std::pair<float,float> centroid;
	int closestPoint = 0;
	std::map<int, std::pair<float,float>> pointsInCluster; 
	
	void newCluster(int k, int label, std::pair<float,float> cent);
}; //K_Cluster

/*
Class for clusterings
allClusters(map): -- allClusters[kval][ith cluster] gives a pointer to the ith cluster for a k of kval.
allPoints(map):  point id as key and x/y coords as value
minK(int) - minimum value of k
maxK(int) - maximum value of k

initPoints() - copies all points into allPoints
storeCluster() - given a value of k and a K_Cluster struct, stores K_Cluster in vector at that k value
calcDistance() - given two float pairs, returns float euclidean distance
calcNewCentroid() - given a value of k and a pointer to a cluster, returns the average of the points in that cluster as a pair of two floats
*/
class K_Means {
	private:
		std::map<int, std::vector<K_Cluster*>> allClusters;  //int is kval, each vector element at ID has cluster for that kval allClusters[i] is one cluster
		std::map<int, std::pair<float,float>> allPoints;
		int minK;
		int maxK;
	public:
		void initPoints(std::map<int, std::pair<float,float>> points);
		void storeCluster(int k, K_Cluster* clust);
		float calcDistance(std::pair<float,float> x1y1, std::pair<float,float> x2y2);
		void calcNewCentroid(int k, int i);
		void initCluster(int k);
		void setMinK(int k);
		void setMaxK(int k);
		int getMinK();
		int getMaxK();
		std::vector<K_Cluster*> getClusters(int k);
		std::vector<std::pair<float,float>> getPointValues(int k, int i);
		void calcShortest(int k);
		bool getPointChange(int k, int i);
		void finalizeCluster(int k, int i, K_Means km);
		void erasePointsInCluster(int k, int i);
		void assignPoints(int k, int i);
		//testing functions
		//void printPoints();
		//void printClusters();
}; //K_Means



#endif
