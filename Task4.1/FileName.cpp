/*
  �������: �������� � ������ � ������ ��������� ������� �, ������� ����� max � min ��������� ������� �.
  �����: ���������� ����� ������������  ������: 4354  ������ ���������: 4.1.24
  ���� ������: 25.10.24  ����������: 25.10.24
*/
#include <iostream>
#include <fstream>
#include <locale>
using namespace std;

void main()
{
	setlocale(LC_ALL, "russian");

	const unsigned n = 100;
	float A[n], B[2*n];
	float tmp = 0;
	int t;
	unsigned int i = 0, j = 0;
	fstream f, g;

	g.open("out3.txt", ios::out);
	if (!g.is_open())
		cout << "��� ��������� �����";
	else
	{
		f.open("in3.txt", ios::in);
		if (!f.is_open())
			cout << "��� �������� �����";
		else
		{
			f >> t;
			if (f.eof())
				g << "���� ����";
			else
			{
				if (t < 0)
				{
					t = 0;
					g << "���� �������� ������������, t = 0";
				}
				if (t > n)
				{
					t = n;
					g << "���� �������� ������������, t = n";
				}
				while ((!f.eof()) && (i < t))
				{
					f >> tmp;
					if (!f.eof())
					{
						A[i] = tmp;
						i++;
					}
				}
				t = i;
				f.close();
				g << "���������� ��������� � A: " << t << "\n" << "A = {";
				for (i = 0; i < t; i++)
				{
					if (i != t-1)
						g << A[i] << ", ";
					else
						g << A[i];
				}
				g <<"}" << "\n";

				if (t != 0)
				{
					float max = A[0], min = A[0];
					for (i = 0; i < t; i++)
					{
						if (A[i] > max)
							max = A[i];
					}
					for (i = 0; i < t; i++)
					{
						if (A[i] == max)
						{
							B[j] = i;
							j++;
						}
					}
					for (i = 0; i < t; i++)
					{
						if (A[i] < min)
							min = A[i];
					}
					for (i = 0; i < t; i++)
					{
						if (A[i] == min)
						{
							B[j] = i;
							j++;
						}
					}
					g << "B = {";
					for (int i = 0; i < j; i++)
					{
						g << B[i] << ",";
					} 
					g << "}";
				}
				else
					g << "B = {}";
			}
		}
		g.close();
	}
}