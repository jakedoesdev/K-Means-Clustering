#include "dunindex.h"
#include "hierarchical.h"
/*
Use all of these to set and get all of my dunindexs

*/
float ZachData::get_Hdunindex()
{
	return Hdunindex;
}
float ZachData::get_Cdunindex()
{
	return Cdunindex;
}

float ZachData::get_Hlevel()
{
	return Hlevel;
}

void ZachData::set_Hlevel(float new_level){
	Hlevel = new_level;
}



void ZachData::set_Hdunindex(float new_Hdunindex){
	Hdunindex = new_Hdunindex;
}
void ZachData::set_Cdunindex(float new_Cdunindex){
	Cdunindex = new_Cdunindex;
}
vector<ZachData>& CalcClass::get_dunVect_list()
{
	return this->dunVect;
}





//void CalcClass::calcforH(vector<HCluster>& hcluster, int level)
/*  This Function finds the closest points in clusters by assigning the the base case for the clusters 
and comparing them to a rotating thru the cluster in a for loop comparing all the points but only if the 
level is decremented by 10 and saves it in a vector of type class so that i can call them in the main


*/
void CalcClass::calcforH(vector<HCluster>& hcluster,int p,int sizeH)
{
	hierarchical hier;
	int closeclus1 = hcluster[0].id;
	int closeclus2 = hcluster[1].id;
	
	int farclus1 = hcluster[0].id;
	int farclus2 = hcluster[1].id;
	

	float closex = pow(hcluster[0].x - hcluster[1].x, 2);
	float closey = pow(hcluster[0].y - hcluster[1].y, 2);
	
	float closedist = sqrt(closex + closey);

	float farx = pow(hcluster[0].x - hcluster[1].x, 2);
	float fary = pow(hcluster[0].y - hcluster[1].y, 2);
	

	float fardist = sqrt(farx + fary);



	
	


	HLevel* hlevel;
	//hlevel.level = x;
	
	//cout << hcluster << endl;
	//cout << x << endl;
	
	int expireclus1;
	int expireclus2;
	int expireclus3;
	int expireclus4;
	float expirex;
	float expirey;
	float expiredist;

	vector<float> dunindex;
	float oneindex = 0.0;

	vector<float> allindex;
	vector<float> alldist;
	ZachData zData;
	int counter =0;
	//

	

//cout << p << endl;
//for loop to ge the points in the first cluster
	for (int x = 140; x<hcluster.size()-1;x++)
	{	counter++;
		//for loop to get the points in the second cluster
		for (int y = 140;y<hcluster.size()-1;y++)
		{	//decrement by 10
			if(x%10 == 0 && y%10==0){

			float tempDist = 0.0;


			expireclus1 = hcluster[x].id;
			expireclus2 = hcluster[y].id;
			expireclus3 = hcluster[x].id;
			expireclus4 = hcluster[y].id;
			expirex = pow(hcluster[x].x - hcluster[y].x, 2);
			expirey = pow(hcluster[x].y - hcluster[y].y, 2);
			expiredist = sqrt(expirex + expirey);

			
			
			
			
			if (closedist>=expiredist && expiredist != 0)
			{	
				closeclus1 = expireclus1;
				closeclus2 = expireclus2;
				closedist = expiredist;
				

			}
			else if (fardist<=expiredist && expiredist != 0)
			{	
				int farclus1 =expireclus3;	
				int farclus2 = expireclus4;
				fardist = expiredist;
				//setting the dist for one index
				oneindex=closedist/fardist;
				//push it to the vector
				zData.set_Hdunindex(oneindex);
				dunVect.push_back(zData);
				
			}
			
		
			
			}
			
			else
			{
		
			
				}


		}
		
		
	}
	//since this is called in a foor loop in main this if will make it to were it only print numbers when the level is greater than 150 and the size is not equal to 1	
	if(p>150 && sizeH != 1){

	
cout << "and a Dunn Index of " << dunVect[p].get_Hdunindex() << endl;



}
	else
{
cout << "" << endl;
}
/*
	//check the numbers in the vector
	if(dunVect.size()>0){
	
	for(int c =0; c<dunVect.size();c++){
	
	
	cout <<  "and a Dunn Index of " << dunVect[c].get_Hdunindex() << endl;
}
}
	
*/

	
}







/*used to create all the points that i will be using in k means clustering 
i had to use this function because part 2 wasnt completed yet and there was no way for me to access the numbers

*/
void CalcClass::createallPoints(std::map<int, std::pair<float, float>> points)
{
	allPts.insert(points.begin(), points.end());
}
/*
this filiters thru the map of pairs and iterates thru two different for loops to go thru all the points
and compare them to find out what is the closest distance and the furthest ditance then diveds them.
it use the standard distance forumla on the numbers

using the standard get to get the k value saved in int and the pair saved in the points for that k.
it then saves all the dun indexs using the set function and then uses push back to put those set dun indexs into the vector. after that it calls the print function and sends the vector
containing all the dun indexs to the print function so that it can calculate the biggest dun index
*/
void CalcClass::calcForK(int i){
	float minDist = -1;
	float maxDist = -1;
	float dunindex;
	
	float numOfmini=0;
	float numOfMax=0;

	

	float dunindexT;
	ZachData zData;
	CalcClass calct;
	float currentDist = 0;
	//pair minPoint<float, float>;
	//pair maxPoint<float, float>;

	for(map<int, pair<float, float>>::iterator i = allPts.begin(); next(i) != allPts.end(); i++)
	{
		//cout << "(" << get<0>(i -> second) << ", " << get<1>(i -> second) << ")\n";

		for(map<int, pair<float, float>>::iterator j = next(i) ; j != allPts.end(); j++)
		{
			//cout << "Comparing: (" << get<0>(i -> second) << ", " << get<1>(i -> second) << ") & (" << get<0>(j -> second) << ", " << get<1>(j -> second) << ")\n";
			
			currentDist = sqrt(pow(get<0>(i -> second) - get<0>(j -> second), 2) + pow(get<1>(i -> second) - get<1>(j -> second), 2));

			if(minDist == -1 || minDist > currentDist)
			{	numOfmini++;
				minDist = currentDist;
			}
			else if(maxDist == -1 || maxDist < currentDist)
			{	numOfMax++;
				maxDist = currentDist;
				
				dunindex = (minDist*minDist) / (maxDist*maxDist);
				zData.set_Cdunindex(dunindex);
				dunVect.push_back(zData);

			}
			

			}
		}

		//this with print the vector list for that k value ----- this is called in main so it will print each time it is called
		cout << get_dunVect_list()[i].get_Cdunindex() << endl;
	
		PrintDunnPartForC(calct.get_dunVect_list());
		/*cout << "TESTING" << endl;
	float mynumber3 = get_dunVect_list()[2].get_Cdunindex();
	float mynumber4 = get_dunVect_list()[3].get_Cdunindex();
	float mynumber5 = get_dunVect_list()[4].get_Cdunindex();
	float mynumber6 = get_dunVect_list()[5].get_Cdunindex();	
	cout << mynumber3 << endl;
	cout << mynumber4 << endl;
	cout << mynumber5 << endl;
	cout << mynumber6 << endl;
	cout << "TESTING" << endl;
*/
		
}
/*
assumes the first one in the vector is the smallest one.
Take the vectors of all the dun indexs for the kmeans and uses a for loop to find the largest
dunindex in the vector then after calculating the highest one it will print that one.


*/

void CalcClass::PrintDunnPartForC(vector<ZachData>& cIndexs){
	/*cout << "TESTING" << endl;
	float mynumber = get_dunVect_list()[2].get_Cdunindex();	
	cout << mynumber << endl;
	cout << "TESTING" << endl;
	*/
	ZachData zdata;
	float smallestHD = get_dunVect_list()[2].get_Cdunindex();
	float temp;
	float largestHD;
	float finaldistance;
	//cout << smallestHD << endl;
for (int x = 2; x<get_dunVect_list().size();x++){
	largestHD=get_dunVect_list()[x].get_Cdunindex();	
	//cout << largestHD << endl;
	if (smallestHD<largestHD)
			{	
				smallestHD=largestHD;
				temp = largestHD;
				
			}
	else if(smallestHD>largestHD)
	{
		largestHD=smallestHD;
		temp=largestHD;

	}



}
//
float mynum;
mynum = temp;
//cout << mynum << endl;
zdata.set_Hlevel(mynum);
/*
cout << "For k-means, a k value of 4 had the highest Dunn index of ";
cout << temp 
<< endl;
*/
//cout << zdata.get_Hlevel() << endl;

//dunVect.push_back(zdata);


}

/*
Take the vectors of all the dun indexs for the hierarchy assumes the first one is the smallest one the filiters thru
 and find the largest one using a for loop each time comparing the number to the last number and setting it to a temp variable 
then print out the temp variable


*/


void CalcClass::PrintDunnPart(vector<ZachData>& hIndexs){
	//cout << "TESTING" << endl;
	//float mynumber = get_dunVect_listC()[0].get_Cdunindex();	
	//cout << mynumber << endl;
	//cout << "TESTING" << endl;
	ZachData calct;
	float smallestHD = get_dunVect_list()[0].get_Hdunindex();
	float temp;
	float largestHD;
	float finaldistance;
for (int x = 0; x<hIndexs.size();x++){
	largestHD=get_dunVect_list()[x].get_Hdunindex();
	
	if (smallestHD<largestHD)
			{	
				smallestHD=largestHD;
				temp = largestHD;
				
			}
	else if(smallestHD>largestHD)
	{
		largestHD=smallestHD;
		temp=largestHD;

	}



}

cout << " clusters had the highest Dunn index of ";
cout << temp 
<< endl;

//cout << get_dunVect_list()[0].get_Hlevel() << endl;


//cout << calct.get_Hlevel() << endl;
//calct.PrintDunnPartForC(calct.get_dunVect_list());

}




