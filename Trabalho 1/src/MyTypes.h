#include <string>
#include <vector>
using namespace std;

struct Line
{
	int ID, freq_circ;
	vector<string> stops; 
	vector<int> time_stops;

};

struct Driver
{
	int ID, hours_day, max_hours, rest_time;
	string name;
	bool available;

};