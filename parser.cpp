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

//estructura de un parser 
struct Parser
{
	map<pair<string,string>,vector<string>> parserTable;
	set<string> noTerminales;
	stack<string> pila;
};

void inicializaParser(Parser& parser)
{
	//inicializa tabla de parseo
	parser.parserTable.emplace(make_pair(pair<string,string>("A","{"),vector<string>{"B"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("B","{"),vector<string>{"{","C","H","}"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("C","num"),vector<string>{"D"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("C","bool"),vector<string>{"D"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","num"),vector<string>{"E","D"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","bool"),vector<string>{"E","D"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","id"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","break"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","{"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","if"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","do"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("D","while"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("E","num"),vector<string>{"G","F"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("E","bool"),vector<string>{"G","F"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("F","id"),vector<string>{"id",";"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("F","["),vector<string>{"[","ctenum","]","id",";"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("G","num"),vector<string>{"num"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("G","bool"),vector<string>{"bool"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("H","id"),vector<string>{"I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("H","break"),vector<string>{"I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("H","{"),vector<string>{"I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("H","if"),vector<string>{"I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("H","do"),vector<string>{"I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("H","while"),vector<string>{"I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("I","id"),vector<string>{"J","I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("I","break"),vector<string>{"J","I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("I","{"),vector<string>{"J","I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("I","if"),vector<string>{"J","I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("I","do"),vector<string>{"J","I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("I","while"),vector<string>{"J","I"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("I","}"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("J","id"),vector<string>{"L","=","N",";"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("J","break"),vector<string>{"break"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("J","{"),vector<string>{"B"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("J","if"),vector<string>{"if","(","N",")","J","K"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("J","do"),vector<string>{"do","J","while","(","N",")","J"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","while"),vector<string>{"while","(","N",")","J"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","else"),vector<string>{"else","J"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","id"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","if"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","break"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","{"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","do"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("K","while"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("L","id"),vector<string>{"id","M"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("M","["),vector<string>{"[","N","]","M"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("M","="),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("N","id"),vector<string>{"P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("N","ctenum"),vector<string>{"P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("N","("),vector<string>{"P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("N","true"),vector<string>{"P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("N","false"),vector<string>{"P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("O","=="),vector<string>{"==","P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("O","||"),vector<string>{"||","P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("O","&&"),vector<string>{"&&","P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("O","!="),vector<string>{"!=","P","O"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("O",")"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("O",";"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("P","("),vector<string>{"R","Q"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("P","ctenum"),vector<string>{"R","Q"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("P","true"),vector<string>{"R","Q"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("P","false"),vector<string>{"R","Q"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("P","id"),vector<string>{"R","Q"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q","<"),vector<string>{"<","R"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q","<="),vector<string>{"<=","R"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q",">"),vector<string>{">","R"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q",">="),vector<string>{">=","R"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q","=="),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q","||"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q","&&"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("Q","!="),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("R","("),vector<string>{"T","S"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("R","ctenum"),vector<string>{"T","S"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("R","true"),vector<string>{"T","S"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("R","false"),vector<string>{"T","S"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("R","id"),vector<string>{"T","S"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","+"),vector<string>{"+","T","S"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","-"),vector<string>{"-","T","S"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","=="),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","||"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","&&"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","!="),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","<"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S","<="),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S",">"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("S",">="),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("T","{"),vector<string>{"V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("T","ctenum"),vector<string>{"V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("T","true"),vector<string>{"V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("T","false"),vector<string>{"V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("T","id"),vector<string>{"V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("U","*"),vector<string>{"*","V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("U","/"),vector<string>{"/","V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("U","%"),vector<string>{"%","V","U"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("U","+"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("U","-"),vector<string>{""}));
	parser.parserTable.emplace(make_pair(pair<string,string>("V","("),vector<string>{"(","N",")"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("V","ctenum"),vector<string>{"ctenum"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("V","id"),vector<string>{"id"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("V","true"),vector<string>{"true"}));
	parser.parserTable.emplace(make_pair(pair<string,string>("V","false"),vector<string>{"false"}));

	//simbolos no terminales de la gramatica
	parser.noTerminales.emplace("A");
	parser.noTerminales.emplace("B");
	parser.noTerminales.emplace("C");
	parser.noTerminales.emplace("D");
	parser.noTerminales.emplace("E");
	parser.noTerminales.emplace("F");
	parser.noTerminales.emplace("G");
	parser.noTerminales.emplace("H");
	parser.noTerminales.emplace("I");
	parser.noTerminales.emplace("J");
	parser.noTerminales.emplace("K");
	parser.noTerminales.emplace("L");
	parser.noTerminales.emplace("M");
	parser.noTerminales.emplace("N");
	parser.noTerminales.emplace("O");
	parser.noTerminales.emplace("P");
	parser.noTerminales.emplace("Q");
	parser.noTerminales.emplace("R");
	parser.noTerminales.emplace("S");
	parser.noTerminales.emplace("T");
	parser.noTerminales.emplace("U");
	parser.noTerminales.emplace("V");

	//agregar el simbolo inicial al pila
	parser.pila.push("A");
}


int main()
{
	Parser parser;
	inicializaParser(parser);
	return 0;
}
