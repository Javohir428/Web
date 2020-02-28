#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <algorithm>
#include <sstream>
#include "functions.h"

using namespace std;

vector<string> getReplacedStringToElements(string element)
{
	vector<string> elems;
	stringstream ss(element);
	string item;

	while (getline(ss, item, 'q'))
	{
		elems.push_back("q" + item);
	}

	sort(elems.begin(), elems.end());
	if (elems.capacity() > 1)
	{
		elems.erase(elems.begin());
		elems.resize(elems.size());
	}

	auto last = unique(elems.begin(), elems.end());
	elems.erase(last, elems.end());
	elems.resize(elems.size());

	return elems;
}

bool checkVertexInTransitions(string vertex, map<Nav, string>& transitions)
{
	bool inMap = false;

	for (auto element : transitions)
	{
		if (element.first.first == vertex)
		{
			inMap = true;
			break;
		}
	}

	return inMap;
}

string generateVertexTransitionValue(Nav pair, map<Nav, string>& transitions)
{
	string value;

	vector<string> elements = getReplacedStringToElements(pair.first);

	vector<string> valueParts;

	for (string element : elements)
	{
		auto it = transitions.find({ element, pair.second });

		if (it != transitions.end())
		{
			if (valueParts.empty())
			{
				auto v1 = getReplacedStringToElements((*it).second);
				valueParts = v1;
			}
			else
			{
				vector<string> temp;

				auto v1 = getReplacedStringToElements((*it).second);
				set_union(valueParts.begin(), valueParts.end(),
					v1.begin(), v1.end(), std::back_inserter(temp));

				valueParts = temp;

				temp.clear();
			}
		}
	}

	sort(valueParts.begin(), valueParts.end());
	auto last = unique(valueParts.begin(), valueParts.end());
	valueParts.erase(last, valueParts.end());

	for (string valuePart : valueParts)
	{
		value += valuePart;
	}

	return  value;
}

void generateEdges(vector<string>& vertexes, map<Nav, string>& transitions, int numOfRow)
{
	vector<string> temp;

	for (auto edge : vertexes)
	{
		if (!checkVertexInTransitions(edge, transitions))
		{
			for (int i = 0; i < numOfRow; i++)
			{
				Nav pair = { edge, i };
				string resultValue = generateVertexTransitionValue(pair, transitions);

				if (resultValue != "")
				{
					transitions[pair] = resultValue;

					auto it = find(vertexes.begin(), vertexes.end(), resultValue);
					if (it == vertexes.end())
					{
						temp.push_back(resultValue);
					}
				}
			}

		}
	}

	if (!temp.empty())
	{
		for (auto element : temp)
		{
			vertexes.push_back(element);
		}

		generateEdges(vertexes, transitions, numOfRow);

		temp.clear();
	}
}

vector<string> fillUniqueVertexes(vector<string> vertexes, int numOfColumn)
{
	vector<string> uniqueVertexes;

	for (int i = 0; i < numOfColumn; i++)
	{
		uniqueVertexes.push_back("q" + std::to_string(i));
	}
	for (auto vertex : vertexes)
	{
		auto iter = find(uniqueVertexes.begin(), uniqueVertexes.end(), vertex);
		if (iter == uniqueVertexes.end())
		{
			uniqueVertexes.push_back(vertex);
		}
	}

	return uniqueVertexes;
}


void printTable(vector<string> vertexes, map<Nav, string> transitions, ostream& output, int numOfRow)
{
	for (auto i = 0; i < numOfRow; i++)
	{
		for (auto j = 0; j < vertexes.size(); j++)
		{
			string el = transitions[{vertexes[j], i}];
			if (el != "")
			{
				output << el << " ";
			}
			else
			{
				output << "-" << " ";
			}
		}
		output << endl;
	}
}
