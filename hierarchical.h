#ifndef HIERARCHICAL_H_
#define HIERARCHICAL_H_

#include <iostream>
#include <vector>
#include "config.h"

using namespace std;

struct HCluster
{
	float x;
	float y;
	int id;
	vector<Point> pointlist;


};

struct HLevel
{
	vector<HCluster> H;
	float shortest_d;
	int level;
};

class hierarchical
{
private:
	vector<HCluster> HCluster_list;
	vector<HLevel> HLevel_list;
public:
	void test(int, float, float);
	vector<HCluster>& get_HCluster_list();
	vector<HLevel>& get_HLevel_list();
	void merge(HCluster&, HCluster&, vector<HCluster>& hcluster);
	void closest(vector<HCluster>&);
	void FillLevel(vector<HCluster>& hcluster, int x);
};

#endif
