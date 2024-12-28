/*
  Задание: Записать в массив В номера элементов массива А, которые равны max и min значениям массива А.
  Автор: Фанасюткин Роман Владимирович  Группа: 4354  Версия программы: 4.1.24
  Дата начала: 25.10.24  Завершения: 25.10.24
*/
#include <iostream>
#include <fstream>
#include <locale>
using namespace std;

void main()
{
	setlocale(LC_ALL, "russian");

	float *pA, *pB;
	float tmp = 0;
	int t = 0;
	unsigned int i = 0, j = 0;
	fstream f, g;

	g.open("out3.txt", ios::out);
	if (!g.is_open())
		cout << "Нет выходного файла";
	else
	{
		f.open("in3.txt", ios::in);
		if (!f.is_open())
			cout << "Нет входного файла";
		else
		{
			while (f >> tmp)
				t++;

			if (t == 0)
				g << "Файл пуст" << endl;
			else
			{
				pA = new float[t];
				pB = new float[2 * t];  

				f.clear();
				f.seekg(0, ios::beg);
				i = 0;
				while (f >> tmp)
				{
					*(pA + i) = tmp;
					i++;
				}
				f.close();
				g << "Количество элементов в A: " << t << "\n" << "A = {";
				for (i = 0; i < t; i++)
				{
					if (i != t - 1)
						g << *(pA + i) << ", ";
					else
						g << *(pA + i);
				}
				g << "}" << "\n";

				if (t != 0)
				{
					float max = *pA, min = *pA;
					for (i = 0; i < t; i++)
					{
						if (*(pA + i) > max)
							max = *(pA + i);
					}
					for (i = 0; i < t; i++)
					{
						if (*(pA + i) == max)
						{
							*(pB + j) = i;
							j++;
						}
					}
					for (i = 0; i < t; i++)
					{
						if (*(pA + i) < min)
							min = *(pA + i);
					}
					for (i = 0; i < t; i++)
					{
						if (*(pA + i) == min)
						{
							*(pB + j) = i;
							j++;
						}
					}
					g << "B = {";
					for (i = 0; i < j; i++)
					{
						if (i != j - 1)
							g << *(pB + i) << ", ";
						else
							g << *(pB + i);
					}
					g << "}";
				}
				else
					g << "B = {}";

				delete[] pA;
				delete[] pB;
			}
		}
		g.close();
	}
}