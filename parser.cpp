#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <stack>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::set;
using std::stack;

struct parser
{
	map<pair<string,string>,vector<string>> parserTable;
	set<string> noTerminales;
	stack<string> pila;
};




int main()
{
	return 0;
}
