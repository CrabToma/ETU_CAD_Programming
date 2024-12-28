/*
  Задание: Даны N точек на плоскости. Наайти среди них точки, являющиеся вершинами фигуры,
  содержащей максимальное число заданных точек
  Автор: Фанасюткин Роман Владимирович  Группа: 4354 Версия программы: K.1.24
  Дата начала: 12.12.24  Завершения: 23.12.24
*/
#include <iostream>
#include <fstream>
#include <locale>

using namespace std;

const unsigned n = 100;
const float epsilon = 1e-6;

double PX[10000][5], PY[10000][5];
int FiguresCount = 0;

double PointsInFigure[10000];

void ScanInputFile(fstream& f, fstream& g, fstream& h, float A[][2], int& size);
bool AreEqual(float a, float b);
//bool AreParalel(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
float Distance(float x1, float y1, float x2, float y2);
//void FindFigure(fstream& f, fstream& g, fstream& h, float A[][2], float& size);

void ScanInputFile(fstream& f, fstream& g, fstream& h, float A[][2], int& size)
{
    float tmp = 0;
    char sym;
    unsigned i = 0, j = 0, inpnum = 0;

    f << skipws;
    f >> size;
    if (f.eof())
    {
        g << "Файл in.txt пуст";
    }
    else
    {
        h << "Количество элементов считанное программой: " << size << "\n";
        if (size < 0)
        {
            size = 0;
            g << "Были сделаны корректировки, size = 0\n";
            h << "Были сделаны корректировки, size = 0\n";
        }
        if (size > n)
        {
            size = n;
            g << "Были сделаны корректировки, size = n\n";
            h << "Были сделаны корректировки, size = n\n";
        }
        f >> noskipws;

        int countInLine = 0;

        for (i = 0; i < size && !f.eof();)
        {
            inpnum++;
            countInLine = 0;
            for (j = 0; j < 2 && !f.eof();)
            {
                f >> sym;
                if (sym == ' ' || sym == '\size')
                {
                    continue;
                }
                else if (sym == '\n')
                {
                    break;
                }
                else
                {
                    f.seekg(-1, ios::cur);
                    if (f >> tmp)
                    {
                        A[i][j] = tmp;
                        //h << "A[" << i << "][" << j << "] = " << tmp << "\n";
                        j++;
                        countInLine++;
                    }
                    else
                    {
                        f.clear();
                        break;
                    }
                }
            }

            if (countInLine == 0)
            {
                h << inpnum << " строка: Отсутствует x и y\n";
            }
            else if (countInLine == 1)
            {
                h << inpnum << " строка: Отсутствует y\n";
            }
            else
            {
                h << inpnum << " строка: Считанна точка (" << A[i][0] << ", " << A[i][1] << ")\n";
                i++;
            }

            while (sym != '\n' && !f.eof())
            {
                f >> sym;
            }
        }
        size = i;
        f.close();

        g << "Количество элементов: " << size << "\nA = {";
        h << "Количество элементов: " << size << "\nA = {";

        for (unsigned int k = 0; k < size; k++)
        {
            g << "(" << A[k][0] << ", " << A[k][1] << ")";
            h << "(" << A[k][0] << ", " << A[k][1] << ")";
            if (k != size - 1)
            {
                g << ", ";
                h << ", ";
            }
        }
        g << "}\n";
        h << "}\n";
    }
}

bool AreEqual(float a, float b)
{
    return fabs(a - b) < epsilon;
}

bool AreParalel(fstream & h, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
{

    h << "\n2-1 & 5-4: " << (y2 - y1) / (x2 - x1) << " " << (y5 - y4) / (x5 - x4);
    h << "\n3-1 & 5-3: " << (y3 - y1) / (x3 - x1) << " " << (y5 - y3) / (x5 - x3);
    h << "\n3-2 & 4-3: " << (y3 - y2) / (x3 - x2) << " " << (y4 - y3) / (x4 - x3)<< '\n';

    return (((y2-y1)/(x2-x1) ==  (y5 - y4) / (x5 - x4)) &&
        ((y3 - y1) / (x3 - x1) ==  (y5 - y3) / (x5 - x3)) &&
        ((y3 - y2) / (x3 - x2), (y4 - y3) / (x4 - x3)));
}

float Distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool AreEqualTriangles(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
{
    float a1 = Distance(x1, y1, x3, y3);
    float d1 = Distance(x3, y3, x4, y4);

    float a2 = Distance(x5, y5, x3, y3);
    float d2 = Distance(x3, y3, x2, y2);

    float a3 = Distance(x1, y1, x2, y2);
    float d3 = Distance(x4, y4, x5, y5);
    
    return ((AreEqual(a1, d1) && AreEqual(a2, d2) && AreEqual(a3, d3)));
}
bool IsFigureUnique(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
{
    float currentX[5] = { x1, x2, x3, x4, x5 };
    float currentY[5] = { y1, y2, y3, y4, y5 };

    for (int a = 0; a < FiguresCount; a++)
    {
        bool allPointsMatch = true;

        for (int i = 0; i < 5; i++)
        {
            bool pointMatch = false;
            for (int j = 0; j < 5; j++)
            {
                if (PX[a][j] == currentX[i] && PY[a][j] == currentY[i])
                {
                    pointMatch = true;
                    break;
                }
            }
            if (!pointMatch)
            {
                allPointsMatch = false; 
                break;
            }   
        }

        if (allPointsMatch)
            return false; 
    }

    return true;
}

void FindFigure(fstream& f, fstream& g, fstream& h, float A[][2], int& size)
{
    float x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (j == i)
                continue;

            for (int d = 0; d < size; d++)
            {
                if (d == i || d == j)
                    continue;

                for (int p = 0; p < size; p++)
                {
                    if (p == i || p == j || p == d)
                        continue;

                    for (int k = 0; k < size; k++)
                    {
                        if (k == i || k == j || k == d || k == p)
                            continue;

                        x1 = A[i][0], y1 = A[i][1];
                        x2 = A[j][0], y2 = A[j][1];
                        x3 = A[d][0], y3 = A[d][1];
                        x4 = A[p][0], y4 = A[p][1];
                        x5 = A[k][0], y5 = A[k][1];

                        if (AreEqualTriangles(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5)
                            && AreParalel(h, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5)
                            && IsFigureUnique(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5))
                        {
                            h << "!!! Считаны фигуры: ";
                            g << "\nСчитаны фигуры: ";

                            // первая фигура
                            PX[FiguresCount][0] = x1;
                            PX[FiguresCount][1] = x2;
                            PX[FiguresCount][2] = x3;
                            PX[FiguresCount][3] = x4;
                            PX[FiguresCount][4] = x5;

                            PY[FiguresCount][0] = y1;
                            PY[FiguresCount][1] = y2;
                            PY[FiguresCount][2] = y3;
                            PY[FiguresCount][3] = y4;
                            PY[FiguresCount][4] = y5;

                            FiguresCount++;

                            // вторая фигура
                            PX[FiguresCount][0] = x2;
                            PX[FiguresCount][1] = x5;
                            PX[FiguresCount][2] = x3;
                            PX[FiguresCount][3] = x1;
                            PX[FiguresCount][4] = x4;

                            PY[FiguresCount][0] = y2;
                            PY[FiguresCount][1] = y5;
                            PY[FiguresCount][2] = y3;
                            PY[FiguresCount][3] = y1;
                            PY[FiguresCount][4] = y4;

                            FiguresCount++;

                            g << "\nФигура №: " << FiguresCount - 1 << "\n";
                            for (int c = 0; c < 5; c++)
                            {
                                g << "(" << PX[FiguresCount - 2][c] <<
                                    ", " << PY[FiguresCount - 2][c] << "), ";
                            }
                            g << "\nФигура №: " << FiguresCount << "\n";
                            for (int c = 0; c < 5; c++)
                            {
                                g << "(" << PX[FiguresCount - 1][c] <<
                                    ", " << PY[FiguresCount - 1][c] << "), ";
                            }

                        }
                        else if (AreEqualTriangles(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5) && IsFigureUnique(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5))
                        {
                            h << "Фигуры - 2 треугольника равны, но оснавания не паралельны,:";
                        }
                        else if (AreEqualTriangles(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5))
                        {
                            h << "Фигуры - 2 треугольника равны, но оснавания не паралельны, И фигура не уникальна:";
                        }
                        else if (AreParalel(h,x1, y1, x2, y2, x3, y3, x4, y4, x5, y5)&& IsFigureUnique(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5))
                        {
                            h << "Фигуры - 2 не равных треугольника, но оснавания паралельны:";
                        }
                        else if (AreParalel(h, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5))
                        {
                            h << "Фигуры - 2 не равных треугольника, но оснавания паралельны:, И фигура не уникальна";
                        }
                        else
                        {
                            h << "Фигуры - 2 не равных треугольника, оснавания не паралельны:";
                        }
                        h << "\n(" << x1 << ", " << y1 << "), "
                            << "(" << x2 << ", " << y2 << "), "
                            << "(" << x3 << ", " << y3 << "), "
                            << "(" << x5 << ", " << y5 << "), "
                            << "(" << x4 << ", " << y4 << ")\n";
                        h << "(" << x2 << ", " << y2 << "), "
                            << "(" << x5 << ", " << y5 << "), "
                            << "(" << x3 << ", " << y3 << "), "
                            << "(" << x1 << ", " << y1 << "), "
                            << "(" << x4 << ", " << y4 << ")\n";
                    }
                }
            }
        }
    }
}

bool IsPointInPolygon(float px, float py, float poly[][2], int n)
{
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++)
    {
        float xi = poly[i][0], yi = poly[i][1];
        float xj = poly[j][0], yj = poly[j][1];

        if ((yi > py) != (yj > py) &&
            (px < (xj - xi) * (py - yi) / (yj - yi) + xi))
        {
            inside = !inside;
        }
    }
    return inside;
}
void IsPointInFigure(float A[][2], int size, fstream& g, fstream& h)
{
    for (int j = 0; j < FiguresCount; j++)
    {
        g << "\n";
        h << "\n";
        PointsInFigure[j] = 0;

        float polygon[5][2] =
        {
            {PX[j][0], PY[j][0]},
            {PX[j][1], PY[j][1]},
            {PX[j][2], PY[j][2]},
            {PX[j][3], PY[j][3]},
            {PX[j][4], PY[j][4]}
        };

        bool isVertex[5] = { false, false, false, false, false };

        for (int i = 0; i < 5; i++)
        {
            for (int k = 0; k < size; k++)
            {
                if (AreEqual(A[k][0], polygon[i][0]) && AreEqual(A[k][1], polygon[i][1]))
                {
                    isVertex[i] = true;
                    break;
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            float xp = A[i][0], yp = A[i][1];

            bool inside = IsPointInPolygon(xp, yp, polygon, 5);

            bool isPointVertex = false;
            for (int v = 0; v < 5; v++)
            {
                if (AreEqual(xp, polygon[v][0]) && AreEqual(yp, polygon[v][1]))
                {
                    isPointVertex = true;
                    break;
                }
            }

            if (inside && !isPointVertex)
            {
                g << xp << " " << yp << "\n";
                h << xp << " " << yp << "\n";
                PointsInFigure[j]++;
            }

            if (isPointVertex)
            {
                g << "Вершина: " << xp << " " << yp << "\n";
                h << "Вершина: " << xp << " " << yp << "\n";
            }
        }

        g << "\nКоличество точек в фигуре №: " << j + 1 << " = " << PointsInFigure[j];
        h << "\nКоличество точек в фигуре №: " << j + 1 << " = " << PointsInFigure[j];
    }
}
void FindMaxFigure(fstream& g, fstream& h)
{
    int MaxCountOfPoints = 0;
    float FiguresWithMaxCountofPoints[100];
    int k = 0;

    for (int j = 0; j <= FiguresCount; j++)
    {
        if (PointsInFigure[j] >= MaxCountOfPoints)
        {
            MaxCountOfPoints = PointsInFigure[j];
        }
    }
    for (int j = 0; j <= FiguresCount; j++)
    {
        if (PointsInFigure[j] == MaxCountOfPoints)
        {
            FiguresWithMaxCountofPoints[k] = j;
            k++;
        }
    }

    g << "\nФигуры с наибольшим количеством точек( " << MaxCountOfPoints << " ) лежащих внутри них:";
    h << "\nФигуры с наибольшим количеством точек лежащих внутри них:";
    for (int i = 0; i < k; i++)
    {
        h << "\nФигура №" << FiguresWithMaxCountofPoints[i] + 1;
        g << "\nФигура №" << FiguresWithMaxCountofPoints[i] + 1;
    }
}

void main()
{
    setlocale(LC_ALL, "russian");

    //float** figures = new float* [n];
    float A[n][2];
    int size;
    fstream f, g, h;

    g.open("results.txt", ios::out);
    if (!g.is_open())
        cout << "Не удолось открыть выходной файл results.txt";
    else
    {
        h.open("protocol.txt", ios::out);
        if (!h.is_open())
            cout << "Не удолось открыть выходной файл protocol.txt";
        else
        {
            f.open("in.txt", ios::in);
            if (!f.is_open())
                cout << "Не удолось открыть входной файл in.txt";
            else
            {
                ScanInputFile(f, g, h, A, size);
                FindFigure(f, g, h, A, size);
                IsPointInFigure(A, size, g, h);
                FindMaxFigure(g, h);
            }
        }
        g.close();
    }
}