#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

struct dataItem{
	int ID;
	double lat, lon;
};

int main(int argc, char* argv[]){
	srand(6453);
	int count=5000;
	for (int i=0; i<argc; i++){
		cerr<<argv[i]<<endl;
		if (strcmp(argv[i],"-n")==0 && i!=argc-1) {
			stringstream parse(argv[i+1]);
			parse>>count;
		}
	}
	//cerr<<count<<endl;
	vector<dataItem> inp; string line;
	while(getline(cin,line))
	{
		dataItem cur; stringstream lineStream(line);
		string cell;
	        for (int i=0; i<3; i++)
        	{
			getline(lineStream,cell,',');
			stringstream conv(cell);
			if (i==0) conv>>cur.ID;
			else if (i==1) conv>>cur.lat;
			else if (i==2) conv>>cur.lon;
	        }
        	inp.push_back(cur);
	}
	cout<<"PointA_Lat,PointA_Lon,PointB_Lat,PointB_Lon"<<endl;
	for (int i=0; i<count; i++){
		int A = (rand()*65536+rand())%inp.size();
		int B = A+(rand()%(inp.size()/5000))-(rand()%(inp.size()/5000));
		if (B<0) B=0;
		if (B>=inp.size()) B = inp.size()-1;
		if (A==B) B = A+rand()%10+1;
		cout<<inp[A].lat<<','<<inp[A].lon<<','<<inp[B].lat<<','<<inp[B].lon<<endl;
	}
}
