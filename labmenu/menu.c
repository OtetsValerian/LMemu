#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include<inttypes.h>
// ���������� �������� ����������
#include <windows.h>
#include <conio.h>

#define MENU_SIZE 3
#define MENU_SIZE_ALGORITM 3
#define MENU_SIZE_POISK 3
#define MENU_SIZE_SETING 3
#define MENU_SIZE_SORTIROVKA 3
#define MENU_SIZE_MASS 3

// �������� �����, ������� ����� ����������

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

//��� �������

int SORT_WIB(HANDLE hStdOut, int* size, int* mass)
{
	
	int* mass2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass2[i] = mass[i];
	}
	int minPosition, tmp;
	clock_t time_start = clock();
	for (int i = 0; i < *size; i++)
	{
		minPosition = i;
		for (int j = i + 1; j < *size; j++)
			if (mass2[minPosition] > mass2[j])
				minPosition = j;
		tmp = mass2[minPosition];
		mass2[minPosition] = mass2[i];
		mass2[i] = tmp;
	}
	clock_t time_end = clock() - time_start;
	if (*size > 20) {
	}
	else {
		printf("�������� �������: ");
		for (int i = 0; i < *size; i++)
		{
			printf("%d ", mass2[i]);
		}
		printf("\n");
	}
	printf("����� ���������� ����������: %f", (double)time_end / CLOCKS_PER_SEC);
	printf("\n");
}

int SORT_SHELL_SENG(HANDLE hStdOut, int* size, int* mass)
{
	int* mass2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass2[i] = mass[i];
	}
	clock_t time_start = clock();
	
	
		if (*size % 2 == 0)
		{
			for (int s = 9*pow(2, *size) - 9 * pow(2, *size/2)+1; s > 0; s /= 2) {
				for (int i = s; i < *size; ++i) {
					for (int j = i - s; j >= 0 && mass2[j] > mass2[j + s]; j -= s) {
						int temp = mass2[j];
						mass2[j] = mass2[j + s];
						mass2[j + s] = temp;
					}
				}
			}
		}
		else
		{
			for (int s = 8 * pow(2, *size) - 6 * pow(2, (*size + 1) / 2) + 1; s > 0; s /= 2) {
				for (int i = s; i < *size; ++i) {
					for (int j = i - s; j >= 0 && mass2[j] > mass2[j + s]; j -= s) {
						int temp = mass2[j];
						mass2[j] = mass2[j + s];
						mass2[j + s] = temp;
					}
				}
			}
		}
	

	clock_t time_end = clock() - time_start;
	
	if (*size > 20) {
	}
	else {
		printf("�������� �������: ");
		for (int i = 0; i < *size; i++)
		{
			printf("%d ", mass2[i]);
		}
		printf("\n");
	}
	printf("����� ���������� ����������: %f", (double)time_end / CLOCKS_PER_SEC);
	printf("\n");
}

int BIN_POISK(HANDLE hStdOut, int* size, int* mass)
{
	int num;
	printf("������� �����, ������� ������ �����: ");
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
		if (num == mass2[middle])
		{
			printf("������ ����� ����������\n");
			system("pause");
			POISK(hStdOut, size, mass);
		}
		else if (num < mass2[middle])
		{
			right = middle - 1;

		}
		else if (num > mass2[middle])
		{
			left = middle + 1;

		}
	}
	printf("������ ����� �� ����������\n");
	system("pause");
	POISK(hStdOut, size, mass);
}

int NAIV_POISK(HANDLE hStdOut, int* size, int* mass)
{
	int element, F = 0;
	printf("������� ������� �������: ");
	scanf_s("%d", &element);
	for (int i = 0; i < *size; i++)
	{
		if (mass[i] == element)
		{
			F = 1;
			printf("������ �������� %d\n", i);
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
		printf("������� �������� ��� � �������");
		POISK(hStdOut, size, mass);
	}
}

int RAND_MASS(HANDLE hStdOut, int* size, int* mass)
{
	printf("������� ������ �������: ");
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
	printf("������� ������ ��������� ����� ����� ������: ");
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
	printf("������ �������: %d\n", *size);
	printf("�������� �������: ");
	for (int i = 0; i < *size; i++)
	{
		printf("%d ", mass[i]);
	}

	printf("\n");
}

int MASS(HANDLE hStdOut, int* size, int* mass)
{
	printf("������� ������ �������: ");
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
	printf("������� �������� � ������: ");
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
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	char* menu[MENU_SIZE_SORTIROVKA] = { "���������� �����-��������", "���������� �������", "�����"};

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// �������� ������ ������
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

			// ������������ ������������� ����
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SORTIROVKA - 1; }
			if (choose_pos > MENU_SIZE_SORTIROVKA - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SORTIROVKA; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�");

			// �������� ������ ������ �������
			iKey = _getch();
		}

		/* 2. ������� ����� ��������� */
		switch (choose_pos) {
		case 0:
			system("cls");
			SORT_SHELL_SENG(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			SORT_WIB(hStdOut, size, mass);
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

int MENU_MASS(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	char* menu[MENU_SIZE_MASS] = { "������ ������", "��������� ������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// �������� ������ ������
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

			// ������������ ������������� ����
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SETING - 1; }
			if (choose_pos > MENU_SIZE_SETING - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SETING; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�");

			// �������� ������ ������ �������
			iKey = _getch();
		}

		/* 2. ������� ����� ��������� */
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
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	char* menu[MENU_SIZE_SETING] = { "������ ������", "���������� ������� ������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// �������� ������ ������
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

			// ������������ ������������� ����
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SETING - 1; }
			if (choose_pos > MENU_SIZE_SETING - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SETING; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�");

			// �������� ������ ������ �������
			iKey = _getch();
		}

		/* 2. ������� ����� ��������� */
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
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	char* menu[MENU_SIZE_POISK] = { "������� �����", "�������� �����", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// �������� ������ ������
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

			// ������������ ������������� ����
			if (choose_pos < 0) { choose_pos = MENU_SIZE_POISK - 1; }
			if (choose_pos > MENU_SIZE_POISK - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_POISK; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�");

			// �������� ������ ������ �������
			iKey = _getch();
		}

		/* 2. ������� ����� ��������� */
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

	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	char* menu[MENU_SIZE_ALGORITM] = { "�����", "����������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// �������� ������ ������
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

			// ������������ ������������� ����
			if (choose_pos < 0) { choose_pos = MENU_SIZE_ALGORITM - 1; }
			if (choose_pos > MENU_SIZE_ALGORITM - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_ALGORITM; i++) {
				cursorPos =
					(COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�");

			// �������� ������ ������ �������
			iKey = _getch();
		}

		/* 2. ������� ����� ��������� */
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
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	char* menu[MENU_SIZE] = { "���������", "���������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// �������� ������ ������
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

			// ������������ ������������� ����
			if (choose_pos < 0) { choose_pos = MENU_SIZE - 1; }
			if (choose_pos > MENU_SIZE - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�");

			// �������� ������ ������ �������
			iKey = _getch();
		}

		/* 2. ������� ����� ��������� */
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

	// ����� ����������

}
// ���������� ������� �������
int main() {
	// ���������
	setlocale(LC_ALL, "rus");
	// ����� �������� ����������� ����
	system("title Application");

	// ������������� �������������� � �������� �������
	SetConsoleCP(1251); // ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

	// �������� ���������� ���� �� �������� � �������
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// ���������� ������ ������� � ������� (� ����� ���� ������ ������)
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);

	// ����� ����� ��� �� ���� �������
	SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	// ������� �����, ����� ��������� ����� �����������
	system("cls");
	int size = 0;
	int* mass = NULL;
	// ���������� ����������
	MENU(hStdOut, &size, mass);
	return 0;
}