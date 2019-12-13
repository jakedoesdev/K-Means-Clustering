#include <iostream>
#include <map>
#include "config.h"
#include "kmeans.h"
#include "hierarchical.h"
#include "dunindex.h"

int main() {

	//CONFIG DECLARATIONS
	Config new_config;

	//KMEANS DECLARATIONS
	K_Means km;
	K_Cluster *kclst;
	std::map<int, std::pair<float,float>> tmpPts;
	std::pair<float,float> tmpCent;
	int tmpID, tmpK, minK, maxK;
	std::vector<K_Cluster*> tmpVec;
	
	//HIERARCHICAL DECLARATIONS
	hierarchical hier;
	
	//DUNINDEX DECLARATIONS
	vector<CalcClass> calc;
	std::vector<map<int, pair<float, float>>> myvect;
	std::vector<float> myvect2;
	CalcClass calcH;
	ZachData Hthis;

	if (new_config.parse_config()) {
		new_config.parse_points();


/**********************************************************************************************************************************************************************************/


		//BEGIN KMEANS CODE
		//get all points, store in tmpPts map with id as key and pair of x/y floats as value
		for(int i = 0; i < new_config.get_point_list().size(); i++) 
		{
			tmpPts[new_config.get_point_list()[i].id] = std::make_pair(new_config.get_point_list()[i].x, new_config.get_point_list()[i].y);
		}
		
		//copy tmpPts to K_Means map variable allPoints 
		km.initPoints(tmpPts);
		
		//get min/max number of clusters to use in iterations
		minK = new_config.get_min_clusters();
		maxK = new_config.get_max_clusters();
		
		//set min/max values of k for K_Means object 
		km.setMinK(minK);
		km.setMaxK(maxK);
		
		//For all centroids in the list, for each value of k,
		//get the centroid, find the point with the corresponding id, and get its xy values
		//then create K_Cluster object for each centroid,, store in K_Means::allClusters
		for(int i = 0; i < new_config.get_centroid_list().size(); i++) 
		{
			for(int j = 0; j < new_config.get_centroid_list()[i].place.size(); j++) 
			{
				//get the point ID and the value of k for this clustering
				tmpID = new_config.get_centroid_list()[i].place[j];
				tmpK = new_config.get_centroid_list()[i].place.size();
				
				//find the x/y value of the point with that ID
				//tmpPts.find(tmpID);
				tmpCent.first = tmpPts.find(tmpID)->second.first;
				tmpCent.second = tmpPts.find(tmpID)->second.second;
				
				//store it in K_Cluster object with initial kvalue, clusterlabel, and centroid x/y pair
				kclst = new K_Cluster;
				kclst->newCluster(tmpK, (j+1), tmpCent);
				km.storeCluster(tmpK, kclst);
			}
		}
		
		//for each value of k, calculate and set initial clusters with centroids from config file.
		for (int i = minK; i <= maxK; i++)
		{	
			km.initCluster(i);
		}
		
		//for each value of k
		for (int i = minK; i <= maxK; i++)
		{	
			//for each cluster in this k, repeatedly recalculate new centroids and reassign points
			for (int j = 0; j < i; j++)
			{	
				km.finalizeCluster(i,j, km);
			}
		}
		
		//for each value of k, calculate and set the ID of the point closest to each centroid
		for (int i = minK; i <= maxK; i++)
		{
			km.calcShortest(i);
		}
	
		//k means outputs
		std::cout << "For k-means clustering:\n";
		for (int i = minK; i <= maxK; i++)
		{
			tmpVec = km.getClusters(i);
			
			std::cout << "For a k value of " << i << " here is the information regarding its clusters:\n";
			for (int j = 0; j < tmpVec.size(); j++)
			{
				std::cout << "Cluster " << tmpVec[j]->clusterLabel << " contains " << tmpVec[j]->pointsInCluster.size() << " points and the point " 
					      << tmpVec[j]->closestPoint << " is closest to its centroid\n";	
			}
		}
		//END KMEANS CODE


/**********************************************************************************************************************************************************************************/		

		//START HIERARCHICAL CODE
		for(int x=0;x<new_config.get_point_list().size();x++)
		{
			hier.test(new_config.get_point_list()[x].id,new_config.get_point_list()[x].x,new_config.get_point_list()[x].y);//turns points into clusters
			hier.get_HCluster_list()[x].pointlist.push_back(new_config.get_point_list()[x]);
		}

		for(int x=0;x<new_config.get_point_list().size();x++)
		{
			hier.FillLevel(hier.get_HCluster_list(),x);
		}
		//END HIERARCHICAL CODE


/**********************************************************************************************************************************************************************************/


		//START DUNINDEX CODE
		int maxx = hier.get_HCluster_list().size();
		std::cout << "Hierarchy level " << hier.get_HLevel_list()[0].level << " with " << hier.get_HLevel_list()[0].H.size() << " clusters inside" << std::endl;
		for (int x = 1;x<maxx;x++)
		{	//int r = x+140;

			if (x % 10 == 0)
			{

				std::cout << "Hierarchy level " << hier.get_HLevel_list()[x].level << " with " << hier.get_HLevel_list()[x].H.size() << " clusters inside ";
				//std::cout << r << endl;

				calcH.calcforH(hier.get_HCluster_list(),x,hier.get_HLevel_list()[x].H.size());

				/*
				for(int d = 0; d<calcH.get_dunVect_list().size();d++){
	
				std::cout <<  " and a Dunn Index of "  << calcH.get_dunVect_list()[x].get_Hdunindex()<< endl;
	
					}
				*/	
			}
			else
			{
				if (hier.get_HLevel_list()[x].H.size() == 1)
				{
					std::cout << "Hierarchy level " << hier.get_HLevel_list()[x].level << " with " << hier.get_HLevel_list()[x].H.size() << " clusters inside " << endl;
				}
			}
		}	


	
				//std:cout<< hier.get_HLevel_list()[x].H.size() << " level ";
				//std::cout << r << endl;
				std::cout << "For centroid-linkage clustering, " << hier.get_HLevel_list()[160].H.size();
				//calcH.calcforH(hier.get_HCluster_list(),x);
				calcH.PrintDunnPart(calcH.get_dunVect_list());
				ZachData zdata;
	
				cout << "For k-means, a k value of  had the highest Dunn index of ";
				cout << zdata.get_Hlevel() << endl;
				cout <<"Complete!"<<endl;

	//END DUNINDEX CODE
	
	
/**********************************************************************************************************************************************************************************/
	
	
	}
	else {
		std::cout << "File not found, exiting" << std::endl;
	}
	return 0;
}

