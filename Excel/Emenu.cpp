#include <sstream>
#include "StreamTable.h"
#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include<inttypes.h>
#include <windows.h>
#include <conio.h>
#include <limits>


#define MENU_SIZE 3
#define MENU_SIZE_ALGORITM 4
#define MENU_SIZE_POISK 3
#define MENU_SIZE_SETING 3
#define MENU_SIZE_SORTIROVKA 3
#define MENU_SIZE_MASS 3
#define SORT_SIZE 2


#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80


int POISK(HANDLE hStdOut, int* size, int* mass);
int SETING(HANDLE hStdOut, int* size, int* mass);
int MENU(HANDLE hStdOut, int* size, int* mass);
int SORT_WIB(int* size, int* mass);
int SORT_SHELL_SENG(int* size, int* mass);
int BIN_POISK(HANDLE hStdOut, int* size, int* mass);
int NAIV_POISK(HANDLE hStdOut, int* size, int* mass);
int RAND_MASS(HANDLE hStdOut, int* size, int* mass);
int LOOKING_MASS(HANDLE hStdOut, int* size, int* mass);
int MASS(HANDLE hStdOut, int* size, int* mass);
int SORTIROVKA(HANDLE hStdOut, int* size, int* mass);
int MENU_MASS(HANDLE hStdOut, int* size, int* mass);
int ALGORITM(HANDLE hStdOut, int* size, int* mass);
int WIB(HANDLE hStdOut, int* size, int* mass);
int SHELL_SENG(HANDLE hStdOut, int* size, int* mass);



void Excel(clock_t time_end_shell_seng, clock_t time_end_wib)
{
	typedef std::numeric_limits< double > dbl;

	double s1 = time_end_shell_seng / CLOCKS_PER_SEC, s2 = time_end_wib / CLOCKS_PER_SEC;

	double tome_sort[2] = { s1, s2 };
	
	StreamTable st(std::cout);
	st.AddCol(30);
	st.AddCol(30);
	st.AddCol(30);
	

	//�����������������, ���� ������� ����� ���������� �������
	//st.Clear();
	//st.SetCols(4, 10);

	//st.SetVisible(1, false);//������� ����� ��������

	st.MakeBorderExt(true);
	st.SetDelimRow(true, '-');//st.SetDelimRow(false);//��� ��������-������������ �����
	st.SetDelimCol(true, '|');//st.SetDelimCol(false);//��� ��������-������������ �����

	const char* sortirovki[SORT_SIZE] = {"���������� �����-��������", "���������� �������"};

	//��������� � �������� ��������� ���������
	st << "��� ����������" << "����� ����������" << "������� �� �������" ;
	enum { nr = SORT_SIZE};
	if (s1 < s2)
	{
		double raz = s2 - s1;
		for (int i = 0; i < nr; i++) {
			if (i == 0) {
				st << sortirovki[i] << (double)tome_sort[i] << 0;
			}
			st << sortirovki[i] << (double)tome_sort[i] << (double)raz;
		}
	}
	else
	{
		double raz = s1 - s2;
		for (int i = 0; i < nr; i++) {
			if (i == 1) {
				st << sortirovki[i] << (double)tome_sort[i] << 0;
			}
			st << sortirovki[i] << (double)tome_sort[i] << (double)raz;
		}
	}
}

int TabExcel(HANDLE hStdOut, int* size, int* mass)
{
	clock_t time_start_wib = clock();
	SORT_WIB(size, mass);
	clock_t time_end_wib = clock() - time_start_wib;
	system("cls");

	clock_t time_start_shell_seng = clock();
	SORT_SHELL_SENG(size, mass);
	clock_t time_end_shell_seng = clock() - time_start_shell_seng;
	system("cls");

	Excel(time_end_shell_seng, time_end_wib);

	return 0;
}

int SORT_WIB(int* size, int* mass)
{

	int* mass2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass2[i] = mass[i];
	}
	int minPosition, tmp;
	
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
	return 0;
}

int WIB(HANDLE hStdOut, int* size, int* mass)
{
	clock_t time_start = clock();
	SORT_WIB(size, mass);
	clock_t time_end = clock() - time_start;
	printf("����� ���������� ����������: %f", (double)time_end / CLOCKS_PER_SEC);
	printf("\n");
	return 0;
}

int SORT_SHELL_SENG(int* size, int* mass)
{
	int* mass2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass2[i] = mass[i];
	}
	if (*size % 2 == 0)
	{
		for (int s = 9 * pow(2, *size) - 9 * pow(2, *size / 2) + 1; s > 0; s /= 2) {
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
	return 0;
}

int SHELL_SENG(HANDLE hStdOut, int* size, int* mass)
{		
	clock_t time_start = clock();
	SORT_SHELL_SENG(size, mass);
	clock_t time_end = clock() - time_start;

	printf("����� ���������� ����������: %f", (double)time_end / CLOCKS_PER_SEC);
	printf("\n");
	return 0;
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
	return 0;
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
	return 0;
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
	return 0;
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
	return 0;
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
	return 0;
}

int SORTIROVKA(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	const char* menu[MENU_SIZE_SORTIROVKA] = { "���������� �����-��������", "���������� �������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
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
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("�");

			// �������� ������ ������ �������
			iKey = _getch();
		}

		/* 2. ������� ����� ��������� */
		switch (choose_pos) {
		case 0:
			system("cls");
			SHELL_SENG(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			WIB(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int MENU_MASS(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	const char* menu[MENU_SIZE_MASS] = { "������ ������", "��������� ������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
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
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
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
	return 0;
}

int SETING(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	const char* menu[MENU_SIZE_SETING] = { "������ ������", "���������� ������� ������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
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
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
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
	return 0;
}

int POISK(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	const char* menu[MENU_SIZE_POISK] = { "������� �����", "�������� �����", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
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
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
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
	return 0;
}

int ALGORITM(HANDLE hStdOut, int* size, int* mass) {

	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	const char* menu[MENU_SIZE_ALGORITM] = { "�����", "����������", "����� �������", "�����"};

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
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
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
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
			TabExcel(hStdOut, size, mass);
			system("pause");
			break;
		case 3:
			system("cls");
			MENU(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int MENU(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // ��������� �� ������� ���������� ������ ����
	int iKey; // ��������� �� �������� ������� �������
	int exit_flag; // ���� �� ���������� ���������
	COORD cursorPos; // ���������� ���������� �������, ����� ����� ��������� �����

	const char* menu[MENU_SIZE] = { "���������", "���������", "�����" };

	// ������������ (���������� ���������) ����������
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. ����� ���� � ������������� */

		// ����� ������� � ��������� ���������
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
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
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// ����������� ��������� �������
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("�", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
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
	return 0;

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
