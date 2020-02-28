#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "functions.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cerr << "wrong arguments" << endl;
		return 1;
	}
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	if (!fin.is_open())
	{
		cerr << "Error " << argv[1] << " not open\n";
		return 1;
	}

	int numOfRow;
	int numOfColumn;

	fin >> numOfRow >> numOfColumn;

	map<Nav, string> transitions;

	string element;
	vector<string> vertexes;

	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
		{
			fin >> element;

			if (element != "-")
			{
				transitions[{ "q" + std::to_string(j), i }] = element;
				vertexes.push_back(element);
			}
		}
	}

	generateEdges(vertexes, transitions, numOfRow);
	vector<string> uniqueVertexes = fillUniqueVertexes(vertexes, numOfColumn);
	printTable(uniqueVertexes, transitions, fout, numOfRow);
}
