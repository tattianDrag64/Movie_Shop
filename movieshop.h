#pragma once
struct movie
{
    enum { S = 40 };
    char title[S];
    char director[S];
    char country[S];
    char genre[S];
    double rating;
    double price;
};

char* strcasestr(const char* str, const char* pattern);

int key(int n = 1); //��������� �� ����

void header();

void mainmenu(movie* mas, int size, int key); //����� ����

void mainn(const movie& m); //����� ������ ���������

void mainn(movie* mas, int size); //����� ������� ���������

//-------------------------------------------------------------------------------------
//����������
int sort(movie* mas, int size);
void sort(movie* mas, int size, bool (*pf)(const movie&, const movie&));

bool sort_by_title_incr(const movie& a, const movie& b);
bool sort_by_title_decr(const movie& a, const movie& b);

bool sort_by_director_incr(const movie& a, const movie& b);
bool sort_by_director_decr(const movie& a, const movie& b);

bool sort_by_genre_incr(const movie& a, const movie& b);
bool sort_by_genre_decr(const movie& a, const movie& b);

bool sort_by_rating_decr(const movie& a, const movie& b);

bool sort_by_price_incr(const movie& a, const movie& b);

int sortalphabetorreverse(movie* mas, int size); //����� ���������� �� �������� ��� � �������� �������

//----------------------------------------------------------------------------------------------------------
//�����
int search(movie* mas, int size);

void search_by_title(movie* mas, int size, char* word);
void search_by_genre(movie* mas, int size, const char* keyW);
void search_by_director(movie* mas, int size, const char* keyW);

//--------------------------------------------------------------------------------------------------
////���������� ����� �� ��������
void most_popular(movie* mas, int size, const char* keyW);
