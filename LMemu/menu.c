#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include<malloc.h>
// управл¤ющие консолью библиотеки
#include <windows.h>
#include <conio.h>

#define MENU_SIZE 3
#define MENU_SIZE_ALGORITM 3
#define MENU_SIZE_POISK 3
#define MENU_SIZE_SETING 3
#define MENU_SIZE_SORTIROVKA 2
#define MENU_SIZE_MASS 3

// основные ключи, которые могут пригодитьс¤

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

//доп функции

int BIN_POISK(HANDLE hStdOut, int* size, int* mass)
{
	int num;
	printf("Введите число, которое хотите найти: ");
	scanf_s("%d", &num);
	int left = 0, right = *size - 1;
	int* mass2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass2[i] = mass[i];
	}
	for (int i = 0; i < *size - 1; i++)
	{
		for (int g = i; g < *size; g++)
		{
			if (mass2[i] > mass2[g])
			{
				int a = mass2[i];
				mass2[i] = mass2[g];
				mass2[g] = a;
			}
		}
	}
	for (int i = 0; i < *size; i++)
	{
		int middle = (left + right) / 2;
		if (num < mass2[middle])
		{
			right = middle - 1;
			printf("0\n");
		}
		else if (num > mass2[middle])
		{
			left = middle + 1;
			printf("1\n");
		}
		if (num == middle)
		{
			printf("Данное число существ");
		}
	}
	for (int i = 0; i < *size; i++)
	{
		printf("%d ", mass2[i]);
	}
	
}

int NAIV_POISK(HANDLE hStdOut, int* size, int* mass)
{
	int element, F = 0;
	printf("Введите элемент массива: ");
	scanf_s("%d", &element);
	for (int i = 0; i < *size; i++)
	{
		if (mass[i] == element)
		{
			F = 1;
			printf("Индекс элемента %d\n", i);
			system("pause");
			break;
		}
	}
	if (F = 1)
	{
		POISK(hStdOut, size, mass);
	}
	else
	{
		printf("Данного элемента нет в массиве");
		POISK(hStdOut, size, mass);
	}
}

int RAND_MASS(HANDLE hStdOut, int* size, int* mass)
{
	printf("Введите размер массива: ");
	if (*size != 0) {
		char k = '0';
		while (k != '\n') {
			k = getchar();
		}
		free(mass);
	}
	int temp;
	scanf_s("%d", &temp);
	*size = temp;
	mass = (int*)malloc(sizeof(int) * (*size));
	system("cls");

	int max, min;
	printf("Введите предел рандомных числе через пробел: ");
	scanf_s("%d %d", &min, &max);
	srand(time(NULL));
	for (int g = 0; g < *size; g++)
	{
		int ran = min + rand() % max;
		mass[g] = ran;
	}
	SETING(hStdOut, size, mass);
}

int LOOKING_MASS(HANDLE hStdOut, int* size, int* mass)
{
	printf("Размер массива: %d\n", *size);
	printf("Значения массива: ");
	for (int i = 0; i < *size; i++)
	{
		printf("%d ", mass[i]);
	}

	printf("\n");
}

int MASS(HANDLE hStdOut, int* size, int* mass)
{
	printf("Введите размер массива: ");
	if (*size != 0) {
		char k = '0';
		while (k != '\n') {
			k = getchar();
		}
		free(mass);
	}
	int temp;
	scanf_s("%d", &temp);
	*size = temp;
	mass = (int*)malloc(sizeof(int) * (*size));
	system("cls");
	printf("Введите значения в массив: ");
	for (int i = 0; i < *size; i++)
	{
		scanf_s("%d", &mass[i]);
	}
	for (int g = 0; g < *size; g++)
	{
		printf("%d ", mass[g]);
	}
	printf("\n");

	SETING(hStdOut, size, mass);
}

int SORTIROVKA(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	char* menu[MENU_SIZE_SORTIROVKA] = { "Пузырьковая сортировка", "Назад" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SORTIROVKA - 1; }
			if (choose_pos > MENU_SIZE_SORTIROVKA - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SORTIROVKA; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("«", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("»");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
}

int MENU_MASS(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	char* menu[MENU_SIZE_MASS] = { "Ручной массив", "Рандомный массив", "Назад" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SETING - 1; }
			if (choose_pos > MENU_SIZE_SETING - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SETING; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("«", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("»");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");

			MASS(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			RAND_MASS(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			SETING(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
}

int SETING(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	char* menu[MENU_SIZE_SETING] = { "Задать массив", "Посмотреть текущий массив", "Назад" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SETING - 1; }
			if (choose_pos > MENU_SIZE_SETING - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SETING; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("«", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("»");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");

			MENU_MASS(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			LOOKING_MASS(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			MENU(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
}

int POISK(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	char* menu[MENU_SIZE_POISK] = { "Наивный поиск", "Бинарный поиск", "Назад" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_POISK - 1; }
			if (choose_pos > MENU_SIZE_POISK - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_POISK; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("«", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("»");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			NAIV_POISK(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			BIN_POISK(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
}

int ALGORITM(HANDLE hStdOut, int* size, int* mass) {

	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	char* menu[MENU_SIZE_ALGORITM] = { "Поиск", "Сортировка", "Назад" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_ALGORITM - 1; }
			if (choose_pos > MENU_SIZE_ALGORITM - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_ALGORITM; i++) {
				cursorPos =
					(COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("«", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("»");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			POISK(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			SORTIROVKA(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			MENU(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
}

int MENU(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	char* menu[MENU_SIZE] = { "Алгоритмы", "Настройки", "Выход" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE - 1; }
			if (choose_pos > MENU_SIZE - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("«", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("»");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			SETING(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			printf("Goodbay!\n");
			system("pause");
			free(mass);
			_Exit(EXIT_SUCCESS);
			return 0;
			break;

		}
	}

	// вывод результата

}
// объ¤вление главной функции
int main() {
	// настройки
	setlocale(LC_ALL, "rus");
	// задаЄм название консольного окна
	system("title Application");

	// устанавливаем взаимодействие с русскими буквами
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	// получаем дескриптор окна дл¤ обращени¤ к консоли
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// отключение мигани¤ курсора в консоли (в нашем меню курсор лишний)
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);

	// задаЄм серый фон дл¤ окна консоли
	SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	// очищаем экран, чтобы настройка цвета применилась
	system("cls");
	int size = 0;
	int* mass = NULL;
	// объ¤вление переменных
	MENU(hStdOut, &size, mass);
	return 0;
}