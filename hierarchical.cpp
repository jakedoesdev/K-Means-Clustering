#include "hierarchical.h"
#include <iostream>
#include <math.h>
#include<iterator>
using namespace std;

/*
 * Test(would be called FillCluster if I was good with varaiable names while doing tests) is a copy of the point struct from config.h
 * since clusters must start out as points but with a different name for future use of functions
 */
void hierarchical::test(int id, float x, float y)
{
	HCluster hcluster;
	hcluster.id=id;
	hcluster.x=x;
	hcluster.y=y;
	this->get_HCluster_list().push_back(hcluster);
}
/*
 * FillLevel will store a vector of HClusters, which is each cluster inside the level, and an int to store which level exactly
 * is being stored
 */
void hierarchical::FillLevel(vector<HCluster>& hcluster, int x)
{
	HLevel hlevel;
	hlevel.H=hcluster;
	hlevel.level=x;
	this->get_HLevel_list().push_back(hlevel);
}
vector<HCluster>& hierarchical::get_HCluster_list()
{
	return this->HCluster_list;
};
vector<HLevel>& hierarchical::get_HLevel_list()
{
	return this->HLevel_list;
};
/* This function takes two clusters, and a cluster vector to merge two clusters and throw it back into the cluster vector at the
 * the spot of the cluster with the shortest id
 * So for example if clusters 1 (x,y)->(2,2) and 2 (x,y)->(4,4) were placed in here, the x and y values of each would be averaged
 * and set to the new cluster, then the new cluster will be given an ID of 1 since 1<2. Clusters 1 and 2 will then be deleted and The new cluster
 * will take the spot of 1. Afterwards since the id order would now be 1,3,4,5..., we need to shorten all IDs after 2 by 1 in order to bring
 * these IDs back into a proper value that can be used
 */
void hierarchical::merge(HCluster &clus1, HCluster &clus2,vector<HCluster>& hcluster)
{

	HCluster newclus;
	float bigid;
	newclus.x=(clus1.x+clus2.x)/2;
	newclus.y=(clus1.y+clus2.y)/2;
	newclus.pointlist.insert(newclus.pointlist.end(), clus1.pointlist.begin(), clus1.pointlist.end());
	newclus.pointlist.insert(newclus.pointlist.end(), clus2.pointlist.begin(), clus2.pointlist.end());

	if(clus1.id>clus2.id)
	{
		newclus.id=clus2.id;
		bigid=clus1.id;

		hcluster.erase(hcluster.begin()+clus2.id-1);
		hcluster.erase(hcluster.begin()+clus1.id-1);
		hcluster.insert(hcluster.begin()+newclus.id-1,newclus);


	}

	if(clus1.id<clus2.id)
	{
		newclus.id=clus1.id;
		bigid=clus2.id;
		hcluster.erase(hcluster.begin()+clus2.id-1);
		hcluster.erase(hcluster.begin()+clus1.id-1);
		hcluster.insert(hcluster.begin()+newclus.id-1,newclus);


	}

	for(int x=bigid-1;x<hcluster.size();x++)
	{
		hcluster.at(x).id-=1;
	}


}
/*This function finds the two closest clusters by taking the first two clusters in a vector
 * and assigning them as a base for future clusters to be compared to.
 * So clusters of ID 1 and ID 2 will be set as having the shortest distance between them
 * but if clusters ID 3 and ID 4 have a shorter distance between them then ID 1 will be replaced with ID 3 and ID 2 will be replaced with ID 4
 * If no other Clusters have a shorter distance between them then they will be thrown into the merge function
 */
void hierarchical::closest(vector<HCluster>& hcluster)
{
	int closeclus1=hcluster[0].id;
	int closeclus2=hcluster[1].id;
	float closex=pow(hcluster[0].x-hcluster[1].x,2);
	float closey=pow(hcluster[0].y-hcluster[1].y,2);
	float closedist=sqrt(closex+closey);

	int expireclus1;
	int expireclus2;
	float expirex;
	float expirey;
	float expiredist;
	float distance;

	for(int x=0; x<hcluster.size();x++)
	{
		for(int y=0;y<hcluster.size();y++)
		{

			expireclus1=hcluster[x].id;
			expireclus2=hcluster[y].id;
			expirex=pow(hcluster[x].x-hcluster[y].x,2);
			expirey=pow(hcluster[x].y-hcluster[y].y,2);
			expiredist=sqrt(expirex+expirey);


			if(closedist>expiredist && expiredist !=0)
			{
				closeclus1=expireclus1;
				closeclus2=expireclus2;
				closedist=expiredist;


			}
			else if(closedist==expiredist && expiredist !=0)
				{
					if(closeclus1>expireclus1)
					{
						closeclus1=expireclus1;
						closeclus2=expireclus2;
						closedist=expiredist;

					}
					else
					{

					}
				}
			else
			{

			}

		}
		this->get_HLevel_list()[this->get_HLevel_list().size()-x].shortest_d=closedist;

	}

	this->merge(hcluster[closeclus1-1],hcluster[closeclus2-1],hcluster);
}


