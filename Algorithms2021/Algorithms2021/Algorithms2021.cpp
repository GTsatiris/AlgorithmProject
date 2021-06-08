#include <iostream>
#include <string>
#include <sstream>

#include "Sorting.h"
#include "ShortestPath.h"

using namespace std;

int main()
{
	bool finish = false;
	string choice = "";
	while (!finish)
	{
		cout << endl << "*** PLEASE SELECT: ***" << endl;
		cout << "0: Sorting" << endl;
		cout << "1: Shortest Path" << endl;
		cout << "2: EXIT" << endl;
		getline(cin, choice);
		stringstream sstream(choice);
		
		int ch = 0;
		sstream >> ch;

		switch (ch)
		{
		case 0:
			DoSorting();
			break;
		case 1:
			DoDijkstra();
			break;
		case 2:
			finish = true;
			break;
		default:
			cout << "INVALID CHOICE!!" << endl;
			break;
		}
	}
}