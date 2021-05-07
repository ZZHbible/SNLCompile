#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include <vector>
#include<vector>
using namespace std;
#define MAXRESERVED 21  // ���屣������������ MAXRESERVED Ϊ 21
typedef enum {
	ID,          /* ��ʶ�� */
	CHAR,        /* �ַ���ʶ�� */
	INTC,    /* �޷���������ʶ�� */
	UNDERANGE,   /* �����±���޷�: '..' */
	ASSIGN,      /* ˫�ַ��ֽ��: '=' */
	ERROR,       /* ���� */
	/* ������ */
	PROGRAM, PROCEDURE, TYPE, VAR, IF, INTEGER,
	THEN, ELSE, FI, WHILE, DO,
	ENDWH, BEGIN, END, READ, WRITE,
	ARRAY, RECORD, OF, RETURN,
	/* ���ַ��ֽ�� */
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


// �����ֲ��ұ�
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

// Tokenʵ����
class Token {
public:
	int line;  // ����
	LexType lex;   // �ʷ���Ϣ(��������)
	string sem;    // ������Ϣ(�����ַ�������)
public:
	Token() {}
	Token(int line, LexType lex, string sem) { this->line = line; this->lex = lex; this->sem = sem; }
};
// �жϵ�ǰ�ַ��Ƿ�Ϊ��ĸ
bool flag(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
		return true;
	}
	return false;
}

// �жϵ�ǰ�ַ��Ƿ�Ϊ����
bool flag1(char ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	return false;
}

// �жϵ�ǰ�ַ��Ƿ�Ϊ���ַ��ֽ��
bool flag2(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')'
		|| ch == '[' || ch == ']' || ch == ';' || ch == '=' || ch == '>' || ch == '<' || ch == ',') {
		return true;
	}
	return false;
}

// ��������һ�����ֽ��
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
// �ַ�����д�ַ�תΪСд
string change(string s) {
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += 32;
		}
	}
	return s;
}

// �ж��ַ����Ƿ�Ϊ������
bool judge(string s) {
	s = change(s);  // תΪСд
	for (int i = 0; i < MAXRESERVED; i++) {
		if (s == reservedWords[i].str) {
			return true;
		}
	}
	return false;
}

// ��ȡLexType
LexType getLexType(string s) {
	for (int i = 0; i < MAXRESERVED; i++) {
		if (s == reservedWords[i].str) {
			return reservedWords[i].tok;
		}
	}
	return ERROR;
}

vector<Token> l;
// ��ȡtoken����
vector<Token> getTokenvector(const char* filename) {

	// 1.����
	enum State { s0, s1, s2, s3, s4, s5, s6, s7, s8 };  // DFA������״̬����ʼ�������֣����֣���ɣ���ֵ��ע�ͣ������±꣬��ʶ��������
	int buffer;                                  // ���ڶ����ַ�
	State state = s0;                            // ��ʼ״̬ΪSTART
	string str;                                  // ���ڽӵ���
	int line = 1, row = 1;                       // ����������
	Token* token;                                // token
	vector<Token> tokenvector;                       // token����


	// 2.���ļ�����Ҫ������Դ����.txt
	int temp = 1;  // �ж��Ƿ�ɹ����ļ�
	FILE* fp;
	if (!(fp = fopen(filename, "r"))) {
		cout << "NOT FIND FILE" << endl;
		temp = 0;
	}

	// 3.��ȡ�ļ�
	//int i = 0;
	while (!feof(fp) && temp) {
		//i++;
		switch (state) {
		case s0:  // ��ʼ״̬
			string().swap(str);  // ÿ�λص���ʼ״̬���ַ����� �ÿ� ׼�����½����ַ�
			buffer = fgetc(fp);  // ��ȡһ���ַ�
			if ((char)buffer == '\n') {  // �����'\n'����+1
				line++;
				row = 1;
				break;
			}
			else if ((char)buffer == '\t') { //�����\t����
				row += 6;
				break;
			}
			else if ((char)buffer == ' ') {  // �����' '����
				row++;
				break;
			}
			else if (flag((char)buffer)) {  // �������ĸ��תs1״̬
				str += (char)buffer;  // �ӵ���
				row++;
				state = s1;
				break;
			}
			else if (flag1((char)buffer)) {  // �����������תs2״̬
				str += (char)buffer;  // ������
				row++;
				state = s2;
				break;
			}
			else if (flag2((char)buffer)) {  // ����ǵ��ַ��ֽ����תs3״̬
				str = (char)buffer;  // �ӵ��ַ��ֽ��
				row++;
				state = s3;
				break;
			}
			else if ((char)buffer == ':') {  // �����':'��תs4״̬
				str = (char)buffer;  // ��':'
				row++;
				state = s4;
				break;
			}
			else if ((char)buffer == '{') {  // �����'{'��תs5״̬
				state = s5;
				break;
			}
			else if ((char)buffer == '.') {  // �����'.'��תs6״̬
				str = (char)buffer;  // ��'.'
				row++;
				state = s6;
				break;
			}
			else {  // ����״̬
				state = s8;
				break;
			}
			break;
		case s1:  // ������״̬
			while ((buffer = fgetc(fp)) != -1 && (flag((char)buffer) || flag1((char)buffer)) && !feof(fp)) {
				str += (char)buffer;  // �ӵ���
				row++;                // ����+1
			}
			ungetc(buffer, fp);
			if (!judge(str)) { // ��ʶ��״̬
				state = s7;
				break;
			}
			else {
				// ����������token��������
				str = change(str);  // ������תСд
				token = new Token(line, getLexType(str), str);
				tokenvector.push_back(*token);
				// �ص���ʼ״̬��������һ������
				state = s0;
				break;
			}
		case s2:  // ����״̬
			while ((buffer = fgetc(fp)) != -1 && !feof(fp) && flag1((char)buffer)) {
				str += (char)buffer;
				row++;
			}
			ungetc(buffer, fp);
			token = new Token(line, INTC, str);
			tokenvector.push_back(*token);
			state = s0;
			break;
		case s3:  // ���״̬(���ַ��ֽ��)
			// ����������token��������
			token = new Token(line, kind(str), str);
			tokenvector.push_back(*token);
			// �ص���ʼ״̬��������һ������
			state = s0;
			break;
		case s4:  // ��ֵ״̬(:=)
			// ��ȡһ���ַ�
			buffer = fgetc(fp);
			str += (char)buffer;
			row++;
			// �ж��Ƿ��Ǹ�ֵ���ţ���������ת����״̬
			if ((char)buffer == '=') {
				// ����������token��������
				token = new Token(line, ASSIGN, str);
				tokenvector.push_back(*token);
				// �ص���ʼ״̬��������һ������
				state = s0;
			}
			else {
				state = s8;  // ��ת����״̬
			}
			break;
		case s5:  // ע��״̬({)
			buffer = fgetc(fp);  // ��ȡһ���ַ�
			while (!feof(fp) && (char)buffer != '}') {
				buffer = fgetc(fp);
			}
			state = s0;  // �ص���ʼ״̬��������һ������
			break;
		case s6:  // ��״̬(..)
			if (feof(fp) || (buffer = fgetc(fp)) != '.') {
				token = new Token(line, DOT, ".");
				tokenvector.push_back(*token);
				fclose(fp); //�ر��ļ�
				return tokenvector;  // �������
			}
			else {
				str += (char)buffer;  // if�Ѿ�����һ��buffer
				row++;
				// ����������token��������
				token = new Token(line, UNDERANGE, str);
				tokenvector.push_back(*token);
				// �ص���ʼ״̬��������һ������
				state = s0;
			}
			break;
		case s7:  // ��ʶ��״̬
			// ����������token��������
			token = new Token(line, ID, str);
			tokenvector.push_back(*token);
			// �ص���ʼ״̬��������һ������
			state = s0;
			break;
		case s8:  // ����״̬
			// ����������token��������
			token = new Token(line, ERROR, str);
			tokenvector.push_back(*token);
			// �ص���ʼ״̬��������һ������
			state = s0;
			break;
		default:
			break;
		}
	}

	return tokenvector;
}