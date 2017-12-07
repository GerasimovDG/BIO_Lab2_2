// BIO_Lab2_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


bool InitWorld(int *mas, int tap, int m)
{
	int j = m - 1;
	while (j >= 0 && mas[j] == tap) j--;
	if (j < 0) return false;
	if (mas[j] >= tap)
		j--;
	mas[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		mas[k] = 1;
	return true;
}

int Sravn(string text, string pat)
{
	int count = 0;
	for (int i = 0;i < pat.length();i++)
	{
		if (text.substr(i, 1) != pat.substr(i, 1)) count++;
	}
	return count;
}

int TotalDistance(string str, string motiv)
{
	int min = INT_MAX;
	for (int i = 0; i < str.size() - motiv.size() + 1; i++)
	{
		int count = Sravn(str.substr(i, motiv.size()), motiv);
		if (count < min)
		{
			min = count;

		}
	}
	return min;
}
int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream fin("input.txt");
	ifstream fin2("input.txt");
	ofstream fout("output.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		int minRes = INT_MAX;
		string lc;
		string temp;
		string word;
		string bestWorld;
		int t = 0;

		char *symbol = new char[4];
		symbol[0] = 'A';
		symbol[1] = 'C';
		symbol[2] = 'G';
		symbol[3] = 'T';

		while (fin)
		{
			getline(fin, temp);
			t++;
		}
		t = t - 2;
		fin.close();
		getline(fin2, lc, '\n');
		int l = atoi(lc.c_str());	// размер шаблона
		cout << "Размер шаблона = " << l << endl;
		cout << "Число строк    = " << t << endl;
		string* DNA = new string[t];
		for (int i = 0; i < t; i++)
		{
			getline(fin2, DNA[i]);
			cout << DNA[i] << endl;
		}
		int *num = new int[l];
		for (int i = 0;i < l - 1;i++)
		{
			num[i] = 1;
		}
		num[l - 1] = 0;
		bool Work = true;
		while (Work)
		{
			Work = InitWorld(num, 4, l); //варианты мотива в числовой форме
			
			for (int k = 0;k < l;k++)
			{
				word = word + symbol[num[k] - 1];
			}

			int sum = 0;
			for (int i = 0; i < t;i++)
			{
				int tmp = TotalDistance(DNA[i], word);
				sum = sum + tmp;
			}
			if (sum < minRes) {
				minRes = sum;
				bestWorld.clear();
				bestWorld = word;
			}
			word.clear();
		}
		cout << minRes << endl;
		cout << "Лучшее слово: " << bestWorld << endl;
		fout << bestWorld << endl;
	}
	fout.close();
	return 0;
}

