#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

class Point
{
private:
	int id_point, id_cluster;
	vector<double> values;
	int total_values;
	string name;
	double time;

public:
	Point(int id_point, vector<double>& values, double time = 0.0,string name = "")
	{
		this->id_point = id_point;
		total_values = values.size();

		for(int i = 0; i < total_values; i++)
			this->values.push_back(values[i]);

		this->name = name;
		this->time = time;
		id_cluster = -1;
	}

	int getID()
	{
		return id_point;
	}

	void setCluster(int id_cluster)
	{
		this->id_cluster = id_cluster;
	}

	int getCluster()
	{
		return id_cluster;
	}

	double getValue(int index)
	{
		return values[index];
	}

	int getTotalValues()
	{
		return total_values;
	}

	void addValue(double value)
	{
		values.push_back(value);
	}

	string getName()
	{
		return name;
	}
	double getTime(){
	return time;}
	
};

class Cluster
{
private:
	int id_cluster;
	vector<double> central_values;
	vector<Point> points;

public:
	Cluster(int id_cluster, Point point)
	{
		this->id_cluster = id_cluster;

		int total_values = point.getTotalValues();

		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i));

		points.push_back(point);
	}

	void addPoint(Point point)
	{
		points.push_back(point);
	}

	bool removePoint(int id_point)
	{
		int total_points = points.size();

		for(int i = 0; i < total_points; i++)
		{
			if(points[i].getID() == id_point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	double getCentralValue(int index)
	{
		return central_values[index];
	}

	void setCentralValue(int index, double value)
	{
		central_values[index] = value;
	}

	Point getPoint(int index)
	{
		return points[index];
	}

	int getTotalPoints()
	{
		return points.size();
	}

	int getID()
	{
		return id_cluster;
	}
};

class KMeans
{
private:
	int K; // number of clusters
	int total_values, total_points, max_iterations;
	vector<Cluster> clusters;

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point point)
	{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_values; i++)
		{
			sum += pow(clusters[0].getCentralValue(i) -
					   point.getValue(i), 2.0);
			cout<<clusters[0].getCentralValue(i)<<"\t\t"<<point.getValue(i)<<"\t\t"<<sum;
		}
		

		min_dist = sqrt(sum);

		for(int i = 1; i < K; i++)
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < total_values; j++)
			{
				sum += pow(clusters[i].getCentralValue(j) -
						   point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist;
				id_cluster_center = i;
			}
		}
		cout<<"     "<<id_cluster_center<<endl;
		return id_cluster_center;
	}

public:
	KMeans(int K, int total_points, int total_values, int max_iterations)
	{
		this->K = K;
		this->total_points = total_points;
		this->total_values = total_values;
		this->max_iterations = max_iterations;
	}

	void run(vector<Point> & points)
	{
		//number of clusters should be always less than number of points
		if(K > total_points)
			return;

		vector<int> indexes;
		//for(int a=0;a<indexes.size();a++){cout<<indexes.at(a)<<"   BBBBBBB";}
		// choose K distinct values for the centers of the clusters i.e select cluster heads;
		// This part selects a random point as cluster head, maps with the point and then pushes to the vector
		for(int i = 0; i < K; i++)
		{
			//while(true)
			//{
				int index_point = rand() % total_points;
				cout<<index_point<<"BLAHHHSSS"<<"   ";
				//If No such element exists, if 8 is the cluster head, then if 6,7 are randomly generated, they cannot be the 					cluster head
			//	if(find(indexes.begin(), indexes.end(),index_point) == indexes.end())
			//	{
					//indexes.push_back(index_point); 
					points[index_point].setCluster(i);  //This point belongs to this cluster-index
					Cluster cluster(i, points[index_point]); //Map the cluster index with the points
					clusters.push_back(cluster);//Push it to the vector
			//		break;
			//	}
			//}
		}
		cout<<endl;
		int iter = 1;

		while(true)
		{
			bool done = true;

			// associates each point to the nearest center
			for(int i = 0; i < total_points; i++)
			{
				int id_old_cluster = points[i].getCluster();
				int id_nearest_center = getIDNearestCenter(points[i]);
				cout<<id_old_cluster<<"   "<<id_nearest_center<<"   "<<done<<endl;
				if(id_old_cluster != id_nearest_center)
				{
					if(id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID());

					points[i].setCluster(id_nearest_center);
					clusters[id_nearest_center].addPoint(points[i]);
					done = false;
				}
			}

			// recalculating the center of each cluster
			for(int i = 0; i < K; i++)
			{
				for(int j = 0; j < total_values; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if(total_points_cluster > 0)
					{
						for(int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster);
					}
				}
			}

			if(done == true || iter >= max_iterations)
			{
				//cout << "Break in iteration " << iter << "\n\n";
				break;
			}

			iter++;
		}

		// shows elements of clusters
		for(int i = 0; i < K; i++)
		{
			
			int total_points_cluster =  clusters[i].getTotalPoints();
			
			cout<<"A"<<endl;
			for(int j = 0; j < total_points_cluster; j++)
			{
				//cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
				//cout <<clusters[i].getID() + 1<<" ";
				for(int p = 0; p < total_values; p++)
					cout << clusters[i].getPoint(j).getValue(p) << " ";

				string point_name = clusters[i].getPoint(j).getName();
				double time = clusters[i].getPoint(j).getTime();
				//double value = clusters[i].getPoint(j).getValue();

				if(point_name != "")
					cout << time << " " << point_name;

				cout << endl;
			}

			cout << "$$";

			//for(int j = 0; j < total_values; j++)
			//	cout << clusters[i].getCentralValue(j) << " ";

			cout << "\n\n";
		}
	}
};

int main(int argc, char *argv[])
{
	srand (time(NULL));

	int total_points, total_values, K, max_iterations, has_name;

	cin >> total_points >> total_values >> K >> max_iterations >> has_name;

	vector<Point> points;
	string point_name;
	double time;

	for(int i = 0; i < total_points; i++)
	{
		vector<double> values;

		for(int j = 0; j < total_values; j++)
		{
			double value;
			cin >> value;
			values.push_back(value);
		}
		cin>>time;
		if(has_name)
		{
			getline(cin,point_name);
			Point p(i, values, time,point_name);
			points.push_back(p);
		}
		else
		{
			Point p(i, values);
			points.push_back(p);
		}
	}

	KMeans kmeans(K, total_points, total_values, max_iterations);
	kmeans.run(points);

	return 0;
}
