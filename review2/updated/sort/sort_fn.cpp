#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
struct details {
double x_c;
double y_c;
double time;
string ad_des;
};
int main() 
{
ifstream input("/home/keyrooh/kmeans/2a.txt");
ifstream input1("/home/keyrooh/kmeans/1a.txt");
ifstream input3("/home/keyrooh/kmeans/3a.txt");
ofstream file("sorted2a.txt");
ofstream file1("sorted1a.txt");
ofstream file3("sorted3a.txt");
std::vector<details> det_vec;
details d;
/*******CLUSTER 2*******/
while (input >>d.x_c >>d.y_c>>d.time&&getline(input,d.ad_des,'!'))
{
det_vec.push_back(d);
}
sort(det_vec.begin(),det_vec.end(),[](const details& s1, const details& s2) { return s1.time < s2.time; });
printf("Sorting!!!!!!!!!!!!!!!!\n\n");
for (auto vectorit = det_vec.begin(); vectorit != det_vec.end(); ++vectorit)
{
cout<<vectorit->x_c<<" "<<vectorit->y_c<<" "<<vectorit->time<<vectorit->ad_des<<endl;
file<<vectorit->x_c<<" "<<vectorit->y_c<<" "<<vectorit->time<<vectorit->ad_des<<endl;
}
det_vec.clear();  
/*******CLUSTER 1*******/
while (input1 >>d.x_c >>d.y_c>>d.time&&getline(input1,d.ad_des,'!'))
{
det_vec.push_back(d);
}
sort(det_vec.begin(),det_vec.end(),[](const details& s1, const details& s2) { return s1.time < s2.time; });
printf("Sorting!!!!!!!!!!!!!!!!\n\n");
for (auto vectorit = det_vec.begin(); vectorit != det_vec.end(); ++vectorit)
{
cout<<vectorit->x_c<<" "<<vectorit->y_c<<" "<<vectorit->time<<vectorit->ad_des<<endl;
file1<<vectorit->x_c<<" "<<vectorit->y_c<<" "<<vectorit->time<<vectorit->ad_des<<endl;
}
det_vec.clear();
/*******CLUSTER 3*******/
while (input3 >>d.x_c >>d.y_c>>d.time&&getline(input3,d.ad_des,'!'))
{
det_vec.push_back(d);
}
sort(det_vec.begin(),det_vec.end(),[](const details& s1, const details& s2) { return s1.time < s2.time; });
printf("Sorting!!!!!!!!!!!!!!!!\n\n");
for (auto vectorit = det_vec.begin(); vectorit != det_vec.end(); ++vectorit)
{
cout<<vectorit->x_c<<" "<<vectorit->y_c<<" "<<vectorit->time<<vectorit->ad_des<<endl;
file3<<vectorit->x_c<<" "<<vectorit->y_c<<" "<<vectorit->time<<vectorit->ad_des<<endl;
}
det_vec.clear();        
return 0;
}
