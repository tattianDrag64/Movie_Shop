#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include "movieshop.h"

using namespace std;

void SetColor(int ForgC = 15)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void SetColor(int text, int fon)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, (fon << 4) + text);
}

char* strcasestr(const char* str, const char* pattern) {
	size_t i;

	if (!*pattern)
		return (char*)str;

	for (; *str; str++) {
		if (toupper((unsigned char)*str) == toupper((unsigned char)*pattern)) {
			for (i = 1;; i++) {
				if (!pattern[i])
					return (char*)str;
				if (toupper((unsigned char)str[i]) != toupper((unsigned char)pattern[i]))
					break;
			}
		}
	}
	return NULL;
}

void header()
{
	SetColor(15, 0);
	cout << " -------------------------------------------------------------------------------------" << endl
		<< "| /_______________________\\_______________________________________________  --  П  X  |" << endl
		<< "| <--  -->  @  www.movieshop.com                                       *        ===   |" << endl
		<< "| $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ |" << endl
		<< "| $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ |" << endl
		<< "| $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ |" << endl
		<< "| ----------------------------------------------------------------------------------- |";
}

int key(int n) //навигация по меню 
{
	int key;
	cout << "| ";
	SetColor(8);
	cout << " Enter a number from 1 to " << n << ": ";
	SetColor(15, 0);
	cin >> key;
	key--;
	return key;
}

void mainmenu(movie* mas, int size, int key) //вывод меню
{
	char menu[5][10] = { "HOME", "SEARCH", "SORT","POPULAR", "EXIT" };
	header();
	cout << endl << "|" << "\t\t\t\t\t\t  ";
	for (int j = 0; j < key; j++)
	{
		cout << " " << menu[j] << " ";
	}
	SetColor(0, 14);
	cout << " " << menu[key] << " ";
	SetColor(7, 0);
	for (int j = key + 1; j < 5; j++)
	{
		cout << " " << menu[j] << " ";
	}
	cout << " |";
	cout << endl << "|                                                                                     |" << endl;
}

void mainn(const movie& m) //вывод данных структуры
{
	cout << "|\t         ============                                                         |" << endl
		<< "|\t        *            *                                                        |" << endl
		<< "|\t        * P          *       " << setw(14) << "TITLE:      " << setw(25) << m.title << setw(11) << "|" << endl
		<< "|\t        *   О        *       " << setw(14) << "DIRECTOR:   " << setw(25) << m.director << setw(11) << "|" << endl
		<< "|\t        *     S      *       " << setw(14) << "COUNTRY:    " << setw(25) << m.country << setw(11) << "|" << endl
		<< "|\t        *       Т    *       " << setw(14) << "GENRE:      " << setw(25) << m.genre << setw(11) << "|" << endl
		<< "|\t        *        Е   *       " << setw(14) << "RATING:     " << setw(25) << m.rating << setw(11) << "|" << endl
		<< "|\t        *          R *       " << setw(14) << "DISK PRICE: " << setw(24) << m.price << "$" << setw(11) << "|" << endl
		<< "|\t        *            *                                                        |" << endl
		<< "|\t         ============                                                         |" << endl
		<< "|                                                                                     |";
}

void mainn(movie* mas, int size)  //вывод массива структуры
{
	for (int i = 0; i < size; i++)
	{
		mainn(mas[i]);
		cout << endl;
	}

}

//-------------------------------------------------------------------------------------
//сортировка
int sort(movie* mas, int size)
{
	char sort[5][15] = { "Title ","Director", "Genre", "Rating", "Disc price" };
	cout << "|\t\t\t\t            SORT BY:                                  |" << endl;
	for (int j = 0; j < 5; j++)
	{
		cout << "|\t\t\t\t       - " << setw(10) << sort[j] << setw(36) << "|" << endl;
	}
	int k = key(5);
	system("CLS");
	mainmenu(mas, size, 2);
	cout << "|\t\t\t\t            SORT BY:                                  |" << endl;
	for (int j = 0; j < k; j++)
	{
		cout << "|\t\t\t\t       - " << setw(10) << sort[j] << setw(36) << "|" << endl;
	}
	cout << "|\t\t\t\t       ";
	SetColor(0, 14);
	cout << "- " << setw(10) << sort[k];
	SetColor(7, 0);
	cout << setw(36) << "|" << endl;
	for (int j = k + 1; j < 5; j++)
	{
		cout << "|\t\t\t\t       - " << setw(10) << sort[j] << setw(36) << "|" << endl;
	}
	cout << "|" << endl;
	return k;
}

int sortalphabetorreverse(movie* mas, int size) //выбор сортировка по алфавиту или в обратном порядке
{
	char variants[2][15] = { "Alphabetical", "In reverse" };
	cout << "|\t\t\t\t           ORDER BY:                                  |" << endl;
	for (int j = 0; j < 2; j++)
	{
		cout << "|\t\t\t          - " << setw(15) << variants[j] << setw(36) << "|" << endl;
	}
	int k = key(2);
	return k;
}

void sort(movie* mas, int size, bool (*pf)(const movie&, const movie&))
{
	int i, k;
	for (i = 0; i < size; i++)
		for (k = 0; k < size - 1 - i; k++)
			if ((*pf)(mas[k], mas[k + 1]))
			{
				swap(mas[k], mas[k + 1]);
			}
}

bool sort_by_title_incr(const movie& a, const movie& b)
{
	return strcmp(a.title, b.title) > 0;
}
bool sort_by_title_decr(const movie& a, const movie& b)
{
	return strcmp(a.title, b.title) < 0;
}
bool sort_by_director_incr(const movie& a, const movie& b)
{
	return strcmp(a.director, b.director) > 0;
}
bool sort_by_director_decr(const movie& a, const movie& b)
{
	return strcmp(a.director, b.director) < 0;
}
bool sort_by_genre_incr(const movie& a, const movie& b)
{
	return strcmp(a.genre, b.genre) > 0;
}
bool sort_by_genre_decr(const movie& a, const movie& b)
{
	return strcmp(a.genre, b.genre) < 0;
}
bool sort_by_rating_decr(const movie& a, const movie& b)
{
	return a.rating < b.rating;
}
bool sort_by_price_incr(const movie& a, const movie& b)
{
	return a.price > b.price;
}

//----------------------------------------------------------------------------------------------------------
//поиск
int search(movie* mas, int size)
{
	char search[5][15] = { "Title ","Genre", "Director" };
	cout << "|\t\t\t\t       SEARCH BY:                                     |" << endl;
	for (int j = 0; j < 3; j++)
	{
		cout << "|\t\t\t\t       - " << setw(10) << search[j] << setw(36) << "|" << endl;
	}
	int k = key(3);
	system("CLS");
	mainmenu(mas, size, 1);
	cout << "|\t\t\t\t       SEARCH BY:                                     |" << endl;
	for (int j = 0; j < k; j++)
	{
		cout << "|\t\t\t\t       - " << setw(10) << search[j] << setw(36) << "|" << endl;
	}
	cout << "|\t\t\t\t       ";
	SetColor(0, 14);
	cout << "- " << setw(10) << search[k];
	SetColor(7, 0);
	cout << setw(36) << "|" << endl;
	for (int j = k + 1; j < 3; j++)
	{
		cout << "|\t\t\t\t       - " << setw(10) << search[j] << setw(36) << "|" << endl;
	}
	return k;
}
void search_by_title(movie* mas, int size, char* word)
{
	bool p = false;
	for (int i = 0; i < size; i++)
	{
		if (strcasestr(mas[i].title, word) != 0)
		{
			mainn(mas[i]);
			cout << endl;
			p = true;
		}
	}
	if (p == false)
		cout << endl << "|                                      No results!                                    |" << endl << endl;
}
void search_by_genre(movie* mas, int size, const char* keyW)
{
	bool p = false;
	for (int i = 0; i < size; i++)
		if (strcasestr(mas[i].genre, keyW))
		{
			mainn(mas[i]);
			cout << endl;
			p = true;
		}
	if (p == false)
		cout << endl << "|                                      No results!                                    |" << endl << endl;
}
void search_by_director(movie* mas, int size, const char* keyW)
{
	bool p = false;
	for (int i = 0; i < size; i++)
		if (strcasestr(mas[i].director, keyW))
		{
			mainn(mas[i]);
			cout << endl;
			p = true;
		}
	if (p == false)
		cout << endl << "|                                      No results!                                    |" << endl << endl;
}

//--------------------------------------------------------------------------------------------------
////сортировка жанра по рейтингу
void most_popular(movie* mas, int size, const char* keyW)
{
	bool p = false;
	for (int i = 0; i < size; i++)
	{
		if (_stricmp(keyW, mas[i].genre) == 0)
		{
			sort(mas, size, sort_by_rating_decr);
			p = true;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (_stricmp(keyW, mas[i].genre) == 0)
		{
			mainn(mas[i]);
			cout << endl;
		}
	}
	if (p == false)
		cout << endl << "|                                      No results!                                    |" << endl << endl;
}

