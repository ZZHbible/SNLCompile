#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include <vector>
#include<vector>
using namespace std;
#define MAXRESERVED 21  // 定义保留字数量常量 MAXRESERVED 为 21
typedef enum {
	ID,          /* 标识符 */
	CHAR,        /* 字符标识符 */
	INTC,    /* 无符号整数标识符 */
	UNDERANGE,   /* 数组下标界限符: '..' */
	ASSIGN,      /* 双字符分界符: '=' */
	ERROR,       /* 错误 */
	/* 保留字 */
	PROGRAM, PROCEDURE, TYPE, VAR, IF, INTEGER,
	THEN, ELSE, FI, WHILE, DO,
	ENDWH, BEGIN, END, READ, WRITE,
	ARRAY, RECORD, OF, RETURN,
	/* 单字符分界符 */
	EQ, GT, LT, PLUS, MINUS, TIMES, OVER,      // '=', '<', '+', '-', '*', '/',
	LMIDPAREN, RMIDPAREN, LPAREN, RPAREN,  // '(', ')', '[', ']'
	DOT, SEMI, COMMA, COLON                      // '.', ';', ',' ,':'
} LexType;
string getLexString(int i)
{
	switch (i)
	{
	case 0:return "ID";
	case 1:return "CHAR";
	case 2:return "INTC";
	case 3:return "UNDERANGE";
	case 4:return "ASSIGN";
	case 5:return "ERROR";
	case 6:return "PROGRAM";
	case 7:return "PROCEDURE";
	case 8:return "TYPE";
	case 9:return "VAR";
	case 10:return "IF";
	case 11:return "INTEGER";
	case 12:return "THEN";
	case 13:return "ELSE";
	case 14:return "FI";
	case 15:return "WHILE";
	case 16:return "DO";
	case 17:return "ENDWH";
	case 18:return "BEGIN";
	case 19:return "END";
	case 20:return "READ";
	case 21:return "WRITE";
	case 22:return "ARRAY";
	case 23:return "RECORD";
	case 24:return "OF";
	case 25:return "RETURN";
	case 26:return "EQ";
	case 27:return "GT";
	case 28:return "LT";
	case 29:return "PLUS";
	case 30:return "MINUS";
	case 31:return "TIMES";
	case 32:return "OVER";
	case 33:return "LMIDPAREN";
	case 34:return "RMIDPAREN";
	case 35:return "LPAREN";
	case 36:return "RPAREN";
	case 37:return "DOT";
	case 38:return "SEMI";
	case 39:return "COMMA";
	case 40:return "COLON";
	default:
		break;
	}
}

LexType getLexType1(string s) {
	if (s == "ID")return ID;
	else if (s == "CHAR")return CHAR;
	else if (s == "INTC")return INTC;
	else if (s == "UNDERANGE")return UNDERANGE;
	else if (s == "ASSIGN")return ASSIGN;
	else if (s == "PROGRAM")return PROGRAM;
	else if (s == "PROCEDURE")return PROCEDURE;
	else if (s == "TYPE")return TYPE;
	else if (s == "VAR")return VAR;
	else if (s == "IF")return IF;
	else if (s == "INTEGER")return INTEGER;
	else if (s == "THEN")return THEN;
	else if (s == "ELSE")return ELSE;
	else if (s == "FI")return FI;
	else if (s == "WHILE")return WHILE;
	else if (s == "DO")return DO;
	else if (s == "ENDWH")return ENDWH;
	else if (s == "BEGIN")return BEGIN;
	else if (s == "END")return END;
	else if (s == "READ")return READ;
	else if (s == "WRITE")return WRITE;
	else if (s == "ARRAY")return ARRAY;
	else if (s == "RECORD")return RECORD;
	else if (s == "OF")return OF;
	else if (s == "EQ")return EQ;
	else if (s == "GT")return GT;
	else if (s == "LT")return LT;
	else if (s == "PLUS")return PLUS;
	else if (s == "MINUS")return MINUS;
	else if (s == "TIMES")return TIMES;
	else if (s == "OVER")return OVER;
	else if (s == "LMIDPAREN")return LMIDPAREN;
	else if (s == "RMIDPAREN")return RMIDPAREN;
	else if (s == "LPAREN")return LPAREN;
	else if (s == "RPAREN")return RPAREN;
	else if (s == "DOT")return DOT;
	else if (s == "SEMI")return SEMI;
	else if (s == "COMMA")return COMMA;
	else if (s == "COLON")return COLON;
	return ERROR;
}


// 保留字查找表
static struct {
	string str;
	LexType tok;
} reservedWords[MAXRESERVED] = {
	{"program",PROGRAM},{"type",TYPE},{"var",VAR},
	{"procedure",PROCEDURE},{"begin",BEGIN},{"end",END},
	{"array",ARRAY},{"of",OF},{"record",RECORD},{"if",IF},{"then",THEN},
	{"else",ELSE},{"fi",FI},{"while",WHILE},{"do",DO},{"endwh",ENDWH},
	{"read",READ},{"write",WRITE},{"return",RETURN},
	{"integer",INTEGER},{"char",CHAR}
};

// Token实体类
class Token {
public:
	int line;  // 行数
	LexType lex;   // 词法信息(单词总类)
	string sem;    // 语意信息(单词字符串本身)
public:
	Token() {}
	Token(int line, LexType lex, string sem) { this->line = line; this->lex = lex; this->sem = sem; }
};
// 判断当前字符是否为字母
bool flag(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
		return true;
	}
	return false;
}

// 判断当前字符是否为数字
bool flag1(char ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	return false;
}

// 判断当前字符是否为单字符分界符
bool flag2(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')'
		|| ch == '[' || ch == ']' || ch == ';' || ch == '=' || ch == '>' || ch == '<' || ch == ',') {
		return true;
	}
	return false;
}

// 区分是哪一个单分界符
LexType kind(string s) {
	char ch = s[0];
	switch (ch) {
	case '=':
		return EQ;
	case '>':
		return GT;
	case '<':
		return LT;
	case '+':
		return PLUS;
	case '-':
		return MINUS;
	case '*':
		return TIMES;
	case '/':
		return OVER;
	case '(':
		return LMIDPAREN;
	case ')':
		return RMIDPAREN;
	case '[':
		return LPAREN;
	case ']':
		return RPAREN;
	case '.':
		return DOT;
	case ';':
		return SEMI;
	case ',':
		return COMMA;
	case ':':
		return COLON;
	default:
		return DOT;
	}
}
// 字符串大写字符转为小写
string change(string s) {
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += 32;
		}
	}
	return s;
}

// 判断字符串是否为保留字
bool judge(string s) {
	s = change(s);  // 转为小写
	for (int i = 0; i < MAXRESERVED; i++) {
		if (s == reservedWords[i].str) {
			return true;
		}
	}
	return false;
}

// 获取LexType
LexType getLexType(string s) {
	for (int i = 0; i < MAXRESERVED; i++) {
		if (s == reservedWords[i].str) {
			return reservedWords[i].tok;
		}
	}
	return ERROR;
}

vector<Token> l;
// 获取token序列
vector<Token> getTokenvector(const char* filename) {

	// 1.变量
	enum State { s0, s1, s2, s3, s4, s5, s6, s7, s8 };  // DFA的所有状态：开始，保留字，数字，完成，赋值，注释，数组下标，标识符，错误
	int buffer;                                  // 用于读入字符
	State state = s0;                            // 初始状态为START
	string str;                                  // 用于接单词
	int line = 1, row = 1;                       // 行数，列数
	Token* token;                                // token
	vector<Token> tokenvector;                       // token链表


	// 2.打开文件：需要解析的源代码.txt
	int temp = 1;  // 判断是否成功打开文件
	FILE* fp;
	if (!(fp = fopen(filename, "r"))) {
		cout << "NOT FIND FILE" << endl;
		temp = 0;
	}

	// 3.读取文件
	//int i = 0;
	while (!feof(fp) && temp) {
		//i++;
		switch (state) {
		case s0:  // 开始状态
			string().swap(str);  // 每次回到初始状态，字符串都 置空 准备重新接受字符
			buffer = fgetc(fp);  // 获取一个字符
			if ((char)buffer == '\n') {  // 如果是'\n'行数+1
				line++;
				row = 1;
				break;
			}
			else if ((char)buffer == '\t') { //如果是\t跳过
				row += 6;
				break;
			}
			else if ((char)buffer == ' ') {  // 如果是' '跳过
				row++;
				break;
			}
			else if (flag((char)buffer)) {  // 如果是字母跳转s1状态
				str += (char)buffer;  // 接单词
				row++;
				state = s1;
				break;
			}
			else if (flag1((char)buffer)) {  // 如果是数字跳转s2状态
				str += (char)buffer;  // 接数字
				row++;
				state = s2;
				break;
			}
			else if (flag2((char)buffer)) {  // 如果是单字符分界符跳转s3状态
				str = (char)buffer;  // 接单字符分界符
				row++;
				state = s3;
				break;
			}
			else if ((char)buffer == ':') {  // 如果是':'跳转s4状态
				str = (char)buffer;  // 接':'
				row++;
				state = s4;
				break;
			}
			else if ((char)buffer == '{') {  // 如果是'{'跳转s5状态
				state = s5;
				break;
			}
			else if ((char)buffer == '.') {  // 如果是'.'跳转s6状态
				str = (char)buffer;  // 接'.'
				row++;
				state = s6;
				break;
			}
			else {  // 错误状态
				state = s8;
				break;
			}
			break;
		case s1:  // 保留字状态
			while ((buffer = fgetc(fp)) != -1 && (flag((char)buffer) || flag1((char)buffer)) && !feof(fp)) {
				str += (char)buffer;  // 接单词
				row++;                // 列数+1
			}
			ungetc(buffer, fp);
			if (!judge(str)) { // 标识符状态
				state = s7;
				break;
			}
			else {
				// 保留字生成token链入链表
				str = change(str);  // 保留字转小写
				token = new Token(line, getLexType(str), str);
				tokenvector.push_back(*token);
				// 回到初始状态继续读下一个单词
				state = s0;
				break;
			}
		case s2:  // 数字状态
			while ((buffer = fgetc(fp)) != -1 && !feof(fp) && flag1((char)buffer)) {
				str += (char)buffer;
				row++;
			}
			ungetc(buffer, fp);
			token = new Token(line, INTC, str);
			tokenvector.push_back(*token);
			state = s0;
			break;
		case s3:  // 完成状态(单字符分界符)
			// 保留字生成token链入链表
			token = new Token(line, kind(str), str);
			tokenvector.push_back(*token);
			// 回到初始状态继续读下一个单词
			state = s0;
			break;
		case s4:  // 赋值状态(:=)
			// 获取一个字符
			buffer = fgetc(fp);
			str += (char)buffer;
			row++;
			// 判断是否是赋值符号，不是则跳转错误状态
			if ((char)buffer == '=') {
				// 保留字生成token链入链表
				token = new Token(line, ASSIGN, str);
				tokenvector.push_back(*token);
				// 回到初始状态继续读下一个单词
				state = s0;
			}
			else {
				state = s8;  // 跳转错误状态
			}
			break;
		case s5:  // 注释状态({)
			buffer = fgetc(fp);  // 获取一个字符
			while (!feof(fp) && (char)buffer != '}') {
				buffer = fgetc(fp);
			}
			state = s0;  // 回到初始状态继续读下一个单词
			break;
		case s6:  // 点状态(..)
			if (feof(fp) || (buffer = fgetc(fp)) != '.') {
				token = new Token(line, DOT, ".");
				tokenvector.push_back(*token);
				fclose(fp); //关闭文件
				return tokenvector;  // 程序结束
			}
			else {
				str += (char)buffer;  // if已经读了一个buffer
				row++;
				// 保留字生成token链入链表
				token = new Token(line, UNDERANGE, str);
				tokenvector.push_back(*token);
				// 回到初始状态继续读下一个单词
				state = s0;
			}
			break;
		case s7:  // 标识符状态
			// 保留字生成token链入链表
			token = new Token(line, ID, str);
			tokenvector.push_back(*token);
			// 回到初始状态继续读下一个单词
			state = s0;
			break;
		case s8:  // 错误状态
			// 保留字生成token链入链表
			token = new Token(line, ERROR, str);
			tokenvector.push_back(*token);
			// 回到初始状态继续读下一个单词
			state = s0;
			break;
		default:
			break;
		}
	}

	return tokenvector;
}