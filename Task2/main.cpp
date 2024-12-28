/*�������:
|
b+ ./\./\.
 |/       \
 |\       /
 |/       \
 |\.  .  ./
 |  \/ \/
 +--|-----|--------->
 \__/     a
   c
��������� ���������, ������� ����������, ����������� �� ����� � ������������
(x, y) ����� �� �������������� �������� x, � �������������� �� ���������
  �����: ���������� ����� ������������	������: 4354	������: 1.1.2024
  ����: 26.09.24*/
#include <iostream>
#include <math.h>

using namespace std;

void main(void)
{
	setlocale(LC_ALL, "Russian");

	float a, b, c, x, y;

	cout << "�������: \n" <<
		" |\n" <<
		"b+ ./\\./\\.     \n" <<
		" |/       \\    \n " <<
		"|\\       /    \n" <<
		" |/       \\     \n" <<
		" |\\.  .  ./      \n" <<
		" |  \\/ \\/      \n" <<
		" +--|-----|--------->     \n" <<
		" \\__/     a   \n" <<
		"   c  \n" <<
		"��������� ���������, ������� ����������, ����������� �� ����� � ������������ \n" <<
		"(x, y) ����� �� �������������� �������� x, � �������������� �� ���������\n" <<
		"�����: ���������� ����� ������������	������ : 4354	������ : 1.1.2024\n" <<
		"���� : 26.09.24\n"
		<< "������� a, b:\n";
	cin >> a >> b;


	if (fabs(a) != fabs(b))
	{
		cout << "������ fabs(a) != fabs(b)";
		exit(0);
	}
	cout << "������� c:";
	cin >> c;
	if (c < 0 && a > 0)
	{
		cout << "������ c < 0";
		exit(0);
	}
	if (c > 0 && a < 0)
	{
		cout << "������ c > 0";
		exit(0);
	}
	if (c > (a / 2) && a >= 0)
	{
		cout << "������ c > (a / 2)";
		exit(0);
	}
	if (c < (a / 2) && a < 0)
	{
		cout << "������ c > (a / 2)";
		exit(0);
	}

	cout << "������� ���������� ����� x, y:";
	cin >> x >> y;

	if (x == 0 && y == 0 && a == 0)
	{
		cout << "����� � ������������ x = " << x << ", y = " << y << " ����� ������ ������";
		exit(0);
	}
	if (x != 0 && a == 0)
	{
		cout << "����� � ������������ x = " << x << ", y = " << y << " �� ����� ������ ������";
		exit(0);
	}

	int k_x = floor(x / a);
	int k_y = floor(y / b);

	if (abs(k_x) == abs(k_y))
	{
		if (c == 0)
		{
			cout << "����� � ������������ x = " << x << ", y = " << y << " ����� ������ ������";
			exit(0);
		}

		x = fabs(fmod(x, a));
		y = fabs(fmod(y, b));
		c = fabs(c), a = fabs(a), b = fabs(b);

			if (x <= a / 2 && y <= b / 2)
			{
				if ((y >= -x + c) && (y >= x - c) && (y <= x + c))
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " ����� ������ ������";
					exit(0);
				}
				else
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " �� ����� ������ ������";
					exit(0);
				}
			}
			else if (x > a / 2 && y <= b / 2)
			{
				if ((y >= -x + a - c) && (y >= x + c - a) && (y <= -x + a + c))
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " ����� ������ ������";
					exit(0);
				}
				else
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " �� ����� ������ ������";
					exit(0);
				}
			}
			else if (x >= a / 2 && y > b / 2)
			{
				if ((y <= x + c) && (y >= x - c) && (y <= -x + 2 * a - c))
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " ����� ������ ������";
					exit(0);
				}
				else
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " �� ����� ������ ������";
					exit(0);
				}
			}
			else if (x < a / 2 && y > b / 2)
			{
				if ((y <= x + a - c) && (y >= -x + a - c) && (y <= -x + a + c))
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " ����� ������ ������";
					exit(0);
				}
				else
				{
					cout << "����� � ������������ x = " << x << ", y = " << y << " �� ����� ������ ������";
					exit(0);
				}
			}
	}
	else
	{
		cout << "����� � ������������ x = " << x << ", y = " << y << " �� ����� ������ ������";
		exit(0);
	}
}
