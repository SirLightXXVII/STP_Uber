#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <vector>
#include <algorithm>

struct dataItem{
	int ID; double lat, lon;
};

double centerLat, centerLon;

bool dataItemCmp(dataItem a, dataItem b){
	double dist1 = (a.lat-centerLat)*(a.lat-centerLat) + (a.lon-centerLon)*(a.lat-centerLon);
	double dist2 = (b.lat-centerLat)*(b.lat-centerLat) + (b.lon-centerLon)*(b.lat-centerLon);
	return dist1<dist2;
}

using namespace std;

int main(int argc, char *argv[])
{
	ofstream output; bool t=false;
	cout<<argc<<endl;
	for (int i=0; i<argc; i++){
		cout<<argv[i]<<endl;
		if (strcmp(argv[i],"-f")==0 && i!=argc-1){
			output.open(argv[i+1]); t=true; break;			
		}
	}
	if (!t) output.open("output.txt");
    ifstream data("London_postcodes.csv");

	string line; stringstream lineStream;
	getline(data,line); lineStream.str(line);
	int ColumnCount=0; string cell; int latRow, lonRow, usedRow;
	while(getline(lineStream,cell,','))
    {
           if (cell=="Latitude") latRow=ColumnCount;
           if (cell=="Longitude") lonRow=ColumnCount;
           if (cell=="In Use?") usedRow=ColumnCount;
           ColumnCount++; 
    }
    int RowCount=0; 
    vector<dataItem> usedAddress;
    while(getline(data,line))
    {
		RowCount++; dataItem cur; cur.ID = RowCount-1; bool Used = false;
		stringstream lineStream2(line);
        for (int i=0; i<ColumnCount; i++)
        {
			getline(lineStream2,cell,',');
			if (i==usedRow && cell=="Yes"){
				 Used = true;
			}
			stringstream conv(cell);
			if (i==latRow) conv>>cur.lat;
			if (i==lonRow) conv>>cur.lon;
        }
        if (Used) usedAddress.push_back(cur);
    }
    if (usedAddress.size()==0){
		cout<<"No valid address!"<<endl;
	    system("PAUSE");
		return 1;
	}
	cout<<"Input complete. Accepted "<<usedAddress.size()<<" rows"<<endl;
    double maxLon=usedAddress[0].lon, minLon=usedAddress[0].lon, maxLat = usedAddress[0].lat, minLat = usedAddress[0].lat; 
    for (int i=1; i<usedAddress.size(); i++){
		maxLon = max(maxLon, usedAddress[i].lon);
		minLon = min(minLon, usedAddress[i].lon);
		maxLat = max(maxLat, usedAddress[i].lat);
		minLat = min(minLat, usedAddress[i].lat);
	}	
	cout<<maxLat<<" "<<maxLon<<" "<<minLat<<' '<<minLon<<endl;
	centerLat = (maxLat + minLat)/2;
	centerLon = (maxLon + minLon)/2;
	sort(usedAddress.begin(), usedAddress.end(), dataItemCmp);
	output<<"ID,Latitude,Longitude"<<endl;
	for (int i=0; i<usedAddress.size(); i++){
		output<<usedAddress[i].ID<<','<<usedAddress[i].lat<<','<<usedAddress[i].lon<<endl;
	}	
    system("PAUSE");
    return EXIT_SUCCESS;
}
