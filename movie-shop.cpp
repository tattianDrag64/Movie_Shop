#include <iostream>
#include <conio.h>
#include <iomanip>
#include <stdio.h>
#include "movieshop.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	const int N = 10;
	movie mas_witn_movies[N]{ {"My Fair Lady", "George Cukor", "USA", "Musical", 7.8, 8.99},
		 {"Spirited Away", "Hayao Miyazaki", "Japan","Fantasy", 8.6, 9.94},
		 {"The Breadwinner", "Nora Twomey", "Ireland","Drama", 7.8, 10.9},
		 {"Parasite", "Bong Joon-ho", "Republic of Korea","Thriller", 8.5, 9.99},
		 {"Klaus", "Sergio Pablos", "Spain","Animation", 8.2, 10.54},
		 {"The Fool", "Yuriy Bykov", "Russia","Drama", 8.1, 9.15},
		 {"The Iron Giant", "Brad Bird", "USA","Science fiction", 8.1, 8.6},
		 {"The Wolf of Wall Street", "Martin Scorsese","USA","Biopic", 8.2, 11.1},
		 {"Hamilton", "Lin-Manuel Miranda","USA", "Biopic", 8.4, 10.5},
		 {"Notre-Dame de Paris", "Gilles Amado", "France", "Musical", 8.9, 9.5}
	};


	mainmenu(mas_witn_movies, N, 0);
	mainn(mas_witn_movies, N);
	int k = key(5);
	do {
		switch (k)
		{
		case 0: {
			system("CLS");
			mainmenu(mas_witn_movies, N, k);
			mainn(mas_witn_movies, N);
			break;
		} //главное меню и вывод всего массива 
		case 1:
		{
			system("CLS");
			mainmenu(mas_witn_movies, N, k);
			int search_num = search(mas_witn_movies, N);
			cin.get();
			char searchword[15];
			cout << "| Search: ";
			cin.getline(searchword, sizeof(searchword));
			switch (search_num)
			{
			case 0:
				search_by_title(mas_witn_movies, N, searchword); break; //поиск по названию
			case 1:
				search_by_genre(mas_witn_movies, N, searchword); break; //поиск по жанру
			case 2:
				search_by_director(mas_witn_movies, N, searchword); break; //поиск по режиссеру 
				break;
			}
			break;
		} //поиск
		case 2:
		{
			system("CLS");
			mainmenu(mas_witn_movies, N, k);
			int sort_num = sort(mas_witn_movies, N);
			if (sort_num == 0) //сортировка по названию
			{
				int sortap = sortalphabetorreverse(mas_witn_movies, N);
				if (sortap == 0)
				{
					system("CLS");
					mainmenu(mas_witn_movies, N, k);
					sort(mas_witn_movies, N, sort_by_title_incr);
				}
				else if (sortap == 1)
				{
					system("CLS");
					mainmenu(mas_witn_movies, N, k);
					sort(mas_witn_movies, N, sort_by_title_decr);
				}
			}
			else if (sort_num == 1) //сортировка по режиссеру
			{
				int sortap = sortalphabetorreverse(mas_witn_movies, N);
				if (sortap == 0)
				{
					system("CLS");
					mainmenu(mas_witn_movies, N, k);
					sort(mas_witn_movies, N, sort_by_director_incr);
				}
				else if (sortap == 1)
				{
					system("CLS");
					mainmenu(mas_witn_movies, N, k);
					sort(mas_witn_movies, N, sort_by_director_decr);
				}
			}
			else if (sort_num == 2) //сортировка по жанру
			{
				int sortap = sortalphabetorreverse(mas_witn_movies, N);
				if (sortap == 0)
				{
					system("CLS");
					mainmenu(mas_witn_movies, N, k);
					sort(mas_witn_movies, N, sort_by_genre_incr);
				}
				else if (sortap == 1)
				{
					system("CLS");
					mainmenu(mas_witn_movies, N, k);
					sort(mas_witn_movies, N, sort_by_genre_decr);
				}
			}
			else if (sort_num == 3) //сортировка по рейтингу 
			{
				system("CLS");
				mainmenu(mas_witn_movies, N, k);
				sort(mas_witn_movies, N, sort_by_rating_decr);
			}
			else if (sort_num == 4) //сортировка по цене
			{
				system("CLS");
				mainmenu(mas_witn_movies, N, k);
				sort(mas_witn_movies, N, sort_by_price_incr);
			}
			mainn(mas_witn_movies, N);
			break;
		} //сортировка
		case 3:
		{
			system("CLS");
			mainmenu(mas_witn_movies, N, k);
			cin.get();
			char searchword[15];
			cout << "| Search: ";
			cin.getline(searchword, sizeof(searchword));
			most_popular(mas_witn_movies, N, searchword);
			break;
		} //сортировка жанра по рейтингу
		default:
			exit(0); //выход
		}
		k = key(5);
	} while (k);

	_getch();
}
