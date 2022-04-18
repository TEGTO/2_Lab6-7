#include<iostream>
#include<cmath>
#include <fstream>

using namespace std;
struct Coor
{
	int x;
	int y;
};
enum Type
{
	full, path, tree = path, cycle
};

struct Graf
{
	Graf()
	{


		this->count_tops = 0;
	}

	Graf(int count_tops, int type)
	{
		mat = new int* [count_tops];
		for (int i = 0; i < count_tops; ++i)
			mat[i] = new int[count_tops];

		this->type = type;
		this->count_tops = count_tops;
	}
	int** mat;
	int type;
	int count_tops;


};

void fill()
{
	ofstream out("Grafs1.txt", ios::binary | ios::app);
	Graf Mas(3, 0);
	out.write((char*)&Mas.count_tops, sizeof(Mas.count_tops));
	out.write((char*)&Mas.type, sizeof(Mas.type));

	Mas.mat[0][0] = 0;
	Mas.mat[0][1] = 1;
	Mas.mat[0][2] = 1;
	Mas.mat[1][0] = 1;
	Mas.mat[1][1] = 0;
	Mas.mat[1][2] = 0;
	Mas.mat[2][0] = 1;
	Mas.mat[2][1] = 1;
	Mas.mat[2][2] = 1;
	for (int i = 0; i < Mas.count_tops; i++)
	{
		for (int j = 0; j < Mas.count_tops; j++)
		{
			out.write((char*)&Mas.mat[i][j], sizeof(Mas.mat[i][j]));
		}
	}
	out.close();
}
struct Top
{

	int count;
	int name;

};

struct lFile
{
	void push_back(Top data);


	void print();
	int find(int x);
	void print_v2(double* arr,int size);
	void print_v3(int* sorted,Coor* arr, int size, int foo(Coor));
private:

	int Size = 0;
	struct Node
	{
		Top data;
		Node* next = nullptr;
		Node* prev = nullptr;
		Node(Top data) { this->data = data; }
	};
	Node* head = nullptr;
	Node* tail = nullptr;

};
void lFile::push_back(Top data) {
	Node* node = new Node(data);
	if (head == nullptr) {
		head = node;
		tail = node;
		head->prev = nullptr;
		tail->next = nullptr;
		this->Size++;
	}
	else {
		tail->next = node;
		node->prev = tail;
		node->next = nullptr;
		tail = node;

		this->Size++;
	}
}
void lFile::print()
{

	Node* iter = head;
	while (iter != nullptr)
	{
		cout << "x" << iter->data.name << endl;

		iter = iter->next;
	}

}

int lFile::find(int x)
{
	Node* iter = head;
	while (iter->data.count != x)
	{
		if (iter->data.count == x)
		{
			return iter->data.name;
		}
		else iter = iter->next;
	}
	return iter->data.name;
}

void lFile::print_v2(double* arr,int size)
{
	Node* iter  = head;
	for (size_t i = 0; i < size; i++)
	{
		iter = head;
		
		while (iter->data.count != arr[i])
		{

			
			iter = iter->next;
		}
		if (iter->data.count == arr[i])
		{
			cout << "Length x" << iter->data.name << " : " << arr[i] << endl;

		}
	}
	
}

void lFile::print_v3(int* sorted,Coor* arr, int size, int foo(Coor))
{
	Coor check;
	Node* iter = head;
	for (size_t i = 0; i < size; i++)
	{

	
		iter = head;

		while (iter->data.count != sorted[i])
		{


			iter = iter->next;
		}
		if (iter->data.count == sorted[i])
		{
			for (int j = 0; j < size; j++)
			{
				if (sorted[i]== foo(arr[j]))
				{
					check = arr[j];
				}
			}
			cout << "x" << iter->data.name << " x=" << check.x << "  " << " y=" << check.y << endl;

		}
		
	}
}



void print(int** arr,int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}

void task1()
{
	int g1 = 0;
	int type;
	int read;
	lFile sort;
	ifstream in("Grafs1.txt", ios::binary);

	in.read((char*)&g1, sizeof(g1));
	in.read((char*)&type, sizeof(type));
	Graf g(g1, type);
	for (int i = 0; i < g1; i++)
	{
		for (int j = 0; j < g1; j++)
		{
			in.read((char*)&read, sizeof(read));
			g.mat[i][j] = read;
		}
	}
	in.close();
	int size = g.count_tops;
	cout << "Unsorted:\n";
	print(g.mat, g.count_tops);
	
	int count = 0, count_arr = 0;
	int* edges = new int[g.count_tops];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (g.mat[i][j] == 1)
			{
				count++;
			}
		}
		edges[count_arr] = count;
		count = 0;
		count_arr++;
	}
	Top d;
	for (int i = 0; i < size; i++)
	{
		d.name = i;
		d.count = edges[i];
		sort.push_back(d);
	}
	
	sort.print();
	cout << endl;
	int buff = 0;
	int i, j;
	for (i = 1; i < size; i++)
	{
		buff = edges[i];


		for (j = i - 1; j >= 0 && edges[j] > buff; j--)
			edges[j + 1] = edges[j];

		edges[j + 1] = buff;
	}
	
	int* sorted = new int[size];
	count = 0;
	for (int k = 0; k < size; k++)
	{
		
		sorted[count] = sort.find(edges[k]);
		count++;
	}

	int **prev ;
	prev = new int* [size];
	for (int i = 0; i < size; ++i)
		prev[i] = new int[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			prev[i][j] = g.mat[i][j];
		}
	}
	count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			g.mat[i][j] = prev[sorted[count]][j];
			
		}
		count++;
	}
	cout << "Sorted:\n";
	print(g.mat, g.count_tops);
	for (size_t i = 0; i < size; i++)
	{
		cout << "x" << sorted[i] << endl;
	}
}


void task2()
{
	int g1 = 0;
	int type;
	int read;
	lFile sort;
	ifstream in("Grafs1.txt", ios::binary);

	in.read((char*)&g1, sizeof(g1));
	in.read((char*)&type, sizeof(type));
	Graf g(g1, type);
	for (int i = 0; i < g1; i++)
	{
		for (int j = 0; j < g1; j++)
		{
			in.read((char*)&read, sizeof(read));
			g.mat[i][j] = read;
		}
	}
	in.close();
	int size = g.count_tops;
	cout << "Unsorted:\n";
	print(g.mat, g.count_tops);

	double** length = new double *[size];
	for (int i = 0; i < size; i++)
	{
		length[i] = new double[size];
	}
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			length[i][j] = rand() % 100;
		}
	}
	double* all_length = new double[size];

	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += length[i][j];
		}
		all_length[i] = sum;
		sum = 0;
	}
	for (int i = 0; i < size; i++)
	{
		cout <<"Length x"<<i<<" : " << all_length[i] << endl;
	}
	Top d;
	for (int i = 0; i < size; i++)
	{
		d.name = i;
		d.count = all_length[i];
		sort.push_back(d);
	}

	
	cout << endl;
		int i, j;
		bool swapped;
		for (i = 0; i < size - 1; i++)
		{
			swapped = false;
			for (j = 0; j < size - i - 1; j++)
			{
				if (all_length[j] > all_length[j + 1])
				{
					swap(all_length[j], all_length[j + 1]);
					swapped = true;
				}
			}
			if (swapped == false)
				break;
		}

		int* sorted = new int[size];
		 int count = 0;
		for (int k = 0; k < size; k++)
		{

			sorted[count] = sort.find(all_length[k]);
			count++;
		}

		int** prev;
		prev = new int* [size];
		for (int i = 0; i < size; ++i)
			prev[i] = new int[size];
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				prev[i][j] = g.mat[i][j];
			}
		}
		count = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{

				g.mat[i][j] = prev[sorted[count]][j];

			}
			count++;
		}
		cout << "Sorted:\n";
		print(g.mat, g.count_tops);
		
		sort.print_v2(all_length, size);

}
void swapEl(int* arr, int i)
{
	int buff;
	buff = arr[i];
	arr[i] = arr[i - 1];
	arr[i - 1] = buff;
}

int foo(Coor x)
{
	return x.x+x.y;
}
void task3(int foo(Coor))
{
	int g1 = 0;
	int type;
	int read;
	lFile sort;
	ifstream in("Grafs1.txt", ios::binary);

	in.read((char*)&g1, sizeof(g1));
	in.read((char*)&type, sizeof(type));
	Graf g(g1, type);
	for (int i = 0; i < g1; i++)
	{
		for (int j = 0; j < g1; j++)
		{
			in.read((char*)&read, sizeof(read));
			g.mat[i][j] = read;
		}
	}
	in.close();
	int size = g.count_tops;
	cout << "Unsorted:\n";
	print(g.mat, g.count_tops);
	
	Coor* arr = new Coor[size];
	for (int i = 0; i < size; i++)
	{
		arr[i].x = rand() % 100;
		arr[i].y = rand() % 100;
		
	}
	int* sorted_arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		sorted_arr[i] = foo(arr[i]);
	}
	Top d;
	for (int i = 0; i < size; i++)
	{
		d.name = i;
		d.count = sorted_arr[i];
		sort.push_back(d);
	}
	sort.print_v3(sorted_arr,arr,size,foo);
	

	int leftMark = 1;
	int rightMark = size - 1;
	while (leftMark <= rightMark)
	{
		for (int i = rightMark; i >= leftMark; i--)
			if (sorted_arr[i - 1] > sorted_arr[i]) swapEl(sorted_arr, i);
		leftMark++;


		for (int i = leftMark; i <= rightMark; i++)
			if (sorted_arr[i - 1] > sorted_arr[i]) swapEl(sorted_arr, i);
		rightMark--;
	}

	int* sorted = new int[size];
	int count = 0;
	for (int k = 0; k < size; k++)
	{

		sorted[count] = sort.find(sorted_arr[k]);
		count++;
	}

	int** prev;
	prev = new int* [size];
	for (int i = 0; i < size; ++i)
		prev[i] = new int[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			prev[i][j] = g.mat[i][j];
		}
	}
	count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			g.mat[i][j] = prev[sorted[count]][j];
		}
		count++;
	}
	cout << "Sorted:\n";
	print(g.mat, g.count_tops);
	sort.print_v3(sorted_arr,arr, size,foo);

}
int main()
{
	setlocale(LC_ALL, "rus");
	//fill();
	//task1();
	//task2();
	//task3(foo);
	system("pause");
	return 0;
}