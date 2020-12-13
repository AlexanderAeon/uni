/*
Лаб. работа №1
Пример простой базы данных
Можно ввести название областей (регионов России) и процент безработицы за 5 лет
Программа выводит данные в виде таблицы в консоли
Помимо значений безработицы,
Программа также выводит коэффициент изменения безработицы и год с мин. значением безработицы
Для каждого элемента БД
*/
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

//Структура область
struct region
{
	char name[15];
	double p[5];
	int min_y;
	double change;
};


//Функция общего назначения
int ArrayIndexOfMin(const double* arr, int N) {
	int elem_i = 0;

	for (int i = 1; i < N; i++) {

		if (arr[elem_i] > arr[i]) elem_i = i;
	}

	return elem_i;
}


//Класс
class EC
{
private:
	region A;
	int N;
public:

	EC(int NN) : N{ NN } {};

	void Input(region& x);
	void InputRand(region& x);
	void Output(region X, int);
	void Sol();
};


//Методы
void EC::Output(region A, int P = 0) {
	if (P == 0) {
		cout << endl;
		printf("Q - коэффициент изменения безработицы\n");
		printf("Y - год с минимальным процентом безработицы");
		printf("\n-------------------------------------------------------------------------");
		printf("\nНазвание области |   1   |   2   |   3   |   4   |   5   |   Q   |   Y   ");
		printf("\n-------------------------------------------------------------------------");
	}
	printf("\n%16s ", A.name);
	for (int i = 0; i < 5; i++) {
		printf("|%5.2f  ", A.p[i]);
	}
	printf("|%5.2f  | %d ", A.change, A.min_y);
	printf("\n-------------------------------------------------------------------------");
}
void EC::Sol() {
	region B;
	B.change = -1;
	//Ввод данных с клавиатуры?
	cout << "Ввести данные случайно? (1 - Да, 0 - нет)" << endl;
	bool K = 1;
	cin >> K;

	double summa_sr = 0;

	for (int i = 0; i < N; i++) {
		if (!K)	Input(A);
		else InputRand(A);
		A.min_y = ArrayIndexOfMin(A.p, 5) + 1;
		A.change = A.p[4] / A.p[0];
		for (int j = 0; j < 5; j++) summa_sr += A.p[j];
		if (A.change > B.change) {
			B = A;
		};
		Output(A, K * i);
	}

	cout << endl << "Среднее арифметическое Q: " << summa_sr/(5*N) << endl;
	cout << "Максимальный Q: " << B.change << endl;

	cout << endl << "Запись с максимальным значением Q: " << endl;
	Output(B);
	cout << endl;
}

void EC::Input(region& x)
{
	cout << "Введите название области" << endl;
	cin >> x.name;
	cout << "Введите процент безработицы за пять лет" << endl;
	for (int i = 0; i < 5; i++) {
		cin >> x.p[i];
	}
}

void EC::InputRand(region& x) {
	const char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
	int L = 26, i;
	for (i = 0; i < rand() % 8 + 2; i++) {
		int ind = rand() % L;
		x.name[i] = alphabet[ind];
	}
	x.name[i] = '\0';
	for (int i = 0; i < 5; i++)	x.p[i] = 1 + rand() % 99;

}




//main
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int C;
	cout << "Введите количество записей" << endl;
	cin >> C;
	EC Example(C);
	Example.Sol();
	system("pause");
	return 0;
}
