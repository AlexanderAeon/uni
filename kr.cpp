/*
Программа представляет собой простую базу данных,
созданную в рамках курсовой работы во время учебы в университете.

Программа работает с данными вида:
название области, процент безработицы за каждый из 5 лет.

Реализовано меню, запись и генерация элементов, редактирование элементов,
а также запись данных в бинарный и текстовые файлы.

Согласно требованиям к КР, программа реализована в виде одного файла.
*/
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <io.h>
#include <vector>

using namespace std;

struct region
{
	char name[15];
	double p[5];
	double change;
	int min_y;
};

int ArrayIndexOfMin(const  double* arr, int N) {
	int elem_i = 0;

	for (int i = 1; i < N; i++) {

		if (arr[elem_i] > arr[i]) elem_i = i;
	}

	return elem_i;
}

class PrClass
{
private:
	region* A;
	vector<region> v;
	long int N;
	char FNT[15] = "data.txt";
	char FNB[15] = "data.bin";
public:
	~PrClass() {delete[] A;};

	void Input(region&);
	void InputRand(region&);
	void Output(region, int, FILE*);

	void Table(int);
	void Sort_Pole(int p, int pr);
	void SORT();

	void ObrStruct(region&);
	void Udalenie();
	void Vkl();
	void Redakt();
	void Menu();

	void SaveData();
	void WriteBin(FILE*);

	void Start();
	void ReadBin(char*);
	void ReadText(char*);

	void PartB();
};

void PrClass::ObrStruct(region& A) {
	A.min_y = ArrayIndexOfMin(A.p, 5) + 1;
	A.change = A.p[4] / A.p[0];
}

void PrClass::Input(region& x)
{
	cout << "Введите название области" << endl;
	cin >> x.name;
	cout << "Введите процент безработицы за пять лет" << endl;
	for (int i = 0; i < 5; i++) {
		cin >> x.p[i];
	}
}

void PrClass::InputRand(region& x) {
	const char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
	int L = 26, i;
	for (i = 0; i < rand() % 8 + 2; i++) {
		int ind = rand() % L;
		x.name[i] = alphabet[ind];
	}
	x.name[i] = '\0';
	for (int i = 0; i < 5; i++)	x.p[i] = 0.01 + ((rand() % 10000) - 1) / 100.0;
}

void PrClass::Output(region A, int P = 0, FILE* ft = stdout) {
	if (P == 0) {
		fprintf(ft, "Q - коэффициент изменения безработицы\n");
		fprintf(ft, "Y - год с минимальным процентом безработицы");
		fprintf(ft, "\n-------------------------------------------------------------------------------------");
		fprintf(ft, "\nНазвание области   |   1г.   |   2г.   |   3г.   |   4г.   |   5г.   |   Q   |   Y   ");
		fprintf(ft, "\n-------------------------------------------------------------------------------------");
	}
	fprintf(ft, "\n %4d %12s ", P + 1, A.name);
	for (int i = 0; i < 5; i++) {
		fprintf(ft, "|  %5.2f  ", A.p[i]);
	}
	fprintf(ft, "|%5.2f  |   %d", A.change, A.min_y);
	fprintf(ft, "\n-------------------------------------------------------------------------------------");
}


void PrClass::Table(int p = 0) {
	system("cls");
	if (p == 1) {
		printf("-------------------------------------------------------------------------------------\n");
		printf("         1         |    2    |    3    |    4    |    5    |    6    |   7   |   8");
		printf("\n-------------------------------------------------------------------------------------");
	}
	for (int i = 0; i < N; i++) {
		Output(A[i], i);
	}
}

void PrClass::Sort_Pole(int p, int pr) // p - номер поля, pr - признак сортировки (1 - возрастание, 0 - убывание)
{
	region x; // вспомогательная переменная для перестановки элементов в массиве
	int f; // признак перестановки, при f = 1  - записи переставляются, иначе нет
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			f = 0;
			switch (p) {
			case 1:
				f = strcmp(A[i].name, A[j].name) < 0;
				break;
			case 2:
				f = A[i].p[p - 2] < A[j].p[p - 2];
				break;

			case 3:
				f = A[i].p[p - 2] < A[j].p[p - 2];
				break;
			case 4:
				f = A[i].p[p - 2] < A[j].p[p - 2];
				break;
			case 5:
				f = A[i].p[p - 2] < A[j].p[p - 2];
				break;
			case 6:
				f = A[i].p[p - 2] < A[j].p[p - 2];
				break;

			case 7:
				f = A[i].change < A[j].change;
				break;

			case 8:
				f = A[i].min_y < A[j].min_y;
				break;
			}

			if (pr) f = !f;

			if (f) {
				x = A[i];
				A[i] = A[j];
				A[j] = x;
			}
		}
	}
}

void PrClass::SORT() {
	int p = 1, pr = 1;

	do {
		Table(1);

		cout << "\n Ввод номера поля для сортировки (1-8), 0 - выход: " << endl;
		cin >> p;
		if (p > 0 && p < 9) {
			cout << "\n По возрастанию (A-Z)? (1 - да, 0 - нет)" << endl;
			cin >> pr;
			Sort_Pole(p, pr);
		}
	} while (p);
}

void PrClass::Udalenie() {
	int nom;
	cout << "\n Ввод номера строки: ";
	cin >> nom;
	if (nom > 0 && nom <= N)
	{
		N--;
		for (int i = nom - 1; i < N; i++) A[i] = A[i + 1];

		A = (region*)realloc(A, N * sizeof(region));
		Table();
	}
	else {
		cout << "Введите корректный номер строки" << endl;
		system("pause");
		Table();
	}
}

void PrClass::Vkl() {
	N++;
	A = (region*)realloc(A, N * sizeof(region));
	Input(A[N - 1]);
	ObrStruct(A[N - 1]);
	Table();
}

void PrClass::Redakt() {
	int nom = 1, p = 1; // nom - строка, p - номер поля
	Table(1);
	cout << "\n Ввод номера строки: ";
	cin >> nom;
	if (nom > 0 && nom <= N) {
		do {
			cout << "\nВвод номера поля для редактирования(1-5), 0 - выход: ";
			cin >> p;
			switch (p) {
			case 1:
				cout << "Ввод названия ВУЗа ";
				cin >> A[nom - 1].name;
				break;
			case 2:
			case 3:
			case 4:
			case 5:
				cout << "Ввод платы за 1 год обучения на " << p - 1 << "-й специальности: " << endl;
				cin >> A[nom - 1].p[p - 2];
			}

			ObrStruct(A[nom - 1]);
			Table();
		} while (p);
	}
	else {
		cout << "Ввод корректного номера строки" << endl;
		system("pause");
		Table();
	}
}

void PrClass::Menu() {
	int k = 1;
	do {
		Table();
		cout << endl;
		cout << "работа с таблицей" << endl;
		cout << "1. удаление" << endl;
		cout << "2. включение" << endl;
		cout << "3. редактирование" << endl;
		cout << "4. сортировка" << endl;
		cout << "5. запись в файл" << endl;
		cout << "0. Выход и часть Б программы" << endl;

		cout << "Выберите действие: ";

		cin >> k;

		switch (k) {
		case 1:
			Udalenie();
			break;
		case 2:
			Vkl();
			break;
		case 3:
			Redakt();
			break;
		case 4:
			SORT();
			break;
		case 5:
			SaveData();
		default:
			continue;
		}
	} while (k);

}

void PrClass::SaveData() {
	FILE* ft;
	FILE* fb;
	//Добавленный участок
	cout << "Введите название бинарного файла:" << endl;
	cin >> FNB;
	cout << "Введите название текстового файла:" << endl;
	cin >> FNT;
	//
	fopen_s(&ft, FNT, "wt");
	for (int i = 0; i < N; i++) Output(A[i], i, ft);
	fclose(ft);
	fopen_s(&fb, FNB, "wb");
	WriteBin(fb);
	Table();
}

void PrClass::WriteBin(FILE* fb) {
	for (int i = 0; i < N; i++) fwrite(A + i, sizeof(region), 1, fb);
	fclose(fb);
}

bool IsExist = 1;
void PrClass::Start() {
	int choice = 1;
	//
	bool ask;
	//
	cout << "Выберите метод ввода данных" << endl;
	cout << "1. Ввести данные случайно" << endl;
	cout << "2. Ввести данные с клавиатуры" << endl;
	cout << "3. Импортировать данные из бинарного файла (*.bin)" << endl;
	cout << "4. Импортировать данные из текстового файла (*.txt)" << endl;
	cout << "Выберите действие: ";

	cin >> choice;

	switch (choice) {
	case 1:
		cout << "Ввод количества записей: " << endl;
		cin >> N;
		A = new region[N];
		for (int i = 0; i < N; i++) InputRand(A[i]);
		break;
	case 2:
		cout << "Ввод количества записей: " << endl;
		cin >> N;
		A = new region[N];
		system("cls");
		for (int i = 0; i < N; i++) Input(A[i]);
		break;
	case 3:
		cout << "Ваш файл существует? (1 - Да, 0 - нет)" << endl;
		cin >> ask;
		if (ask) {
			cout << "Ввод полного названия файла: ";
			cin >> FNB;
			ReadBin(FNB);
		}
		else {
			cout << "Файл не будет импортирован, потому что его не существует" << endl;
			cout << "Создайте файл" << endl;
			IsExist = 0;
		}
		break;
	case 4:
		cout << "Ваш файл существует? (1 - Да, 0 - нет)" << endl;
		cin >> ask;
		if (ask) {
			cout << "Ввод полного названия файла: ";
			cin >> FNT;
			ReadText(FNT);
		}
		else {
			cout << "Файл не будет импортирован, потому что его не существует" << endl;
			cout << "Создайте файл" << endl;
			IsExist = 0;
		}
	}

	for (int i = 0; i < N; i++) ObrStruct(A[i]);
}

long int FILE_SIZE(char* NF, int size = 1) {
	long int k, L;
	int d; // дескриптор
	FILE* f;
	fopen_s(&f, NF, "rb");
	if (f) {
		d = _fileno(f);
		L = _filelength(d);
		k = L / size; // количество записей в файле размером size
		fclose(f);
	}
	else cout << "Такого файла нет" << endl;
	return k;
}

void PrClass::ReadBin(char* NF) {
	long int k = FILE_SIZE(NF, sizeof(region)); // N
	N = k;
	FILE* fb;
	fopen_s(&fb, NF, "rb");
	A = (region*)realloc(A, N * sizeof(region));

	int i = 0;
	while (fread(A + i, sizeof(region), 1, fb)) i++; // A+i == &A[i]
	fclose(fb);
}


int Proverka(char c, char* R) {
	int f = 0, L = strlen(R);
	for (int i = 0; i < L; i++)
		if (c == R[i]) f = 1;
	return f;
}

int Slovo(char* str, int k) {
	char R[] = " !?;:*|_<>-"; // разделители слов строки
	int f = 0;
	char s2[100]; // вспомогательная переменная для текущего слова в строке
	int i = 0, nom = 0, j = 0; // вспомогательные переменные
	while (str[i]) {
		//если символ не разделитель
		if (Proverka(str[i], R) == 0) {
			s2[j] = str[i]; j++;
		}
		else if (j) {
			s2[j] = '\0';
			nom++;
			j = 0;
			if (nom == k) { f = 1; break; }
		}
		i++;
	}
	i = 0;
	while (s2[i]) str[i] = s2[i++];
	str[i] = '\0';
	return f;
}

region ReadRegion(char* st) {
	region Z;
	Z.p[0] = -1;
	char slovo[100];
	int k = 1;
	strcpy_s(slovo, st);
	while (Slovo(slovo, k)) {
		string IsWrongSlovo(slovo);
		if (IsWrongSlovo == "Название") return Z;
		switch (k) {
		case 2:
			strcpy_s(Z.name, slovo);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			Z.p[k - 3] = atoi(slovo); // преобразование строки slovo в int
		}
		strcpy_s(slovo, st);
		k++;
	}
	return Z;
}

void PrClass::ReadText(char* NT) {
	long int k = FILE_SIZE(FNT);
	char s[100];
	int i = 0;
	FILE* ft;
	fopen_s(&ft, FNT, "rt");
	while (fgets(s, 100, ft)) {
		region Z = ReadRegion(s); //заполнение полей записи данными из строки
		if (Z.p[0] > 0) {
			N = i + 1;
			A = (region*)realloc(A, N * sizeof(region));

			ObrStruct(Z);
			A[N - 1] = Z;
			i++;
		}
	}
	fclose(ft);
}

void PrClass::PartB() {
	for (int i = 0; i < N; i++) { if ((A[i].p[0] > A[i].p[1]) && (A[i].p[1] > A[i].p[2]) && (A[i].p[2] > A[i].p[3]) && (A[i].p[3] > A[i].p[4])) v.push_back(A[i]); }
	cout << "\n\nСписок областей, в которых процент безработицы в течении 5-ти лет постоянно уменьшался:" << endl;
	for (int i = 0; i < v.size(); i++) { Output(v[i], i); }

	region Max;
	Max.change = 0;
	for (int i = 0; i < N; i++) { if (A[i].change > Max.change) Max = A[i]; }
	cout << "\nОбласть, в котором процент безработицы увеличился в максимальное количество раз: " << endl;
	Output(Max);
	cout << endl;
}


int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	PrClass P;
	P.Start();
	if (IsExist) {
		P.Menu();
		P.PartB();
	}
	system("pause");
	return 0;
}
