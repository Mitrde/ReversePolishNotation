#include<iostream>
#include <cstdlib>
#include "Arithmetic.h"

using namespace std;



int main()
{
	setlocale(LC_ALL, "Russian");

	char str1[256] = { 0 };
	char str2[256] = { 0 };
	double res = 0;
	cout << "������� �������������� ���������:" << endl;
	gets_s(str1);


	if (correct(str1)){

		opn(str1, str2);
		cout << " �������� �������� ������: " << endl;
		cout << str2 << endl;
		res = result(str2);
		cout << "��������� ��������������� ���������: " << endl;
		cout << res << endl;

	}
	else { cout << "��������� �� ���������!" << endl; }
	system("pause");
	return 0;
}

