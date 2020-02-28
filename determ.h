#pragma once

using namespace std;

using Nav = pair<string, int>;

vector<string> getReplacedStringToElements(string element);
bool checkVertexInTransitions(string vertex, map<Nav, string>& transitions);
string generateVertexTransitionValue(Nav pair, map<Nav, string>& transitions);
void generateEdges(vector<string>& vertexes, map<Nav, string>& transitions, int numOfRow);
void printTable(vector<string> vertexes, map<Nav, string> transitions, ostream& output, int numOfRow);
vector<string> fillUniqueVertexes(vector<string> vertexes, int numOfColumn);
