#include <iostream>
using namespace std;
struct stek
{
	int now;
	stek* next;
	void push(stek*&, int );
	int pop(stek*&);
	int peek(stek*);
};
void stek::push(stek*& st, int versh)
{

	stek* elem = new stek;
	elem->now = versh;
	elem->next = st;
	st = elem;
}
int stek::pop(stek*& st)
{

	int value = st->now;
	stek* temp = st;
	st = st->next;
	delete temp;
	return value;
}
int stek::peek(stek* st)
{
	return st->now;
}

struct List
{
	int now;
	List* next;
	void add(List*&, int);
	void deletik(List*&,int);
};
void List::add(List*& list, int data)
{  

	if (!list) {
		list = new List;
		list->now = data; 
		list->next = 0; 
		return; 
	}
	List* temp = list;
	while (temp->next) temp = temp->next;
	List* elem = new List;
	elem->now = data;
	elem->next = NULL;
	temp->next = elem;
}
void List::deletik(List*& l, int key)
{

	if (l->now == key) {
		List* tmp = l;
		l = l->next; 
		delete tmp; 
	}
	else
	{
		List* tmp = l;
		while (tmp)
		{
			if (tmp->next)
				if (tmp->next->now == key)
				{
					List* tmp2 = tmp->next;
					tmp->next = tmp->next->next;
					delete tmp2;
				}
			tmp = tmp->next;
		}
	}
}

int tru(List** gr, int number)
{
	int count;
	for (int i = 0; i < number; i++)
	{

		count = 0;
		List* nearby = gr[i];

		while (nearby)
		{
			count++;
			nearby = nearby->next;
		}
		if (count % 2 == 1) return 0;
	}
	return 1;
}

void check(List** gr, int v)
{
	stek k;
	List l;
	stek *S = 0;
	int next;
	v = v - 1;
	k.push(S, v);
	while (S)
	{
		v = k.peek(S);
		if (!gr[v]) {
			v = k.pop(S);
			cout << v + 1 << "  ";
		}
		else
		{
			next = gr[v]->now;
			k.push(S, next);
			l.deletik(gr[v], next);
			l.deletik(gr[next], v);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "Количество вершин:  ";
	int n; 
	cin >> n;
	int matr;
	cout << "Начальная вершина: ";
	int ent;
	cin >> ent;
	cout << "Введите матрицу смежности" << endl;
	List s;
	List** graph = new List * [n];
	for (int i = 0; i < n; i++) {
		graph[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			cin >> matr;
			if (matr) s.add(graph[i], j);
		}
	}
	if (tru(graph, n))
	{
		cout << "Путь эйлерова цикла: ";
		check(graph, ent);
	}
	else cout << "Эйлеров цикл не получится.";
	return 0;
}