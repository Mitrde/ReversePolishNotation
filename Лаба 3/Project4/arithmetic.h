#pragma once

#include<iostream>
#include"Stack.h"
#include<string.h>
using namespace std;

const int MAX_DIGIT_SIZE = 8;   //максимальный размер многозначного числа

int prioritet(char s)               //приоритет символа
{
	switch (s)
	{
	case '(':
	case ')': return 1;
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	case '^': return 4;
	}

}

bool isalpha(char s)                     //проверка , €вл€етс€ ли однозначным числом
{
	return s >= '0' && s <= '9';
}

bool isoperation(char s)                // проверка , €вл€етс€ ли символ операцией
{
	return s == '+' || s == '-' || s == '*' || s == '/' || s == '^';
}

bool correct(char *str)               // проверка корректности :   начало строки, подр€д идущие знаки операций, деление на 0, конец строки 
{
	int i = 0;
	bool r = true;

	if (!isalpha(str[0]) && str[0] != '-' && str[0] != '(')
		//		throw"incorrect input";
	{
		r = false;
		cout << "¬ыражение не должно начинатьс€ с некорректного знака операций или закрывающей скобки!  ";
	}

	int k = 0;
	while (str[i] != '\0')
	{
		if ((isoperation(str[i]) && isoperation(str[i + 1])) || (str[i] == '/' && str[i + 1] == '0'))
			//throw"incorrect input";
			k++;

		i++;
	}
	if (k != 0){
		cout << "Ќекорректно расставлены знаки операций (в том числе €вное деление на 0)!  "; // не€вное деление (как разница двух чисел) на 0 обрабатываетс€ как исключение на этапе
		r = false;                                                                                                 // вычислени€ обратной польской записи
	}


	if (isoperation(str[strlen(str) - 1]))
		//	throw"incorrect input";
	{
		cout << "¬ыражение заканчиваетс€ знаком операции!  ";
		r = false;
	}
	return r;
}

bool isdigit(int k, char *str, char *s) // проверка многозначности
{
	int i = 0;
	while (isalpha(str[k]))
	{
		s[i] = str[k];
		i++;
		k++;
	}
	k += i;
	if (i >= MAX_DIGIT_SIZE)
		throw"too large digit size";
	return true;
}


bool check_brackets(char *str)      //проверка открывающих и закрывающих скобок
{
	int i = 0;
	Stack <char> T(100);
	bool r = true;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			T.Push(str[i]);
		if (str[i] == ')')

		{
			try {
				if (T.isEmpty())	throw"incorrect input";
			}
			catch (char a) { cout << "—кобки расставлены неверно!  " << a << endl; }
		}
		else
		{
			while (T.top() != '(')
				T.Pop();
		}
	}
	i++;

	return r;
}//*/


void opn(char *str, char *str2)         //преобразование в постфиксную запись
{
	Stack<char> st;
	int i = 0;
	int j = 0;
	int k = 0;
	if (str[0] == '-')
	{
		st.Push('~');
		i++;
	}

	while (str[i] != '\0')
	{
		if (isalpha(str[i]))//проверка многозначности
		{
			str2[j] = str[i];
			j++;
			k = i + 1;
			int l = 0;
			while (isalpha(str[k]))
			{
				str2[j] = str[k];
				k++;
				j++;
				l++;
			}
			i += l;
			if (l >= MAX_DIGIT_SIZE)
				throw"too large digit";
			str2[j] = ' ';
			j++;
		}

		else if (isoperation(str[i]))   //преобразование
		{
			if (st.isEmpty() || prioritet(st.top()) < prioritet(str[i]))
			{
				st.Push(str[i]);
			}
			else if (prioritet(st.top()) >= prioritet(str[i]))
			{
				str2[j] = st.Pop();
				st.Push(str[i]);
				j++;
				str2[j] = ' ';
				j++;
			}
		}
		else if (str[i] == '(')
		{
			st.Push(str[i]);
			if (str[i + 1] == '-')
			{
				st.Push('~');
				i++;
			}
		}
		else if (str[i] == ')')
		{
			if (st.top() == '(' || st.isEmpty())
			{
				//throw"incorrect input";
				cout << " Ќекоректный ввод! (ћогут быть лишние скобки)  " << endl;
				break;
			}
			else
			{
				while (st.top() != '(')
				{
					str2[j] = st.Pop();
					j++;
					str2[j] = ' ';
					j++;
				}
			}
			st.Pop();
		}
		i++;
	}
	while (!st.isEmpty())
	{
		if (st.top() == '(')
		{
			//throw"error input";
			cout << "Ќекорректно расставлены скобки! (ѕреобразование в обратную польскую запись может быть выполнено неверно!)  \n";
			getchar();
			break;
		}
		else
		{
			str2[j] = st.Pop();
			j++;
			str2[j] = ' ';
			j++;
		}
	}
}

double result(char *str2)          //вычисление результата
{
	int i = 0;
	char *s = new char[MAX_DIGIT_SIZE];
	Stack<double> st(10);
	double alpha1, alpha2;
	while (str2[i] != '\0')
	{
		if (isalpha(str2[i]))//выделить подстроку
		{

			int l = 0;
			int k = i + 1;
			while (isalpha(str2[k]))
			{
				k++;
				l++;
			}
			if (str2[k + 1] == '~')//+1
			{

				s[0] = '-';
				int m = 1;
				while (m != l + 2)
				{
					s[m] = str2[k - l - 1];
					k++;
					m++;
				}
				i = i + l + 2;
			}
			else
			{
				s[0] = str2[i];
				int m = 1;
				while (m != l + 1)
				{
					s[m] = str2[k - l];
					k++;
					m++;
				}
				i += l;
			}
			st.Push(atof(s));        //atof преобразует строку в числовое значение типа дабл
			for (int i = 0; i < MAX_DIGIT_SIZE; i++)
				s[i] = 0;
		}
		else if (isoperation(str2[i]))
		{
			alpha1 = st.Pop();
			alpha2 = st.Pop();
			switch (str2[i])
			{
			case '+':
			{
						st.Push(alpha2 + alpha1);
			}
				break;
			case'-':
			{
					   st.Push(alpha2 - alpha1);
			}
				break;
			case'*':
			{
					   st.Push(alpha2 * alpha1);
			}
				break;
			case'/':
			{
					   if (alpha1 == 0)
						   throw"division by zero";     //ƒеление на 0 обрабатываетс€ как исключение во врем€ вычислени€ обратной польской записи
					   else
						   st.Push(alpha2 / alpha1);

			}
				break;
			case'^':
			{
					   if (alpha2 == 0)
						   throw"incorrect input";
					   double res = 1;
					   if (alpha1 == 0)
						   st.Push(res);
					   else if (alpha1 > 0)
					   {
						   int j = 0;
						   while (j != alpha1)
						   {
							   res *= alpha2;
							   j++;
						   }
						   st.Push(res);
					   }
					   else if (alpha1 < 0)
					   {
						   int j = 0;
						   while (j != -alpha1)
						   {
							   res *= alpha2;
							   j++;
						   }
						   st.Push(1 / res);
					   }
			}
				break;
			}
		}
		i++;
	}
	delete[] s;
	return (st.Pop());
}
