#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

struct dataItem{
        int ID;
        double lat, lon;
};

string generate_name(){
	vector<string> names = {"Oliver", "Jack", "Harry", "Jacob", "Charlie", "Thomas", "George", "Oscar", "James", "William", "Noah", "Alfie", "Joshua", "Muhammad", "Henry", "Leo", "Archie", "Ethan", "Joseph", "Freddie", "Samuel", "Alexander", "Logan", "Daniel", "Isaac", "Max", "Mohammed", "Benjamin", "Mason", "Lucas", "Edward", "Harrison", "Jake", "Dylan", "Riley", "Finley", "Theo", "Sebastian", "Adam", "Zachary", "Arthur", "Toby", "Jayden", "Luke"};
	int rnd = rand();
	return names[rnd%names.size()];
}

string generate_surname(){
	vector<string> NamePrefix = {"", "bel", "nar", "xan", "bell", "natr", "ev"};
	vector<string> NameSuffix= {"", "us", "ix", "ox", "ith","ath", "um", "ator", "or", "axia", "imus", "ais", "itur", "orex", "o", "y"};
	vector<string> NameStems = {"adur", "aes", "anim", "apoll", "imac", "educ", "equis", "extr", "guius", "hann","equi", "amora", "hum", "iace", "ille", "inept", "iuv", "obe", "ocul", "orbis"};
	string Name;
	Name += NamePrefix[(rand() % NamePrefix.size())];
	Name += NameStems[(rand() % NameStems.size())];
	Name += NameSuffix[(rand() % NameSuffix.size())];
	Name[0]=toupper(Name[0]);
	return Name;

}

int main(int argc, char** argv){
	int count  = 50;
	cout<<"Name"<<','<<"Surname"<<','<<"CurrentLatitute"<<','<<"CurrentLongitude"<<endl;
        for (int i=0; i<argc; i++){
                cerr<<argv[i]<<endl;
                if (strcmp(argv[i],"-n")==0 && i!=argc-1) {
                        stringstream parse(argv[i+1]);
                        parse>>count;
                }
        }
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
	for (int i=0; i<count; i++){
		int rnd = rand()*65536+rand();
		dataItem cur = inp[rnd%inp.size()];
		cout<<generate_name()<<','<<generate_surname()<<','<<cur.lat<<','<<cur.lon<<endl;
	}
}
