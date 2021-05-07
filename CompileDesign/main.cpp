#include "string.h"
#include "stdio.h"
#include"scanner.h"
#include"recursive_descent.h"
#include"LL1.h"

int main() {
	/* LL1*/
	clock_t start, finish;
	double totaltime;
	start = clock();
	parser();
	cout << endl;
	if (haveError == false)
	{
		cout << "Print syntax tree!";
		printTree(0, 0);
	}
	else {
		for (int i = 0; i < errorList.size(); i++)
		{
			cout << errorList[i];
		}
	}
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n�˳��������ʱ��Ϊ" << totaltime << "�룡" << endl;
	/*  LL1*/

	///* �ʷ�����*/
	//const char* f = "D:\\�μ�\\ѧϰ-������\\����ԭ�����\\3.txt";
	//l = getTokenvector(f);
	////2.����������
	//vector<Token>::iterator it;
	//for (it = l.begin(); it != l.end(); it++) {
	//	cout << "<" << it->line << "," << it->lex << "," << it->sem << ">" << endl;
	//}
	///* �ʷ����� */

	/* �ݹ��½� */
	//const char* f = "D:\\�μ�\\ѧϰ-������\\����ԭ�����\\3.txt";
	//getPredict();
	//l = getTokenvector(f);
	//printf("Parser start!\n");
	//Program();
	/* �ݹ��½�*/

	//for (int i = 0; i < predict.size(); i++)
	//{
	//	cout << i << '\t';
	//	for (int j = 0; j < predict[i].size(); j++)
	//	{
	//		string tt = predict[i][j];
	//		cout << tt << '\t';
	//	}
	//	cout << endl;
	//}
	system("pause");
}