#include <fstream>
#include <string.h>
ifstream input("D:\\map.txt"); //Считываемый файл
int i, j; //Счетчики
int lenstr; //Тут хранится длина строки
int stroki = 0; //Здесь находится количество строк рисунке
int stolbci = 0; //Здесь находится количество столбцов рисунке
string inputstr; //Вспомогательная переменная для считывания из файла
char* str = new char[1024]; //Вспомогательная переменная для измерения колличества строк

//Проверка на существование файла
if (!input)
{
	cout << "\nNo input file" << endl;
	return 1;
}

//Првоерка на пустой файл
if (input.peek() == EOF)
{
	cout << "\nFile is empty" << endl;
	return 2;
}

//Находим максимальную длину строки и колличество строк, которые будут использоватся для задания массива
while (!input.eof())
{
	input.getline(str, 1024, '\n'); //Считываем строку из файла

	//Узнаем длину строки
	lenstr = 0;
	while ((str[lenstr] != '\n') and (str[lenstr] != '\0'))
	{
		lenstr++;
	}

	if (lenstr > stolbci) //Если текущая длина строки больше колличества столбцов
	{
		stolbci = lenstr; //Кол-ву столбцов присваиваем значение текущей длины строки
	}
	stroki++;//Увеличиваем количество строк в массиве на 1
}
input.close();

//Переоткрываем файл, чтобы начать считывать файл сначала
ifstream input2("D:\\map.txt");

//Создаем двумерный массив
char** arr = new char* [stroki];
for (i = 0; i < stroki; i++)
	arr[i] = new char[stolbci + 1];

//Чтение рисунка в массив из файла
i = 0;
while (!input2.eof())
{
	getline(input2, inputstr); //Читаем строку файла
	j = 0;
	while ((inputstr[j] != '\n') && (inputstr[j] != '\0'))//Пока не встретим \n или \0
	{
		arr[i][j] = inputstr[j]; //Записываем сисвол в массив
		j++;
	}
	if (j < stolbci) //Как только наткунулись на \n или \0 заполняем оставшиеся ячейки в строке на ' '
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