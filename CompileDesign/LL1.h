#pragma onceunultiSym;
#include<map>
#include<unordered_map>
#include"scanner.h"
using namespace std;


string strip(const string& str, char ch = ' ')
{
	//除去str两端的ch字符
	int i = 0;
	while (str[i] == ch)// 头部ch字符个数是 i
		i++;
	int j = str.size() - 1;
	while (str[j] == ch) //
		j--;
	return str.substr(i, j + 1 - i);
}


unordered_map<string, string> symName = { {"=","EQ"},{"<" ,"LT"},{"+" ,"PLUS"},{"-" ,"MINUS"},{"*" , "TIMES"},{"/" , "OVER"},{"[" , "LPAREN"},
{"]","RPAREN"},{"." , "DOT"},{";" , "SEMI"},{"," , "COMMA"},{"(" , "LMIDPAREN"},{")" , "RMIDPAREN"},{":=" , "ASSIGN"},{".." , "UNDERANGE"} };
vector<Token>tokens;
int curpos = 0;
Token curToken;
int curLine = 0;
map<int, vector<int>>syntaxTree; //语法树
map<int, string>syntaxTreeNode;	//语法树的节点
vector<string>ultiSym; //终极符表
vector<string>unultiSym; //非终极符表
vector<vector<string>>predict1; //predict集
//vector<vector<string>>LL1table; //LL1分析表
map<vector<string>, vector<string>> LL1table1;//LL1分析表
int nodenum = 0;  //树节点的int值，表示第几个节点
vector<int>emp;
bool haveError = false;
bool curTKErr = false;
string errorList = "";

void getNextToken()
{
	curpos += 1;
	curToken = tokens[curpos];
	curTKErr = false;
}

void getSym()
{

	int temp = 1;  // 判断是否成功打开文件
	FILE* fp;
	if (!(fp = fopen("D:\\课件\\学习-大三下\\编译原理课设\\ultiSym.txt", "r"))) {
		cout << "NOT FIND FILE" << endl;
		temp = 0;
	}
	int line = 1;
	string str;  //用于接单词
	int buffer;  // 用于读入字符
	while (!(feof(fp) && temp))
	{
		buffer = fgetc(fp);  // 获取一个字符
		if ((char)buffer == ' ')continue;
		if ((char)buffer == '\t')continue;
		if ((char)buffer == '\n') {  // 如果是'\n'行数+1
			if (str != "")
			{
				ultiSym.push_back(str);
				string().swap(str);
			}
		}
		else if ((char)buffer == ',') { //如果是','则压入tempVec
			ultiSym.push_back(str);
			string().swap(str);
		}
		else {
			if (buffer == -1)break;
			str += (char)buffer;
		}
	}
	fclose(fp);
	FILE* fp1;
	if (!(fp1 = fopen("D:\\课件\\学习-大三下\\编译原理课设\\unultiSym.txt", "r"))) {
		cout << "NOT FIND FILE" << endl;
		temp = 0;
	}
	line = 1;
	string().swap(str);  //用于接单词
	while (!(feof(fp1) && temp))
	{
		buffer = fgetc(fp1);  // 获取一个字符
		if ((char)buffer == ' ')continue;
		if ((char)buffer == '\t')continue;
		if ((char)buffer == '\n') {  // 如果是'\n'行数+1
			if (str != "")
			{
				unultiSym.push_back(str);
				string().swap(str);
			}
		}
		else if ((char)buffer == ',') { //如果是','则压入tempVec
			if (str != "")
			{
				unultiSym.push_back(str);
				string().swap(str);
			}
		}
		else {
			if (buffer == -1)break;
			str += (char)buffer;
		}
	}
	if (!str.empty())
		unultiSym.push_back(str);
	fclose(fp1);
}

void getPredict1()
{
	int temp = 1;  // 判断是否成功打开文件
	FILE* fp;
	if (!(fp = fopen("D:\\课件\\学习-大三下\\编译原理课设\\predict.txt", "r"))) {
		cout << "NOT FIND FILE" << endl;
		temp = 0;
	}
	int line = 1;
	string str;  //用于接单词
	int buffer;  // 用于读入字符
	vector<string> tempVec;
	while (!(feof(fp) && temp))
	{
		buffer = fgetc(fp);  // 获取一个字符
		if ((char)buffer == '\n') {  // 如果是'\n'行数+1
			tempVec.push_back(str);
			string().swap(str);
			predict1.push_back(tempVec);
			tempVec.clear();
		}
		else if ((char)buffer == ',') { //如果是','则压入tempVec
			tempVec.push_back(str);
			string().swap(str);
		}
		else {
			if (buffer == -1)break;
			str += (char)buffer;
		}
	}
	if (!str.empty()) { tempVec.push_back(str); predict1.push_back(tempVec); }
	fclose(fp);

}
vector<vector<string>>production;
void getProduction()
{
	vector<vector<string>> lines;
	int temp = 1;  // 判断是否成功打开文件
	FILE* fp;
	if (!(fp = fopen("D:\\课件\\学习-大三下\\编译原理课设\\production.txt", "r"))) {
		cout << "NOT FIND FILE" << endl;
		temp = 0;
	}
	int line = 1;
	string str;  //用于接单词
	int buffer;  // 用于读入字符
	vector<string> tempVec;
	while (!(feof(fp) && temp))
	{
		buffer = fgetc(fp);  // 获取一个字符
		if (buffer == -1)break;
		if ((char)buffer == '\n') {  // 如果是'\n'行数+1
			tempVec.push_back(str);
			string().swap(str);
			if (!tempVec.empty())
				lines.push_back(tempVec);
			tempVec.clear();
		}
		else {
			if (buffer == -1)break;
			str += (char)buffer;
		}
	}
	if (!str.empty()) {
		tempVec.push_back(str); lines.push_back(tempVec);
	}
	fclose(fp);
	string left; //左边的非终极符
	vector<string> right; //右边的推导式
	for (int i = 0; i < lines.size(); i++)
	{
		string temp = strip(lines[i][0]);
		const char* deli_left_right = "::=";
		if (temp.find(deli_left_right) != string::npos)
		{
			char* left_t = strtok((char*)temp.data(), deli_left_right); //取出左边的表达式
			left = (string)left_t;
			left = strip(left);
			int erase = string(left_t).size() + 3;
			temp.erase(temp.begin(), temp.begin() + erase);
			while (temp != "")
			{
				temp = strip(temp);
				char* t_right = strtok((char*)temp.data(), " ");
				right.push_back((string)t_right);
				int erase = temp.size() == string(t_right).size() ? string(t_right).size() : string(t_right).size() + 1;
				temp.erase(temp.begin(), temp.begin() + erase);
			}
			right.insert(right.begin(), left);
			production.push_back(right);
			right.clear();
		}
		else //为|,  ID 这种情况
		{
			temp.erase(temp.begin(), temp.begin() + 1);
			while (temp != "")
			{
				temp = strip(temp);
				char* t_right = strtok((char*)temp.data(), " ");
				right.push_back((string)t_right);
				int erase = temp.size() == string(t_right).size() ? string(t_right).size() : string(t_right).size() + 1;
				temp.erase(temp.begin(), temp.begin() + erase); //逐个提取
			}
			right.insert(right.begin(), left);
			production.push_back(right);
			right.clear();
		}

	}

}

bool match(string curSym, string tokenSym)
{
	if (curSym == tokenSym)return true;
	int flag = 0;
	if (symName.find(curSym) != symName.end())
	{
		if (symName.at(curSym) == tokenSym)return true;
	}
	for (int i = 0; i < ultiSym.size(); i++)
	{
		if (ultiSym[i] == tokenSym)tokenSym = change(tokenSym);
	}
	if (tokenSym == curSym)return true;
	return false;

}

void Creat_LL1table()
{
	for (int k = 0; k < unultiSym.size(); k++)
	{
		string word = unultiSym[k];
		for (int j = 0; j < ultiSym.size(); j++)
		{
			string token = ultiSym[j];
			for (int i = 0; i < production.size(); i++)
			{
				vector<string> prod = production[i];  //取出每一个元素
				if (prod[0] == word)
				{
					vector<string> pre = predict1[i];
					int flag = 0;
					for (int m = 0; m < pre.size(); m++)
					{
						if (match(pre[m], token))flag = 1;
					}
					if (flag)
					{
						LL1table1.insert({ {word,token},{prod.begin() + 1,prod.end()} });//（word,token）--->(produnction的右部)，word为终极符，token为非终极符，在predict中能找到token即加入
					}
				}
			}
		}
	}
	//for (auto i : LL1table1) {
	//	cout << i.first[0] << " " << i.first[1]<<"->";
	//	for (auto j : i.second) {
	//		cout << j << " ";
	//	}
	//	cout << endl;
	//}
}

void init()
{
	tokens = getTokenvector("D:\\课件\\学习-大三下\\编译原理课设\\3.txt");
	getSym();
	getProduction();
	getPredict1();
	Creat_LL1table();
}

void error(int line, string expect, string found)
{
	if (curTKErr) return;
	curTKErr = true;
	string inf = "Error founded at line " + to_string(line) + " Expected " + " or " + expect + " Founded " + found + "\n";
	errorList.append(inf);
}

void addChild(int father, int son)
{
	if (syntaxTree.find(father) == syntaxTree.end())
	{
		vector<int> add;
		syntaxTree[father] = add;
	}

	syntaxTree[father].push_back(son);

}

bool doParser(int father)
{
	string curSym = syntaxTreeNode[father];
	string inf = getLexString(curToken.lex);
	if (inf == "")inf = "ERROR";
	int flag = 1;
	int i = 0;
	string LL1_sem = getLexString(curToken.lex);
	vector<string> search{ curSym,LL1_sem };
	vector<string> rightpart;
	if (LL1table1.find(search) != LL1table1.end()) 
	{
		flag = 0; rightpart = LL1table1.find(search)->second;
	}
	if (flag)
	{
		/*error 信息*/
		for (int i = 0; i < ultiSym.size(); i++)
		{
			int flag = 0;
			string word = ultiSym[i];
			vector<string> s{ curSym,word };
			if (LL1table1.find(s) != LL1table1.end()) {
				error(curToken.line, word, inf);
				haveError = true;
				return false;
			}
		}
	}
	cout << "Current Token:" << curToken.line << ' ' << curToken.lex << ' ' << curToken.sem << endl;
	cout << "Use production:" << curSym << "->";
	for (int i = 0; i < rightpart.size(); i++)
	{
		cout << rightpart[i] << ' ';
	}
	cout << endl;

	bool empty = true;

	for (int i = 0; i < rightpart.size(); i++)
	{
		string sym = rightpart[i];
		int flag = 0;
		for (int j = 0; j < ultiSym.size(); j++)
		{
			if (sym == ultiSym[j] || sym == change(ultiSym[j]))
			{
				flag = 1;
				break;
			}
			if (symName.find(sym) != symName.end()) {
				flag = 1;
				break;
			}
		}
		int flag1 = 0;
		for (int i = 0; i < unultiSym.size(); i++)
		{
			if (sym == unultiSym[i]) flag1 = 1;
		}
		if (flag)
		{
			cout << "CurUltiSym" << " " << sym;
			string inf = getLexString(curToken.lex);
			if (inf.size() == 0)inf = "ERROR";
			if (match(sym, getLexString(curToken.lex)))
			{
				empty = false;
				cout << "match ultimate symbol " << sym << " to " << inf << endl;
				nodenum++;
				syntaxTreeNode[nodenum] = inf;
				addChild(father, nodenum);
				getNextToken();
			}
			else {
				error(curToken.line, sym, inf);
			}
		}
		else if (flag1)
		{
			nodenum++;
			syntaxTreeNode[nodenum] = sym;
			addChild(father, nodenum);
			bool res = doParser(nodenum);
			if (res == false)empty = false;
		}

	}
	if (empty == true)
	{
		emp.push_back(father);
	}
	return empty;
}


void parser()
{
	init();
	curpos = -1;
	nodenum = 0;  //结点数
	getNextToken();
	syntaxTreeNode[nodenum] = "Program";
	doParser(0);
}

void printTree(int nodeid, int deep)
{
	for (int i = 0; i < emp.size(); i++)
	{
		if (nodeid == emp[i])return;
	}
	cout << endl;
	for (int i = 0; i < deep; i++)
	{
		cout << "     ";
	}
	cout << syntaxTreeNode[nodeid];
	if (syntaxTree.find(nodeid) == syntaxTree.end())return;
	vector<int>child = syntaxTree[nodeid];
	for (int i = 0; i < child.size(); i++)
	{
		printTree(child[i], deep + 1);
	}
}