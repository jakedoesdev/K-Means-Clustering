#ifndef DUNINDEX_H_
#define DUNINDEX_H_

#include <vector>
#include <iostream>
#include <limits.h>
#include <utility>
#include <tuple>
#include <cmath>
#include "hierarchical.h"
#include "kmeans.h"

using std::map;
using std::pair;
using std::get;
using std::next;

class ZachData{
public:
float Hdunindex;

float Cdunindex;

float Hlevel;


float get_Hdunindex();
float get_Cdunindex();

float get_Hlevel();

void set_Hdunindex(float new_Hdunindex);
void set_Cdunindex(float new_Cdunindex);

void set_Hlevel(float new_level);

};




class CalcClass {
private:
		

	vector<ZachData> dunVect;
	
	
	
	float dunindexForh;
	vector<hierarchical> HcList;
	
	std::map<int, std::pair<float, float>> allPts;
public:	
		


	vector<ZachData>& get_dunVect_list();
	
	
	
	void PrintDunnPartForC(vector<ZachData>& cIndexs);

	
	void PrintDunnPart(vector<ZachData>& hIndexs);
	void calcforH(vector<HCluster>& hcluster, int p,int sizeH);
	void createallPoints(std::map<int, std::pair<float, float>> points);
	void distance(vector<HCluster>&);
	void calcForK(int i);
		
};

#endif
