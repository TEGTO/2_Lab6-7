#include<iostream>
#include<cmath>
#include <fstream>

using namespace std;
struct Coor
{
	int x;
	int y;
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
	ofstream out("Grafs2.txt", ios::binary | ios::app);
	Graf Mas(3, 0);
	out.write((char*)&Mas.count_tops, sizeof(Mas.count_tops));
	out.write((char*)&Mas.type, sizeof(Mas.type));

	Mas.mat[0][0] = 0;
	Mas.mat[0][1] = 1;
	Mas.mat[0][2] = 1;
	Mas.mat[1][0] = 1;
	Mas.mat[1][1] = 0;
	Mas.mat[1][2] = 1;
	Mas.mat[2][0] = 1;
	Mas.mat[2][1] = 1;
	Mas.mat[2][2] = 0;
	for (int i = 0; i < Mas.count_tops; i++)
	{
		for (int j = 0; j < Mas.count_tops; j++)
		{
			out.write((char*)&Mas.mat[i][j], sizeof(Mas.mat[i][j]));
		}
	}
	out.close();
}
struct Data
{

	int count;
	int name;
	int name2=0;
};

struct lFile
{
	void push_back(Data data);


	void print();
	int find(int x);
	void print_v2(double* arr,int size);
	void print_v3(int* sorted,Coor* arr, int size, int foo(Coor));
	Data find_v2(int x);
private:

	int Size = 0;
	struct Node
	{
		Data data;
		Node* next = nullptr;
		Node* prev = nullptr;
		Node(Data data) { this->data = data; }
	};
	Node* head = nullptr;
	Node* tail = nullptr;

};
void lFile::push_back(Data data) {
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
			cout << "x" << iter->data.name << "| x=" << check.x << " " << "y=" << check.y <<" | f="<<foo(check) << endl;

		}
		
	}
}

Data lFile::find_v2(int x)
{
	Node* iter = head;
	while (iter->data.count != x)
	{
		if (iter->data.count == x)
		{
			return iter->data;
		}
		else iter = iter->next;
	}
	return iter->data;
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
void InsertSort(int edges[], int size)
{
	int buff = 0;
	int i, j;
	for (i = 1; i < size; i++)
	{
		buff = edges[i];


		for (j = i - 1; j >= 0 && edges[j] > buff; j--)
			edges[j + 1] = edges[j];

		edges[j + 1] = buff;
	}

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
	Data d;
	for (int i = 0; i < size; i++)
	{
		d.name = i;
		d.count = edges[i];
		sort.push_back(d);
	}
	
	sort.print();
	cout << endl;
	////////—ортировка ¬ставками/////
	InsertSort(edges, size);
	///////////////////////////////// мен€ент правый элемент на левый пока на дойдет до меньшего элемента  
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

void bubbleSort(double arr[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
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
	Data d;
	for (int i = 0; i < size; i++)
	{
		d.name = i;
		d.count = all_length[i];
		sort.push_back(d);
	}

	
	cout << endl;
	/////////////—ортировка пузырьком//////////// 
	bubbleSort(all_length, size);
		///////////////////////////////////////
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
void myShakerSort(int* arr, int size)
{
	int leftMark = 1;
	int rightMark = size - 1;
	while (leftMark <= rightMark)
	{
		for (int i = rightMark; i >= leftMark; i--)
			if (arr[i - 1] > arr[i]) swapEl(arr, i);
		leftMark++;


		for (int i = leftMark; i <= rightMark; i++)
			if (arr[i - 1] > arr[i]) swapEl(arr, i);
		rightMark--;

	}
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
	Data d;
	for (int i = 0; i < size; i++)
	{
		d.name = i;
		d.count = sorted_arr[i];
		sort.push_back(d);
	}
	sort.print_v3(sorted_arr,arr,size,foo);
	
	////////////—ортировка перемешиванием ////////
	myShakerSort(sorted_arr, size);
	/////////////////////////////////////// делает циклы в две стороны, постепенно сужа€ их, самый легкий в начало, самый т€желый в конец 
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
void QuickSort(int Array[], unsigned int N, int L, int R)
{
	int iter = L,
		jter = R;

	int middle = (R + L) / 2;

	int x = Array[middle];
	int w;

	do
	{
		while (Array[iter] < x)
		{
			iter++;
		}

		while (x < Array[jter])
		{
			jter--;
		}

		if (iter <= jter)
		{
			w = Array[iter];
			Array[iter] = Array[jter];
			Array[jter] = w;

			iter++;
			jter--;
		}
	} while (iter < jter);

	if (L < jter)
	{
		QuickSort(Array, N, L, jter);
	}

	if (iter < R)
	{
		QuickSort(Array, N, iter, R);
	}
}
void task4()
{
	int g1 = 0;
	int type;
	int read;
	lFile sort;
	ifstream in("Grafs2.txt", ios::binary);

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

	double** length = new double* [size];
	for (int i = 0; i < size; i++)
	{
		length[i] = new double[size];
	}
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (g.mat[i][j]!=0)
			{

				length[i][j] = rand() % 100;
			}
			else 
			{
				length[i][j] = 0;
			}
		
		}
	}

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			for (size_t k = 0; k < size; k++)
			{
				for (size_t l = 0; l < size; l++)
				{
					if (i+j == k+l&& k !=i&& l==i)
					{
						length[i][j] = length[k][l];
					}
				}
			}
			

		}
	}
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if(length[i][j]!=0)
			cout << "x" << i << j << "= " << length[i][j] << endl;
		}
	}
	int* long_length = new int[size * size];
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			long_length[count] = length[i][j];
			count++;
		}
	}
	Data d;
	count = 0;
	int h = 0;
	for (int i = 0; i < size*size; i++)
	{

		d.name = h;
		
		
		d.name2 = count;
		count++;
		if (count == size)
		{
			count = 0;
			h++;
		}
		d.count = long_length[i];
		sort.push_back(d);

	}
	
	cout << endl;

	///Ѕыстра€ сортировка////
	QuickSort(long_length, size*size, 0, size*size - 1);
	///////////////////////// выбераетс€ опорный элемент, делитс€ массив пополам, на лево меньшие , на право большие элементы от опорного и т.д. пока размер не будет <= 1 
	Data* sorted = new Data[size*size];
	 count = 0;
	for (int k = 0; k < size*size; k++)
	{

		sorted[count] = sort.find_v2(long_length[k]);
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

			g.mat[i][j] = prev[sorted[count].name][sorted[count].name2];
			count++;
		}
		
	}
	cout << "Sorted:\n";
	print(g.mat, g.count_tops);
	Coor *check= new Coor[size * size];
	int check_int = 0;
	count = 0;
	for (int i = 0; i < size * size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (long_length[i] == length[j][k]&& long_length[i]!=0)
				{
					for (int b = 0; b < size*size; b++)
					{
						if (j == check[b].x && k == check[b].y) check_int++;
					}
					if (check_int == 0)
					{
						cout << "x" << j << k << "=" << long_length[i] << endl;
						check[count].x = j; check[count].y = k;
						count++;
					}
					else check_int = 0;
				}
			}
		}
	}
}
void Merge(int* A, int first, int last)
{
	int middle, start, final, j;
	int* mas = new int[100];
	middle = (first + last) / 2; //вычисление среднего элемента
	start = first; //начало левой части
	final = middle + 1; //начало правой части
	for (j = first; j <= last; j++) //выполн€ть от начала до конца
		if ((start <= middle) && ((final > last) || (A[start] < A[final])))
		{
			mas[j] = A[start];
			start++;
		}
		else
		{
			mas[j] = A[final];
			final++;
		}
	//возвращение результата в список
	for (j = first; j <= last; j++) A[j] = mas[j];
	delete[]mas;
}
void MergeSort(int* A, int first, int last)
{
	{
		if (first < last)
		{
			MergeSort(A, first, (first + last) / 2); //сортировка левой части
			MergeSort(A, (first + last) / 2 + 1, last); //сортировка правой части
			Merge(A, first, last); //сли€ние двух частей
		}
	}
}
void task5(int foo(Coor))
{
	int g1 = 0;
	int type;
	int read;
	lFile sort;
	ifstream in("Grafs2.txt", ios::binary);

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

	Coor** length = new Coor* [size];
	for (int i = 0; i < size; i++)
	{
		length[i] = new Coor[size];
	}
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (g.mat[i][j] != 0)
			{

				length[i][j].x = rand() % 100;
				length[i][j].y = rand() % 100;
			}
			else
			{
				length[i][j].x = 0;
				length[i][j].y = 0;
			}

		}
	}

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			for (size_t k = 0; k < size; k++)
			{
				for (size_t l = 0; l < size; l++)
				{
					if (i + j == k + l && k != i && l == i)
					{
						length[i][j] = length[k][l];
					}
				}
			}


		}
	}
	int* long_length = new int[size * size];
	int count = 0;
	
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (length[i][j].x != 0&& length[i][j].y!=0)
				cout << "x" << i << j <<"| x=" << length[i][j].x <<" y=" << length[i][j].y << "| f result= " << foo(length[i][j]) << endl;
			long_length[count] = foo(length[i][j]);
			count++;
		}
	}
	Data d;
	count = 0;
	int h = 0;
	for (int i = 0; i < size * size; i++)
	{

		d.name = h;


		d.name2 = count;
		count++;
		if (count == size)
		{
			count = 0;
			h++;
		}
		d.count = long_length[i];
		sort.push_back(d);

	}
	///—ортировка сли€нием//// 
	MergeSort(long_length, 0, size*size - 1);
	///////////////////////// разбивает массив пополам, так до единицы, после в новый массив в начало идЄт меньшее число, и т.д., в конце сливает всЄ в один массив
	Data* sorted = new Data[size * size];
	count = 0;
	
	for (int k = 0; k < size * size; k++)
	{

		sorted[count] = sort.find_v2(long_length[k]);
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

			g.mat[i][j] = prev[sorted[count].name][sorted[count].name2];
			count++;
		}

	}
	cout << "Sorted:\n";
	print(g.mat, g.count_tops);
	Coor* check = new Coor[size * size];
	int check_int = 0;
	count = 0;
	for (int i = 0; i < size * size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (long_length[i] == foo(length[j][k]) && long_length[i] != 0)
				{
					for (int b = 0; b < size * size; b++)
					{
						if (j == check[b].x && k == check[b].y) check_int++;
					}
					if (check_int == 0)
					{
						cout << "x" << j << k << "| f result =" << long_length[i] << endl;
						check[count].x = j; check[count].y = k;
						count++;
					}
					else check_int = 0;
				}
			}
		}
	}
}
void ShellSort(int n, int mass[])
{
	int i, j, step;
	int tmp;
	for (step = n / 2; step > 0; step /= 2)
		for (i = step; i < n; i++)
		{
			tmp = mass[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < mass[j - step])
					mass[j] = mass[j - step];
				else
					break;
			}
			mass[j] = tmp;
		}
}
void task6()
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
	Data d;
	for (int i = 0; i < size; i++)
	{
		d.name = i;
		d.count = edges[i];
		sort.push_back(d);
	}

	sort.print();
	cout << endl;
	////////—ортировка Ўелла/////
	ShellSort(size, edges);
	////////////////////////////////// как метод втавки, но с шагами, каждый раз уменьша€ шаг
	int* sorted = new int[size];
	count = 0;
	for (int k = 0; k < size; k++)
	{

		sorted[count] = sort.find(edges[k]);
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
	for (size_t i = 0; i < size; i++)
	{
		cout << "x" << sorted[i] << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	//fill();
	//task1();
	//task2();
	//task3(foo);
	//task4();
	//task5(foo);
	//task6();
	system("pause");
	return 0;
}