#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<iomanip>

using namespace std;

void random (int W[20][20], int n);

char bufRus [256];
int n;
char *Rus (const char* text)
{
    CharToOemA(text, bufRus);
	return bufRus;
}

int main()
{
    int W[20][20]; // матрица весов
    int u1, u2;    // u1 - начальная вершина, u2 - конечная вершина  
    int length = 0;    // длина пути 
    int weight;    // вес пути
    int P[20];     
    const int GM = 842150451;    // используется в качестве обозначения максимально возможного числа.
    int m[20];     // метка вершин
    int t;         // текущая вершина
    int d[20];     // всем вершинам преписывается вес.
    int min;       // минимальное значение
    int k, c;      // переменные для временного хранения данных
    int Path[20];  // последовательность номеров вершин определяющая путь
    int choise = 1;
    
	srand(time(NULL));
    // текстовые сообщения выводимые на экран
	while (true)
	{
		cout << Rus("Введите колличество вершин в графе от 2 до 20: ");
		cin >> n;
		cout << endl;
		if (n >= 2 && n <= 20)
		{
			break;
		}
		if (n > 20) // если вершин больше 20
		{
			cout<<Rus("Количество вершин должно быть <= 20\n");
		}
		if (n < 2) // если меньше 2, то смысла нету
		{
			cout<<Rus("Количество вершин должно быть >= 2\n");
		}
	}
	random(W, n);

    //заменяем элементы главной диагонали нулями
    cout << setw(40) << Rus("МАТРИЦА ДЛИН ДУГ ГРАФА\n\n");
    for (int i = 1; i <= n; i++)
	{
        for(int j = 1; j <= n; j++)
        {
            if (W[i][j] < 0)
			{
                W[i][j] = GM;
			}
            if (i == j)
			{
                W[i][j] = 0;
			}
            W[i][j] = W[j][i];
        }
	}

    // оформление и вывод матрицы весов

    //вывод номеров вершин
    for (int i = 1; i <= n; i++)
	{
        cout << setw(4) << "V" << i;
	}
    cout << endl;

    // вывод вертикальной верхний черты
    for (int i = 1; i <= n*3-2; i++)
	{
        cout << setw(2) << "-";
	}
    cout << endl;
        
    // вывод массива
    for (int i = 1; i <= n; i++)
	{ 
		for (int j = 1; j <= n; j++)
		{
			cout << setw(4) << W[i][j] << "|";
		}
		cout << setw(3) << "V" << i << endl;
    }
    for(int i = 1; i <= n*3-2; i++)
	{
        cout << setw(2) << "-";
	}

    // ввод начальной и конечной вершины в графе
	cout << Rus("\nНомер начальной вершины пути <от 1 до ") << n << "> ";
    cin >> u1;
    cout << endl;

    cout << Rus("Введите номер конечной вершины пути <от 1 до ") << n << "> ";
    cin >> u2;
    cout << endl;

    if (u1 == u2)
    {
        cout << Rus("Путь найден\nДлина пути 0\nВес пути 0\nПоследовательность номеров вершин 0\n");
    }

    // реализация алгоритма Дейкстры
    if (u1 != u2)
    {
        for (int i = 1; i <= n; i++)
        {
            d[i] = GM;
            P[i] = 0;
            m[i] = 0;
        }
        d[u1] = 0;
        t = u1;
        while (length == 0)
        {
            for (int i = 1; i <= n; i++)
            {
                if(W[t][i] < GM)
                {
                    c = d[t] + W[t][i];
                    if (d[i] > c)
                    {
                        d[i] = c;
                        P[i] = t;
                    }
                }
            }
            min = GM;
            k = 0;
            for (int i = 1; i <= n; i++)
            {
                if (m[i] == 0)
				{
                    if (d[i] < min)
                    {
                        min = d[i];
                        k = i;
                    }
				}
            }
            if (k != 0)
            {
                m[k] = 1;
                t = k;
                if (t == u2)
				{
					length = 1;
				}
            }
            else
			{
				length = -1;
			}
        }
        if (length == 1)
        {
            Path[1] = u2;
            length = 2;
            for (int j = u2; j != u1; length++)
            {
                Path[length] = P[j];
                j = P[j];
            }
            k = length/2;
            for (int i = 1; i <= k; i++)
            {
                t = Path[i];
                Path[i] = Path[length-i];
                Path[length-i] = t;
            }
            length--;
        }
        weight = d[u2];

    // Проверка  и вывод полученных результатов
    if (length == -1)
	{
        cout << Rus("Путь не найден") << endl;
	}
    else 
    {
        cout << Rus("Путь найден") << endl;
        cout << Rus("Колличество соединенных путей ") << length << endl;
        cout << Rus("Длина пути " ) << weight << endl;
        cout << Rus("Последовательность номеров вершин " );
        for (int j = 1; j <= length; j++)
		{
			cout << setw(3) << "V" << Path[j];
		}
		cout << endl;
    }
	}
    cout << endl;
	return 0;
}

void random (int W[20][20], int n)
{
    for (int i = 1; i <= n; i++)
	{
        for (int j = 1; j <= n; j++)
		{
            W[i][j] = 1 + rand() % 20;
		}
	}     
}