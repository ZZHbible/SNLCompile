#pragma once
#include"scanner.h"
/********************递归下降*******************/
vector<vector<string>>predict;
int tokens_num = 0;

void getPredict()
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
			predict.push_back(tempVec);
			tempVec.clear();
		}
		else if ((char)buffer == ',') { //如果是','则压入tempVec
			tempVec.push_back(str);
			string().swap(str);
		}
		else {
			str += (char)buffer;
		}
	}
	if (!str.empty()) { tempVec.push_back(str); predict.push_back(tempVec); }
	fclose(fp);
	for (int i = 0; i < predict.size(); i++)
	{
		for (int j = 0; j < predict[i].size(); j++)
		{
			if (predict[i][j] == "=")predict[i][j] = "EQ";
			if (predict[i][j] == "<") predict[i][j] = "LT";
			if (predict[i][j] == "+") predict[i][j] = "PLUS";
			if (predict[i][j] == "-") predict[i][j] = "MINUS";
			if (predict[i][j] == "*")predict[i][j] = "TIMES";
			if (predict[i][j] == "/") predict[i][j] = "OVER";
			if (predict[i][j] == "[") predict[i][j] = "LPAREN";
			if (predict[i][j] == "]") predict[i][j] = "RPAREN";
			if (predict[i][j] == ".")  predict[i][j] = "DOT";
			if (predict[i][j] == ";") predict[i][j] = "SEMI";
			if (predict[i][j] == ",") predict[i][j] = "COMMA";
			if (predict[i][j] == "(") predict[i][j] = "LMIDPAREN";
			if (predict[i][j] == ")") predict[i][j] = "RMIDPAREN";
			if (predict[i][j] == ":=") predict[i][j] = "ASSIGN";
		}
	}
}

//函数位置调整一下！！
bool match(string curToken, int num)
{
	if (getLexType1(curToken) == l[num].lex || getLexType(curToken) == l[num].lex) {
		printf("successfully match\t");
		cout << curToken << endl;;
		tokens_num++;
		return true;
	}
	return false;
}
void error(int n)
{
	cout << "line " << l.at(n).line << " 类型为 " << l.at(n).lex << " 内容为 " << l.at(n).sem << "  " << " error ";
}
void ActParamList();
void BaseName();
void DeclarePart();
void Exp();
void FieldDecList();
void FormList();
void IdList();
void Low();
void ParamDecList();
void ProcDec();
void StmList();
void Term();
void Top();
void TypeDecList();
void TypeName();
void VarDecList();
void VarIdList();

void MultOp()
{
	int flag = 0;
	for (int i = 0; i < predict[102].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[102][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[103].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[103][i]))flag1 = 1;
	}
	if (flag)	match("TIMES", tokens_num);
	else if (flag1) match("OVER", tokens_num);
	else error(tokens_num);
}
void CmpOp()
{
	int flag = 0;
	for (int i = 0; i < predict[98].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[98][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[99].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[99][i]))flag1 = 1;
	}
	if (flag) {
		match("LT", tokens_num);
	}
	else if (flag1) {
		match("EQ", tokens_num);
	}
	else error(tokens_num);
}

void AddOp()
{
	int flag = 0;
	for (int i = 0; i < predict[100].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[100][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[101].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[101][i]))flag1 = 1;
	}
	if (flag) match("PLUS", tokens_num);
	else if (flag1) match("MINUS", tokens_num);
	else error(tokens_num);
}
void FieldVarMore()
{
	int flag = 0;
	for (int i = 0; i < predict[96].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[96][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[97].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[97][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) {
		match("LPAREN", tokens_num);
		Exp();
		match("RPAREN", tokens_num);
	}
	else error(tokens_num);
}
void FieldVar()
{
	int flag = 0;
	for (int i = 0; i < predict[95].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[95][i]))flag = 1;
	}
	if (flag) {
		match("ID", tokens_num);
		FieldVarMore();
	}
	else error(tokens_num);
}
void VariMore()
{
	int flag = 0;
	for (int i = 0; i < predict[92].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[92][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[93].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[93][i]))flag1 = 1;
	}
	int flag2 = 0;
	for (int i = 0; i < predict[94].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[94][i]))flag2 = 1;
	}
	if (flag);
	else if (flag1) {
		match("LPAREN", tokens_num);
		Exp();
		match("RPAREN", tokens_num);
	}
	else if (flag2) {
		match("DOT", tokens_num);
		FieldVar();
	}
	else error(tokens_num);
}
void Variable()
{
	int flag = 0;
	for (int i = 0; i < predict[91].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[91][i]))flag = 1;
	}
	if (flag) {
		match("ID", tokens_num);
		VariMore();
	}
	else error(tokens_num);
}
void Factor()
{
	int flag = 0;
	for (int i = 0; i < predict[88].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[88][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[89].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[89][i]))flag1 = 1;
	}
	int flag2 = 0;
	for (int i = 0; i < predict[90].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[90][i]))flag2 = 1;
	}
	if (flag)
	{
		match("LMIDPAREN", tokens_num);
		Exp();
		match("RMIDPAREN", tokens_num);
	}
	else if (flag1) {
		match("INTC", tokens_num);
	}
	else if (flag2)Variable();
	else error(tokens_num);
}
void OtherFactor()
{
	int flag = 0;
	for (int i = 0; i < predict[86].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[86][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[87].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[87][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) {
		MultOp();
		Term();
	}
	else error(tokens_num);
}
void Term()
{
	int flag = 0;
	for (int i = 0; i < predict[85].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[85][i]))flag = 1;
	}
	if (flag) {
		Factor();
		OtherFactor();
	}
	else error(tokens_num);
}
void OtherTerm()
{
	int flag = 0;
	for (int i = 0; i < predict[83].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[83][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[84].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[84][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) {
		AddOp();
		Exp();
	}
	else error(tokens_num);
}
void Exp()
{
	int flag = 0;
	for (int i = 0; i < predict[82].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[82][i]))flag = 1;
	}
	if (flag) {
		Term();
		OtherTerm();
	}
	else error(tokens_num);
}
void OtherRelE()
{
	int flag = 0;
	for (int i = 0; i < predict[81].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[81][i]))flag = 1;
	}
	if (flag) {
		CmpOp();
		Exp();
	}
	else error(tokens_num);
}
void RelExp()
{
	int flag = 0;
	for (int i = 0; i < predict[80].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[80][i]))flag = 1;
	}
	if (flag) {
		Exp();
		OtherRelE();
	}
	else 	error(tokens_num);
}
void ActParamMore()
{
	int flag = 0;
	for (int i = 0; i < predict[78].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[78][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[79].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[79][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) {
		match("COMMA", tokens_num);
		ActParamList();
	}
	else error(tokens_num);
}
void ActParamList()
{
	int flag = 0;
	for (int i = 0; i < predict[76].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[76][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[77].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[77][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) {
		Exp();
		ActParamMore();
	}
	else error(tokens_num);
}


void CallStmRest()
{
	int flag = 0;
	for (int i = 0; i < predict[75].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[75][i]))flag = 1;
	}
	if (flag)
	{
		match("LMIDPAREN", tokens_num);
		ActParamList();
		match("RMIDPAREN", tokens_num);
	}
	else error(tokens_num);
}
void ReturnStm()
{
	int flag = 0;
	for (int i = 0; i < predict[74].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[74][i]))flag = 1;
	}
	if (flag)
	{
		match("return", tokens_num);
		match("LMIDPAREN", tokens_num);
		Exp();
		match("RMIDPAREN", tokens_num);
	}
	else error(tokens_num);
}
void OutputStm()
{
	int flag = 0;
	for (int i = 0; i < predict[73].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[73][i]))flag = 1;
	}
	if (flag)
	{
		match("write", tokens_num);
		match("LMIDPAREN", tokens_num);
		Exp();
		match("RMIDPAREN", tokens_num);
	}
	else error(tokens_num);
}
void InVar()
{
	int flag = 0;
	for (int i = 0; i < predict[72].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[72][i]))flag = 1;
	}
	if (flag)match("ID", tokens_num);
	else error(tokens_num);
}
void InputStm()
{
	int flag = 0;
	for (int i = 0; i < predict[71].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[71][i]))flag = 1;
	}
	if (flag)
	{
		match("read", tokens_num);
		match("LMIDPAREN", tokens_num);
		InVar();
		match("RMIDPAREN", tokens_num);
	}
	else
		error(tokens_num);

}
void LoopStm()
{
	int flag = 0;
	for (int i = 0; i < predict[70].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[70][i]))flag = 1;
	}
	if (flag) {
		match("while", tokens_num);
		RelExp();
		match("do", tokens_num);
		StmList();
		match("endwh", tokens_num);
	}
	else error(tokens_num);

}
void ConditionalStm()
{
	int flag = 0;
	for (int i = 0; i < predict[69].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[69][i]))flag = 1;
	}
	if (flag)
	{
		match("if", tokens_num);
		RelExp();
		match("then", tokens_num);
		StmList();
		match("else", tokens_num);
		StmList();
		match("fi", tokens_num);
	}
	else error(tokens_num);

}
void AssignmentRest()
{
	int flag = 0;
	for (int i = 0; i < predict[68].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[68][i]))flag = 1;
	}
	if (flag) {
		VariMore();
		match("ASSIGN", tokens_num);
		Exp();
	}
	else error(tokens_num);
}
void AssCall()
{
	int flag = 0;
	for (int i = 0; i < predict[66].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[66][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[67].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[67][i]))flag1 = 1;
	}
	if (flag)	AssignmentRest();
	else if (flag1)CallStmRest();
	else error(tokens_num);
}
void Stm()
{
	int flag = 0;
	for (int i = 0; i < predict[60].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[60][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[61].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[61][i]))flag1 = 1;
	}
	int flag2 = 0;
	for (int i = 0; i < predict[62].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[62][i]))flag2 = 1;
	}
	int flag3 = 0;
	for (int i = 0; i < predict[63].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[63][i]))flag3 = 1;
	}
	int flag4 = 0;
	for (int i = 0; i < predict[64].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[64][i]))flag4 = 1;
	}
	int flag5 = 0;
	for (int i = 0; i < predict[65].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[65][i]))flag5 = 1;
	}
	if (flag) {
		ConditionalStm();
	}
	else if (flag1) {
		LoopStm();
	}
	else if (flag2) {
		InputStm();
	}
	else if (flag3) {
		OutputStm();
	}
	else if (flag4) {
		ReturnStm();
	}
	else if (flag5) {
		match("ID", tokens_num);
		AssCall();
	}
	else error(tokens_num);
}
void StmMore()
{
	int flag = 0;
	for (int i = 0; i < predict[58].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[58][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[59].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[59][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) {
		match("SEMI", tokens_num);
		StmList();
	}
	else error(tokens_num);
}
void StmList()
{
	int flag = 0;
	for (int i = 0; i < predict[57].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[57][i]))flag = 1;
	}
	if (flag) {
		Stm();
		StmMore();
	}
	else error(tokens_num);
}
void ProgramBody()
{
	int flag = 0;
	for (int i = 0; i < predict[56].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[56][i]))flag = 1;
	}
	if (flag) {
		match("begin", tokens_num);
		StmList();
		match("end", tokens_num);
	}
	else error(tokens_num);
}
void ProcBody()
{
	int flag = 0;
	for (int i = 0; i < predict[55].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[55][i]))flag = 1;
	}
	if (flag) ProgramBody();
	else error(tokens_num);
}
void ProcDecPart()
{
	int flag = 0;
	for (int i = 0; i < predict[54].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[54][i]))flag = 1;
	}
	if (flag)
	{
		DeclarePart();
	}
	else error(tokens_num);
}
void FidMore()
{
	int flag = 0;
	for (int i = 0; i < predict[52].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[52][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[53].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[53][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) {
		match("COMMA", tokens_num);
		FormList();
	}
	else error(tokens_num);
}
void FormList()
{
	int flag = 0;
	for (int i = 0; i < predict[51].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[51][i]))flag = 1;
	}
	if (flag)
	{
		match("ID", tokens_num);
		FidMore();
	}
	else error(tokens_num);
}
void Param()
{
	int flag = 0;
	for (int i = 0; i < predict[49].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[49][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[50].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[50][i]))flag1 = 1;
	}
	if (flag) {
		TypeName();
		FormList();
	}
	else if (flag1)
	{
		match("var", tokens_num);
		TypeName();
		FormList();
	}
	else error(tokens_num);
}
void ParamMore()
{
	int flag = 0;
	for (int i = 0; i < predict[47].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[47][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[48].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[48][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)
	{
		match("SEMI", tokens_num);
		ParamDecList();
	}
	else error(tokens_num);
}
void ParamDecList()
{
	int flag = 0;
	for (int i = 0; i < predict[46].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[46][i]))flag = 1;
	}
	if (flag) {
		Param();
		ParamMore();
	}
	else error(tokens_num);
}
void ParamList()
{
	int flag = 0;
	for (int i = 0; i < predict[44].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[44][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[45].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[45][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) ParamDecList();
	else error(tokens_num);
}
void ProcName()
{
	int flag = 0;
	for (int i = 0; i < predict[43].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[43][i]))flag = 1;
	}
	if (flag)
	{
		match("ID", tokens_num);
	}
	else 	error(tokens_num);
}
void ProcDecMore()
{
	int flag = 0;
	for (int i = 0; i < predict[41].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[41][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[42].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[42][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)	ProcDec();
	else error(tokens_num);

}
void ProcDec()
{
	int flag = 0;
	for (int i = 0; i < predict[40].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[40][i]))flag = 1;
	}
	if (flag)
	{
		match("procedure", tokens_num);
		ProcName();
		match("LMIDPAREN", tokens_num);
		ParamList();
		match("RMIDPAREN", tokens_num);
		match("SEMI", tokens_num);
		ProcDecPart();
		ProcBody();
		ProcDecMore();
	}
	else error(tokens_num);
}
void ProcDecpart()
{
	int flag = 0;
	for (int i = 0; i < predict[38].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[38][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[39].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[39][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)
	{
		ProcDec();
	}
	else error(tokens_num);
}
void VarIdMore()
{
	int flag = 0;
	for (int i = 0; i < predict[36].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[36][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[37].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[37][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)
	{
		match("COMMA", tokens_num);
		VarIdList();
	}
	else error(tokens_num);
}
void VarIdList()
{
	int flag = 0;
	for (int i = 0; i < predict[35].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[35][i]))flag = 1;
	}
	if (flag) {
		match("ID", tokens_num);
		VarIdMore();
	}
	else 	error(tokens_num);
}
void VarDecMore()
{
	int flag = 0;
	for (int i = 0; i < predict[33].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[33][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[34].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[34][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)VarDecList();
	else error(tokens_num);
}
void VarDecList()
{
	int flag = 0;
	for (int i = 0; i < predict[32].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[32][i]))flag = 1;
	}
	if (flag) {
		TypeName();
		VarIdList();
		match("SEMI", tokens_num);
		VarDecMore();
	}
	else 	error(tokens_num);
}
void VarDec()
{
	int flag = 0;
	for (int i = 0; i < predict[31].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[31][i]))flag = 1;
	}
	if (flag) {
		match("var", tokens_num);
		VarDecList();
	}
	else 	error(tokens_num);
}
void VarDecpart()
{
	int flag = 0;
	for (int i = 0; i < predict[29].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[29][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[30].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[30][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) VarDec();
	else error(tokens_num);

}
void IdMore()
{
	int flag = 0;
	for (int i = 0; i < predict[27].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[27][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[28].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[28][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)
	{
		match("COMMA", tokens_num);
		IdList();
	}
	else error(tokens_num);
}
void FieldDecMore()
{
	int flag = 0;
	for (int i = 0; i < predict[24].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[24][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[25].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[25][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1) 	FieldDecList();
	else error(tokens_num);
}
void IdList()
{
	int flag = 0;
	for (int i = 0; i < predict[26].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[26][i]))flag = 1;
	}
	if (flag)
	{
		match("ID", tokens_num);
		IdMore();
	}
	else 	error(tokens_num);
}
void ArrayType()
{
	int flag = 0;
	for (int i = 0; i < predict[18].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[18][i]))flag = 1;
	}
	if (flag)
	{
		match("array", tokens_num);
		match("LPAREN", tokens_num);
		Low();
		match("UNDERANGE", tokens_num);
		Top();
		match("RPAREN", tokens_num);
		match("of", tokens_num);
		BaseName();
	}
	else error(tokens_num);
}
void FieldDecList()
{
	int flag = 0;
	for (int i = 0; i < predict[22].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[22][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[23].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[23][i]))flag1 = 1;
	}
	if (flag)
	{
		BaseName();
		IdList();
		match("SEMI", tokens_num);
		FieldDecMore();
	}
	else if (flag1)
	{
		ArrayType();
		IdList();
		match("SEMI", tokens_num);
		FieldDecMore();
	}
	else
		error(tokens_num);
}
void RecType()
{
	int flag = 0;
	for (int i = 0; i < predict[21].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[21][i]))flag = 1;
	}
	if (flag)
	{
		match("record", tokens_num);
		FieldDecList();
		match("end", tokens_num);
	}
	else error(tokens_num);
}
void Top()
{
	int flag = 0;
	for (int i = 0; i < predict[20].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[20][i]))flag = 1;
	}
	if (flag)match("INTC", tokens_num);
	else 	error(tokens_num);
}
void Low()
{
	int flag = 0;
	for (int i = 0; i < predict[19].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[19][i]))flag = 1;
	}
	if (flag)match("INTC", tokens_num);
	else 	error(tokens_num);
}

void StructureType()
{
	int flag = 0;
	for (int i = 0; i < predict[16].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[16][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[17].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[17][i]))flag1 = 1;
	}
	if (flag)ArrayType();
	else if (flag1)RecType();
	else error(tokens_num);
}
void BaseName()
{
	int flag = 0;
	for (int i = 0; i < predict[14].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[14][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[15].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[15][i]))flag1 = 1;
	}
	if (flag)
		match("integer", tokens_num);
	else if (flag1)
		match("char", tokens_num);
	else
		error(tokens_num);
}
void TypeName()
{

	int flag = 0;
	for (int i = 0; i < predict[11].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[11][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[12].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[12][i]))flag1 = 1;
	}

	int flag2 = 0;
	for (int i = 0; i < predict[13].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[13][i]))flag2 = 1;
	}
	if (flag)
		BaseName();
	else if (flag1)
		StructureType();
	else if (flag2)
		match("ID", tokens_num);
	else
		error(tokens_num);
}
void TypeId()
{
	int flag = 0;
	for (int i = 0; i < predict[10].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[10][i]))flag = 1;
	}
	if (flag)
	{
		match("ID", tokens_num);
	}
	else
		error(tokens_num);
}
void TypeDecMore()
{
	int flag = 0;
	for (int i = 0; i < predict[8].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[8][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[9].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[9][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)
	{
		TypeDecList();
	}
	else
		error(tokens_num);
}
void TypeDecList()
{
	int flag = 0;
	for (int i = 0; i < predict[7].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[7][i]))flag = 1;
	}
	if (flag)
	{
		TypeId();
		match("EQ", tokens_num);
		TypeName();
		match("SEMI", tokens_num);
		TypeDecMore();
	}
	else
		error(tokens_num);
}
void TypeDec()
{
	int flag = 0;
	for (int i = 0; i < predict[6].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[6][i]))flag = 1;
	}
	if (flag)
	{
		match("type", tokens_num);
		TypeDecList();
	}
	else
		error(tokens_num);
}
void TypeDecpart()
{
	int flag = 0;
	for (int i = 0; i < predict[4].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[4][i]))flag = 1;
	}
	int flag1 = 0;
	for (int i = 0; i < predict[5].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[5][i]))flag1 = 1;
	}
	if (flag);
	else if (flag1)
	{
		TypeDec();
	}
	else
		error(tokens_num);

}
void DeclarePart()
{
	int flag = 0;
	for (int i = 0; i < predict[3].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[3][i]))flag = 1;
	}
	if (flag)
	{
		TypeDecpart();
		VarDecpart();
		ProcDecpart();
	}
	else
		error(tokens_num);
}
void ProgramName()
{
	int flag = 0;
	for (int i = 0; i < predict[2].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[2][i]))flag = 1;
	}
	if (flag)
	{
		match("ID", tokens_num);
	}
	else
		error(tokens_num);
}

void ProgramHead()
{
	int flag = 0;
	for (int i = 0; i < predict[1].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[1][i]))flag = 1;
	}
	if (flag)
	{
		match("program", tokens_num);
		ProgramName();
	}
	else
		error(tokens_num);
}

void Program() //程序头
{
	int flag = 0;
	for (int i = 0; i < predict[0].size(); i++)
	{
		if (l[tokens_num].lex == getLexType1(predict[0][i]))flag = 1;
	}
	if (flag)
	{
		ProgramHead();
		DeclarePart();
		ProgramBody();
	}
	if (match("DOT", tokens_num))
		printf("0 errors");
	else
		error(tokens_num);
}

/****************递归下降****/
