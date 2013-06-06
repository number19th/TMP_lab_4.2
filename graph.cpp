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
    int W[20][20]; // ������� �����
    int u1, u2;    // u1 - ��������� �������, u2 - �������� �������  
    int length = 0;    // ����� ���� 
    int weight;    // ��� ����
    int P[20];     
    const int GM = 842150451;    // ������������ � �������� ����������� ����������� ���������� �����.
    int m[20];     // ����� ������
    int t;         // ������� �������
    int d[20];     // ���� �������� ������������� ���.
    int min;       // ����������� ��������
    int k, c;      // ���������� ��� ���������� �������� ������
    int Path[20];  // ������������������ ������� ������ ������������ ����
    int choise = 1;
    
	srand(time(NULL));
    // ��������� ��������� ��������� �� �����
	while (true)
	{
		cout << Rus("������� ����������� ������ � ����� �� 2 �� 20: ");
		cin >> n;
		cout << endl;
		if (n >= 2 && n <= 20)
		{
			break;
		}
		if (n > 20) // ���� ������ ������ 20
		{
			cout<<Rus("���������� ������ ������ ���� <= 20\n");
		}
		if (n < 2) // ���� ������ 2, �� ������ ����
		{
			cout<<Rus("���������� ������ ������ ���� >= 2\n");
		}
	}
	random(W, n);

    //�������� �������� ������� ��������� ������
    cout << setw(40) << Rus("������� ���� ��� �����\n\n");
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

    // ���������� � ����� ������� �����

    //����� ������� ������
    for (int i = 1; i <= n; i++)
	{
        cout << setw(4) << "V" << i;
	}
    cout << endl;

    // ����� ������������ ������� �����
    for (int i = 1; i <= n*3-2; i++)
	{
        cout << setw(2) << "-";
	}
    cout << endl;
        
    // ����� �������
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

    // ���� ��������� � �������� ������� � �����
	cout << Rus("\n����� ��������� ������� ���� <�� 1 �� ") << n << "> ";
    cin >> u1;
    cout << endl;

    cout << Rus("������� ����� �������� ������� ���� <�� 1 �� ") << n << "> ";
    cin >> u2;
    cout << endl;

    if (u1 == u2)
    {
        cout << Rus("���� ������\n����� ���� 0\n��� ���� 0\n������������������ ������� ������ 0\n");
    }

    // ���������� ��������� ��������
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

    // ��������  � ����� ���������� �����������
    if (length == -1)
	{
        cout << Rus("���� �� ������") << endl;
	}
    else 
    {
        cout << Rus("���� ������") << endl;
        cout << Rus("����������� ����������� ����� ") << length << endl;
        cout << Rus("����� ���� " ) << weight << endl;
        cout << Rus("������������������ ������� ������ " );
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