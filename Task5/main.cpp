/* �������: ����� ���������� ������� �������������� ������� ������� A �������� N*N
  ��� ��������� N
       m    N/2
   [ ][ ][ ][ ][X][ ][ ]
 m [ ][ ][ ][X][ ][ ][ ]
   [ ][ ][X][ ][X][ ][ ]
N/2[ ][X][ ][ ][ ][X][ ]
   [X][ ][X][ ][ ][ ][X]
   [ ][ ][ ][X][ ][ ][ ]
   [ ][ ][ ][ ][X][ ][ ]
  �����: ���������� ����� ������������, ������ 4354, ������ ���������: 5.1.24
  ���� ������: 27.11.24  ����������: 06.12.24 */

#include <iostream>
#include <fstream>

using namespace std;

void CalcSize(fstream& fin, short& n0, short& n, short& m0, short& m);
void InpF(fstream& fin, float** Arr, short n);
void Process(short& n, short& m, float& max, float** Arr);
void OutString(fstream& fout, short n, short i, float** Arr);
bool OutTask(fstream& fout, string wayin, short n0, short n, short m0, short m, float** Arr);
void OutResult(fstream& fout, float max);

int main()
{
    setlocale(LC_ALL, "RU");

    fstream fin;
    fstream fout;
    short n, n0, m, m0;

    string wayin = "in.txt";
    string wayout = "out.txt";

    fout.open(wayout, ios::out);
    if (!fout.is_open())
        cout << "������ �������� ����� �� ������!\n";
    else
    {
        fin.open(wayin, ios::in);
        if (!fin.is_open())
            cout << "������ �������� ����� �� ������!";
        else
        {
            CalcSize(fin, n0, n, m0, m);
            float** Arr = new float* [n];
            for (short i = 0; i < n; i++)
                Arr[i] = new float[n] {};
            InpF(fin, Arr, n);
            if (!OutTask(fout, wayin, n0, n, m0, m, Arr))
            {
                float max = 0;
                Process(n, m, max, Arr);
                OutResult(fout, max);
            }
            for (short i = 0; i < n; i++)
                delete[] Arr[i];
            delete[] Arr;
        }
    }
    fout.close();
    fin.close();
}
void CalcSize(fstream& fin, short& n0, short& n, short& m0, short& m)
{
    fin >> n0;
    fin >> m0;
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���������� ������� ������ ����� n0 � m0

    if (n0 > 0)
    {
        n = n0;
        if (m0 > 0 && m0 <= n)
        {
            m = m0;
            float* B = new float[100]();
            float num;
            short i = 0, j = 0;

            while (fin >> num)
            {
                j++;
                if (fin.peek() == '\n' || fin.eof()) // ���� �������� ����� ������ ��� �����
                {
                    B[i] = j;
                    i++;
                    j = 0;
                }
            }

            short maxSquareSize = 0;
            for (short size = 1; size <= n; ++size)
            {
                bool valid = true;
                for (short row = 0; row < size; ++row)
                {
                    if (B[row] < size)
                    {
                        valid = false;
                        break;
                    }
                }
                if (valid)
                    maxSquareSize = size;
                else
                    break;
            }
            n = maxSquareSize;

            delete[] B;
        }
        else
        {
            m = 0;
        }
    }
    else
    {
        n = 0;
        m = 0;
    }
}
void InpF(fstream& fin, float** Arr, short n)
{
    float num, m;
    char sym;

    fin.clear();
    fin.seekg(0);
    fin << skipws;
    fin >> num;
    fin >> m;
    fin >> noskipws;
    for (short i = 0; i < n && !fin.eof(); i++)
    {
        for (short j = 0; j < n && !fin.eof(); j++)
        {
            fin >> sym;
            if (sym == ' ' || sym == '\t' || sym == '\n')
            {
                j--;
                continue;
            }
            else
            {
                fin.seekg(-1, ios::cur);
                fin >> num;
                *(*(Arr + j) + i) = num;
            }
        }
        while (sym != '\n' && !fin.eof())
        {
            fin >> sym;
        }
    }
}

void OutString(fstream& fout, short n, short i, float** Arr)
{
    string str;
    for (short j = 0; j < n; j++)
    {
        fout << *(*(Arr + j) + i) << "  ";
    }
    fout << "\n";
}

bool OutTask(fstream& fout, string wayin, short n0, short n, short m0, short m, float** Arr)
{
    bool a = 0;
    fout << "�������: ����� ���������� ������� �������������� ������� ������� A �������� N*N\n"
        << "��� ��������� N\n"
        << "       m    N/2\n"
        << "   [ ][ ][ ][ ][X][ ][ ]\n"
        << "  m[ ][ ][ ][X][ ][ ][ ]\n"
        << "   [ ][ ][X][ ][X][ ][ ]\n"
        << "N/2[ ][X][ ][ ][ ][X][ ]\n"
        << "   [X][ ][X][ ][ ][ ][X]\n"
        << "   [ ][ ][ ][X][ ][ ][ ]\n"
        << "   [ ][ ][ ][ ][X][ ][ ]\n"
        << "�����: ���������� ����� ������������, ������ 4354, ������ ���������: 5.1.24\n"
        << "���� ������ : 27.11.24  ���������� : 06.12.24\n";
    if (n0 < 0)
    {
        fout << "�� �������� ������ N > 0\n";
        a = -1;
    }
    else if (n0 == 0)
    {
        fout << "�� �������� ������ N > 0\n";
        a = -1;
    }
    else if (!(n0 % 2))
    {
        fout << "�� ������� ������ N ������ ���� ��������\n";
        a = -1;
    }
    else if (m0 == 0)
    {
        fout << "�� �������� ������ m > 0\n";
        a = -1;
    }
    else if (m0 < 0)
    {
        fout << "�� �������� ������ m > 0\n";
        a = -1;
    }
    else
    {
        fout << "N = " << n << "\n";
        fout << "m = " << m << "\n";
        fout << "�������, ��������� ����������:\n";
        for (short i = 0; i < n; i++)
            OutString(fout, n, i, Arr);
    }
    return a;
}

void OutResult(fstream& fout, float max)
{
    fout << "\n���������� ������� �������������� ������� = " << max << "\n";
}

void Process(short& n, short& m, float& max, float** Arr)
{
    float* B = new float[n * n];
    int k = 0;
    short i = m - 1, j = (n - 1) / 2;

    while (i >= 0 && j >= 0 && j < n && i < n)
    {
        *(B + k) = *(*(Arr + i) + j);
        k++, i--, j++;
    }
    i = m - 1, j = (n - 1) / 2;
    while (i >= 0 && j >= 0 && j < n && i < n)
    {
        *(B + k) = *(*(Arr + i) + j);
        k++, i++, j--;
    }
    i = m - 1, j = (n - 1) / 2;
    while (i >= 0 && j >= 0 && j < n && i < n)
    {
        *(B + k) = *(*(Arr + i) + j);
        k++, i++, j++;
    }
    j = m - 1, i = (n - 1) / 2;
    while (i >= 0 && j >= 0 && j < n && i < n)
    {
        *(B + k) = *(*(Arr + i) + j);
        k++, i++, j++;
    }

    float maxfromarea = *B;

    for (int p = 0; p <= k; p++)
    {
        if (*(B + p) > maxfromarea)
            maxfromarea = *(B + p);
    }
    max = maxfromarea;
    delete[] B;
}
