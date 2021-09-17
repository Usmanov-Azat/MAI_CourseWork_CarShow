#include<iostream>
#include <cstdlib>
#include<fstream>
#include<string>
#include<Windows.h>

using namespace std;
/****************************************************************************************************

											С Т Р У К Т У Р Ы

*****************************************************************************************************/


//Структура для описания клиента
struct Client {
	int nomer;
	string  imya, familiya, otchestvo;

};
//Структура для описания авто
struct Avto {
	string marka, model, realisation, dop;
};
//Совмещенная структура
struct Data {
	Client _client;
	Avto _avto;
};
/*******************************************************************************************************

						  П Р О Т О Т И П Ы    Ф У Н К Ц И Й

***********************************************************************************************************/


void ReadFile(Data* (&d), int& n);//Прототип функции чтения базы из файла
void print(Data* (&d), int n);//Прототип функции вывода базы на экран
void menu(char& m);//Прототип функции вызова меню
void New(Data* (&d), int n);//Прототип функции добавления клиента
void Delete(Data* (&d), int& n, int number);//Прототип функции удаления клиента
void save(Data* (&d), int n);//Прототип функции применения изменений
int diag();//Прототип функциии проверяющей файл на корректность



/****************************************************************************************************************

							  О С Н О В Н А Я   Ф У Н К Ц И Я

*******************************************************************************************************************/



int main() {
	int error = 0;//ошибки
	int n = 0;//количество клиентов
	SetConsoleCP(1251);//подключение русского языка
	SetConsoleOutputCP(1251);//подключение русского языка
	setlocale(LC_ALL, "Russian");//подключение русского языка
	Data* d = new Data[256];//Создание массива структур
	error = diag();//Проверка файла на корректность

				   //Если файл не найден
	if (error == 1) {
		cout << "Ошибка!База данных клиентов не найдена!\n\n";
		return 1;
	}

	ReadFile(d, n);//Читаем данные из файла
	char m;//Выбор в меню
	int number_delete;//Номер клиента для удаления
	menu(m);//Вызов меню

	//Пока не выбрали 0
	while (m != 0) {

		switch (m) {

			//Выводим базу данных на печать
		case '1':
			system("cls");

			print(d, n);
			cout << endl;

			menu(m);
			system("cls");
			break;

			//Добавляем клиента
		case '2':

			n++;

			New(d, n);

			cout << "Клиент успешно добавлен!\n\n";
			menu(m);
			system("cls");
			break;

			//Удаляем клиента
		case '3':
			system("cls");
			cout << "Введите номер клиента, которого хотите удалить:\n\n";
			cin >> number_delete;
			system("cls");
			if (number_delete > n) {
				cout << "Ошибка!Клиента с данным номером не существует\n\n";

			}

			system("cls");
			Delete(d, n, number_delete);
			cout << "Клиент успешно удален!\n\n";
			menu(m);

			break;

			//Сохраняем изменения
		case '4':
			save(d, n);
			system("cls");
			cout << "Изменения успешно сохранены!\n\n";
			menu(m);

			break;
			//Выход из программы
		case '0':
			system("cls");

			return 0;

			break;
		default:
			system("cls");
			menu(m);
		}
	}
	system("cls");
	return 0;

}
/*************************************************************************************************************

		   Р Е А Л И З А Ц И Я    Ф У Н К Ц И Й

***************************************************************************************************************/


//Функция чтениея из файла
void ReadFile(Data* (&d), int& n)
{
	ifstream fin("data.txt");

	//файл существует, можно из него читать
	fin >> n;

	for (int i = 1; i < n + 1; i++) {
		fin >> d[i]._client.nomer;//Считывание номера клиента
		fin >> d[i]._client.familiya;//Считывание фамилии клиента
		fin >> d[i]._client.imya;//Считывание имени клиента
		fin >> d[i]._client.otchestvo;//Считывание отчества клиента
		fin >> d[i]._avto.marka;//Считывание марка автомобился
		fin >> d[i]._avto.model;//Считывание модели автомобиля 
		fin >> d[i]._avto.realisation;//Считывание реализация
		fin >> d[i]._avto.dop;//Считывание дополнительного оборудования

	}

	fin.close();

}

//Фнкция вывода данных о клиенте
void print(Data* (&d), int n) {
	for (int i = 1; i < n + 1; i++) {
		cout << "№ Клиента: " << d[i]._client.nomer << endl;
		cout << "Фамилия клиента: " << d[i]._client.familiya << endl;
		cout << "Имя клиента: " << d[i]._client.imya << endl;

		cout << "Отчество клиента: " << d[i]._client.otchestvo << endl;
		cout << "Марка автомобиля: " << d[i]._avto.marka << endl;
		cout << "Модель автомобиля: " << d[i]._avto.model << endl;
		cout << "Реализован ли автомобиль: " << d[i]._avto.realisation << endl;
		cout << "Имеются ли дополнительные оборудования: " << d[i]._avto.dop << endl;
		cout << endl;
	}
}
//Функция вывода меню
void menu(char& m) {
	cout << "Выберите действие:\n" << "(1)Вывести базу клиентов\n" << "(2)Добавить нового клиента\n" << "(3)Удалить клиента\n" << "(4)Сохранить изменения\n" << "(0)Закрыть меню\n\nДействие: ";
	cin >> m;
}
//Функция добавленмя клиента
void New(Data* (&d), int n) {


	d[n]._client.nomer = n;
	system("cls");
	cout << "\nВведите фамилию клиента:\n\n";

	cin >> d[n]._client.familiya;
	system("cls");
	cout << "\nВведите имя клиента:\n\n";

	cin >> d[n]._client.imya;
	system("cls");

	cout << "\nВведите отчество клиента:\n\n";

	cin >> d[n]._client.otchestvo;
	system("cls");
	cout << "\nВведите марку автомобиля:\n\n";
	cin >> d[n]._avto.marka;
	system("cls");
	cout << "\nВведите модель автомобиля:\n\n";
	cin >> d[n]._avto.model;
	system("cls");
	cout << "\nРеализован ли автомобиль?(Да/нет):\n\n";
	cin >> d[n]._avto.realisation;
	system("cls");
	cout << "\nИмеются ли дополнительные оборудования в автомобиле?(Да/нет):\n\n";
	cin >> d[n]._avto.dop;
	system("cls");


}

//Функция удаления пользователя
void Delete(Data* (&d), int& n, int number) {
	for (int i = number; i < n; i++) {
		//i = i + 1;
		//d[i]._client.nomer = d[i + 1]._client.nomer;
		d[i]._client.familiya = d[i + 1]._client.familiya;
		d[i]._client.imya = d[i + 1]._client.imya;
		d[i]._client.otchestvo = d[i + 1]._client.otchestvo;
		d[i]._avto.marka = d[i + 1]._avto.marka;
		d[i]._avto.model = d[i + 1]._avto.model;
		d[i]._avto.realisation = d[i + 1]._avto.realisation;
		d[i]._avto.dop = d[i + 1]._avto.dop;
	}
	n--;


}

//Функция сохранения текущих данных
void save(Data* (&d), int n) {

	ofstream fout("data.txt");
	//remove("test.txt");
	fout << n << endl;
	for (int i = 1; i < n + 1; i++) {

		fout << d[i]._client.nomer << endl;
		fout << d[i]._client.familiya << endl;
		fout << d[i]._client.imya << endl;

		fout << d[i]._client.otchestvo << endl;
		fout << d[i]._avto.marka << endl;
		fout << d[i]._avto.model << endl;
		fout << d[i]._avto.realisation << endl;
		fout << d[i]._avto.dop << endl;
		fout << endl;
	}
}
//Функция проверки файла на корректность
int diag() {
	ifstream fin("data.txt");
	if (!fin)
	{
		return 1;
		fin.close();      //закрыть файл

		return 1;         //выход по ошибке
	} // end if
	else if (fin.eof()) 	//файл пуст
	{
		fin.close();    //закрыть файл

		return 2;   //выход по ошибке


	}
	else {
		return 0;

	}
}




