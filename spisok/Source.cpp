#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;
struct node
{
	int data;
	node* next;
	node* prev;
	node(int _data)
	{
		data = _data;
		next = nullptr;
		prev = nullptr;
	}
};

struct list
{
	node* head;
	node* tail;

	list() : head(nullptr), tail(nullptr) {}

	bool zero()
	{
		return head == nullptr;
	}

	void push_back(int y)
	{
			node* x = new node(y);

			if (zero())
			{
				head = x;
				tail = x;
			}
			tail->next = x;
			x->prev = tail;
			tail = x;
	}

	void pushback(int k)
	{
		for (int i = 0; i < k; i++)
		{
			node* x = new node(rand() % 10);

			if (zero())
			{
				head = x;
				tail = x;
			}
			tail->next = x;
			x->prev = tail;
			tail = x;
		}
	}

	void print()
	{
		if (zero()) {
			cout << "список пуст";
			return;
		}
		node* current_node = head;

		while (current_node)
		{
			cout << current_node->data << " ";
			current_node = current_node->next;
		}
		cout << endl;
	}

	node* operator[] (int index)
	{
		--index;
		if (index == 0)
		{
			node* p = head;
			p = p->next;
			p->prev = nullptr;
			free(head);
			head->next = p->next;
			head = p;
		}
		else {
			if (zero()) return nullptr;
			node* p = head;
			node* x = head;

			for (int i = 0; i < index; i++) {
				p = p->next;
				if (!p) return nullptr;
			}
			for (int i = 0; i < (index - 1); i++) {
				x = x->next;
				if (!x) return nullptr;
			}
			x->next = p->next;
			delete p;

			return 0;
		}
	}

	void alldel()
	{
			node* current;
			current = head;

			for (int i = 1; head->next = nullptr; i++) {}

			if (zero()) return;
			node* current_node = head;
			head = current_node->next;
			delete current_node;
	}



	void out(int kolichestvo_el)
	{
		ofstream file;
		file.open("F1.txt", ofstream::app);
		if (!file.is_open())
		{
			cout << "Ошибка открытия файла!\n";
		}
		else
		{
			node* current_node = head;
			int i = 1;
			do
			{
				file.write((char*)&current_node->data, sizeof(int));
				current_node = current_node->next;
				i++;
			} while (i <= kolichestvo_el);
		}
		file.close();
	}

	//восстановление списка из файла
	void in(int kolichestvo_el, struct list s)
	{
		ifstream file;
		file.open("F1.txt");
		if (!file.is_open())
		{
			cout << "Ошибка открытия файла!\n";
		}
		else
		{
			int x;
			for (int i = 1; i <= kolichestvo_el; i++)
			{
				file.read((char*)&x, sizeof(int));
				s.push_back(x);
			}
		}
		file.close();
		cout << "Востановленный список: \n";
		s.print();
	}

};

int main()
{
	setlocale(0, "rus");
	int n, k;
	srand(time(0));
	list l;
	cout << "Сколько элементов добавить в конец списка?" << endl;
	cin >> k;
	l.pushback(k);
	l.print();
	cout << "Какой по счету элемент удалить?" << endl;
	cin >> n;
	l.operator[](n);
	l.print();
	k--;
	l.out(k);
	l.alldel();
	l.in(k , l);
	return 0;
}