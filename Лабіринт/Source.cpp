#include <fstream>
#include <string.h>
ifstream input("D:\\map.txt"); //����������� ����
int i, j; //��������
int lenstr; //��� �������� ����� ������
int stroki = 0; //����� ��������� ���������� ����� �������
int stolbci = 0; //����� ��������� ���������� �������� �������
string inputstr; //��������������� ���������� ��� ���������� �� �����
char* str = new char[1024]; //��������������� ���������� ��� ��������� ����������� �����

//�������� �� ������������� �����
if (!input)
{
	cout << "\nNo input file" << endl;
	return 1;
}

//�������� �� ������ ����
if (input.peek() == EOF)
{
	cout << "\nFile is empty" << endl;
	return 2;
}

//������� ������������ ����� ������ � ����������� �����, ������� ����� ������������� ��� ������� �������
while (!input.eof())
{
	input.getline(str, 1024, '\n'); //��������� ������ �� �����

	//������ ����� ������
	lenstr = 0;
	while ((str[lenstr] != '\n') and (str[lenstr] != '\0'))
	{
		lenstr++;
	}

	if (lenstr > stolbci) //���� ������� ����� ������ ������ ����������� ��������
	{
		stolbci = lenstr; //���-�� �������� ����������� �������� ������� ����� ������
	}
	stroki++;//����������� ���������� ����� � ������� �� 1
}
input.close();

//������������� ����, ����� ������ ��������� ���� �������
ifstream input2("D:\\map.txt");

//������� ��������� ������
char** arr = new char* [stroki];
for (i = 0; i < stroki; i++)
	arr[i] = new char[stolbci + 1];

//������ ������� � ������ �� �����
i = 0;
while (!input2.eof())
{
	getline(input2, inputstr); //������ ������ �����
	j = 0;
	while ((inputstr[j] != '\n') && (inputstr[j] != '\0'))//���� �� �������� \n ��� \0
	{
		arr[i][j] = inputstr[j]; //���������� ������ � ������
		j++;
	}
	if (j < stolbci) //��� ������ ����������� �� \n ��� \0 ��������� ���������� ������ � ������ �� ' '
	{
		while (j < stolbci)
		{
			arr[i][j] = ' ';
			j++;
		}
	}
	i++;
}
input2.close();