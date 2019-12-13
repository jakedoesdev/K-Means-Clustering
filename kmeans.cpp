/*
Author:  Jacob Everett (jae0204)
Class:  CSCE2110
Instructor:  Professor Helsing

Notes/Issues: This portion of this program takes the points read in from the points file, organizes them into clusters based around the centroids read in from the config file, and then repeatedly recalculates and reassigns 
points until clustering is complete. We were instructed to finish clustering when no points changed clusters between two consecutive assignments, but I was not able to figure out how to determine whether the points in
a cluster from this assignment matched the points in the cluster in the previous assignment. As a hacky fix in order to produce somewhat reasonable output, I chose to base whether or not a clustering was
complete on whether or not consecutive recalculations of centroids resulted in the same centroid. My logic was that if centroids didn't change then neither did points, but I believe this may have introduced
some small errors into my data, sometimes resulting in final clusters of slightly different sizes with, in some cases, slightly different closest points. I think that's the issue, at least.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include "kmeans.h"

/*
initCluster()
Given a value of k, initCluster() calls calcDistance to find the distance between each point in allPoints and each centroid for that value of k in allClusters.
That distance is stored in float tmpDist, which is stored in the vector distList. Once all distances have been calculated and stored, distList is iterated through to find the shortest distance.
The point that corresponds to that distance is added to the pointsInCluster map variable of the K_Cluster object stored in allClusters.

Storage location example:  if k is 3, a point that is closest to the 3rd centroid will be stored in allClusters[3(kval)][] 
*/
void K_Means::initCluster(int k)
{
	std::vector<float> distList;
	K_Means km;

	//testing outputs
	//if (k == 2)
	//{
	//	std::cout << "***************************************INIT CYCLE***************************************************" << std::endl;
	//}

	for (int i = 0; i < allPoints.size(); i++)
	{
		//temporary variables to store points and centroids for distance calculations
		std::pair<float,float> tmpPt;
		std::pair<float,float> tmpCent;
		float tmpDist = 0.0;
		int assignLoc = 0;
		
		//set tmpPt equal to first point (ids start at 1, 1 is map key for first point)
		tmpPt = allPoints[i+1];
		
		
		//for each centroid in this value of k, calculate the distance to this point and store it in the same order it is retrieved in distList
		//if k is 2, distList[0] will contain the distance from the first point to the first centroid, 
		//and distList[1] will contain the distance from the first point to the second centroid, distList[2] the second point first centroid distance, etc.
		for (int j = 0; j < k; j++)
		{
			
			tmpCent = allClusters[k][j]->centroid;
			tmpDist = km.calcDistance(tmpPt, tmpCent);
			distList.push_back(tmpDist);	
		}
		
		//for each distance in distList and each cluster in this clustering, compare distance to tmpShortest (set equal to a value outside the scope of possible distances),
		//if the current distance is longer than tmpShortest, do nothing
		//if it is shorter, set tmpShortest equal to that distance
		//each distance (j), each value of k (l)
		for (int j = 0; j < distList.size(); j++)
		{
			float tmpShortest = 999999;
			for (int l = 0; l < k; l++)
			{
				if (distList[l] > tmpShortest)
				{
					//next l
				}
				else if (distList[l] < tmpShortest)
				{
					tmpShortest = distList[l];
					assignLoc = l;
				}	
			}
		}
		
		//insert the point into the map of points inside the cluster it was assigned to with its id (i+1) as key and tmpPt pair as value
		//k - map key for vector of clusters corresponding to that k
		//assignLoc - where the particular cluster this point is being assigned to is found. if the point is being assigned to the first cluster in its clustering, loc = 0
		allClusters[k][assignLoc]->pointsInCluster.insert({i+1, tmpPt});
		allClusters[k][assignLoc]->numPoints++;
		
		//output for testing
		// if (k == 2)
		// {
			// std::cout << "ID(i+1): " << i+1 << " added to cluster: " << allClusters[k][assignLoc]->clusterLabel << std::endl;
		// }
		
		distList.clear();	
	} //end loop through points
} //initCluster
	
/*
Given a value of k and an int representing the cluster to calculate, calcNewCentroid calculates a new centroid for that cluster by
dividing the sums of x and y coordinates by the number of points in the clustering and returning this value to the caller as a pair of floats.
If the previous centroid is the same as this centroid, pointChange is set to false and clustering is complete.
*/
void K_Means::calcNewCentroid(int k, int i)
{
	float x = 0;
	float y = 0;
	std::pair<float,float> newCenter;
	std::pair<float,float> oldCenter;
	
	oldCenter = allClusters[k][i]->centroid;
	
	//get sum of all x coords
	for (auto it : allClusters[k][i]->pointsInCluster)
	{
		x += it.second.first;
	}
	
	//get sum of all y coords
	for (auto it : allClusters[k][i]->pointsInCluster)
	{
		y += it.second.second;
	}
	
	//get average of x and y coords
	x = x/(float)(allClusters[k][i]->numPoints);
	y = y/(float)(allClusters[k][i]->numPoints);
	
	//set new centroid x y coords as average of all x and y in pointsInCluster
	newCenter = std::make_pair(x,y);
	allClusters[k][i]->centroid = newCenter;
	
	//if centroid didn't change, points will not change. clustering done for this value of k.
	if (oldCenter == newCenter)
	{
		allClusters[k][i]->pointChange = false;
	}
	else
	{
		newCenter = std::make_pair(x,y);
		allClusters[k][i]->centroid = newCenter;
	}
} //calcNewCentroid


/*
Given a value of k, an integer i representing the cluster index, and a K_Means object, finalizeCluster calculates new centroids for each cluster in this value of k,
removes all previous points from pointsInCluster, then assigns points and recalculates new centroids while the pointChange bool is true.
*/
void K_Means::finalizeCluster(int k, int i, K_Means km)
{
	//calculate new centroids for each cluster in this k
	for (int j = 0; j < k; j++)
	{
		km.calcNewCentroid(k,j);
	}
	
	//while pointChange bool for this cluster is true or there are no points in the cluster, calculate new centroids and assign points to those centroids
	while (km.getPointChange(k,i) || (allClusters[k][i]->pointsInCluster.size() == 0))
	{
		
		for (int j = 0; j < k; j++)
		{
			km.erasePointsInCluster(k,j);
		}

		km.assignPoints(k,i);
		km.calcNewCentroid(k,i);
	}
} //finalizeCluster

//assign new points to pointsInCluster variable for ith cluster for this k
void K_Means::assignPoints(int k, int i)
{
	std::vector<float> distList;
	K_Means km;
	float closest;
	

	//testing outputs
	// if (k == 2)
	// {
		// std::cout << "***************************************ASSIGN CYCLE***************************************************" << std::endl;
	// }
	
	//for each point in allPoints
	for (int j = 0; j < allPoints.size(); j++)
	{
		//create tmp variables to hold current point, centroid, distances, and index of location distance was taken from
		std::pair<float,float> tmpPt;
		std::pair<float,float> tmpCent;
		float tmpDist = 0.0;
		int assignLoc = 0;
		
		//get this point
		tmpPt = allPoints[j+1];
		
		//get distance from this point to each centroid for this value of k and store it in distList in the order it was calculated
		for (int l = 0; l < k; l++)
		{
			tmpCent = allClusters[k][l]->centroid;
			tmpDist = km.calcDistance(tmpPt, tmpCent);
			distList.push_back(tmpDist);
		}
		
		//set closest to an impossible value, compare each element of distList against closest
		//if element of distList is closer than closest, set closest = current distList element
		//set assignLoc to value of l where closest distance was found. This is the location of the cluster the point is assigned to.
		closest = 999999;
		for (int l = 0; l < distList.size(); l++)
		{
			if (distList[l] < closest)
			{
				//std::cout << "k: " << k << std::endl;
				closest = distList[l];
				assignLoc = l;
				//std::cout << "closest is: " << closest << std::endl;
			}
		}
		
		//assign the point to its cluster, set numPoints = to the size of the pointsInCluster map.
		allClusters[k][assignLoc]->pointsInCluster.insert({j+1, tmpPt});
		allClusters[k][assignLoc]->numPoints = allClusters[k][assignLoc]->pointsInCluster.size();

		//testing outputs
		// if (k == 2)
		// {
			// std::cout << "ID(i+1): " << j+1 << " added to cluster: " << allClusters[k][assignLoc]->clusterLabel << " which contains " << allClusters[k][assignLoc]->pointsInCluster.size() << " points." << std::endl;
		// }
		
	
		distList.clear();
	}
} //assignPoints

/*
Given a value of k and the index of a cluster i, erasePointsInCluster() erases and clears pointsInCluster and sets numPoints for that cluster to 0.
Called from finalizePoints 
*/
void K_Means::erasePointsInCluster(int k, int i)
{
	allClusters[k][i]->pointsInCluster.erase(allClusters[k][i]->pointsInCluster.begin(), allClusters[k][i]->pointsInCluster.end());
	allClusters[k][i]->pointsInCluster.clear();
	allClusters[k][i]->numPoints = 0;
	
}

//returns value representing whether or not points in a given cluster at a given value of k have changed clusters
bool K_Means::getPointChange(int k, int i)
{
	return allClusters[k][i]->pointChange;
}

/*
Given a value of k, calcShortest compares the distance from each point in a cluster to its centroid and finds the shortest distance.
The ID of the point corresponding to that distance is set as the ID of the closestPoint for the cluster.
*/
void K_Means::calcShortest(int k)
{
	K_Means km;
	float shortestDist = 0;
	std::pair<float,float> tmpPt;
	std::pair<float,float> tmpCent;
	float tmpDist = 0;
	int tmpID = 0;
	//for all clusters in this k
	for (int i = 0; i < k; i++)
	{
		//for all points in this cluster
		shortestDist = 999999;
		for (auto it : allClusters[k][i]->pointsInCluster)
		{	
			//set tmpPt equal to this point, set tmpCent equal to centroid at i
			tmpPt = it.second;			
			tmpCent = allClusters[k][i]->centroid;
			tmpDist = km.calcDistance(tmpPt, tmpCent);
			
			if (tmpDist < shortestDist)
			{
				shortestDist = tmpDist;
				allClusters[k][i]->closestPoint = it.first;
			}
			//need to figure out how to get ID of point at previous iterator in order to compare to current ID in case of distance tie
			// else if (tmpDist == shortestDist)
			// {
				// if (it.first > prev.first)
				// {
					// allClusters[k][i]->closestPoint = prev.first;
				// }
				// else
				// {
					// allClusters[k][i]->closestPoint = it.first;
				// }
			
			// }
			
		}
	}
} //calcShortest


//Given a value of k, getClusters returns a vector of pointers to all K_Cluster objects for that value of k.
std::vector<K_Cluster*> K_Means::getClusters(int k)
{
	return allClusters[k];
}

/*
Given two pairs containing floats, calcDistance will calculate the euclidean distance between the two points and return that distance to the caller.
*/
float K_Means::calcDistance(std::pair<float,float> x1y1, std::pair<float,float> x2y2)
{
	float x,y = 0.0;
	float euclid = 0.0;
	
	x = x1y1.first - x2y2.first;
	y = x1y1.second - x2y2.second;
	
	euclid = sqrt(pow(x,2) + pow(y,2));
	
	return euclid;
}

/*
Given a value of k and an integer i representing the specific cluster for that value of k, getPointValues will return a vector
containing float pairs of all the x y values included in that cluster. IDs are not returned. 
*/
std::vector<std::pair<float,float>> K_Means::getPointValues(int k, int i)
{
	//K_Means km;
	std::vector<std::pair<float,float>> vals;
	std::vector<std::pair<float,float>> tmpVec; //= allClusters[k][i]->P;

	for(auto it : allClusters[k][i]->pointsInCluster)
	{
		std::cout << it.second.first << std::endl;
		std::cout << it.second.second << std::endl;
		vals.push_back(it.second);
	}
	
	return vals;
}

/*
Given a value of k, a cluster identifier label, and a pair of floats representing the centroid for a cluster, newCluster sets those values in a K_Cluster struct
*/
void K_Cluster::newCluster(int k, int label, std::pair<float,float> cent)
{
	kVal = k;
	clusterLabel = label;
	centroid = cent;
} //initCluster

/*
Given a map of int keys and pairs of float values, initPoints copies that map into allPoints
*/
void K_Means::initPoints(std::map<int, std::pair<float,float>> points)
{
	allPoints.insert(points.begin(), points.end());
}

/*
Given a value of k and a pointer to a K_Cluster struct, storeCluster stores that cluster in allClusters map in the vector located at that value of k.
*/
void K_Means::storeCluster(int k, K_Cluster* clust)
{
	allClusters[k].push_back(clust);
}

void K_Means::setMaxK(int k)
{
	maxK = k;
}

void K_Means::setMinK(int k)
{
	minK = k;
}