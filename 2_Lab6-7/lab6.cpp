#include<iostream>
#include<cmath>
#include <fstream>

using namespace std;

enum Type
{
	full, path, tree = path, cycle
};
struct Graf
{
	Graf()
	{
	

		this->count_tops =0;
	}
	
	Graf(int count_tops, int type)
	{
		mat = new int* [count_tops];
		for (int i = 0; i < count_tops; ++i)
			mat[i] = new int[count_tops];

		this->type = type;
		this->count_tops = count_tops;
	}
	int **mat;
	int type;
	int count_tops;


};
void fill()
{
	ofstream out("Grafs.txt", ios::binary | ios::app);
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

float ch_polu_full(int x ,int k,int n)
{
	float poly = 1;
	if (x < k)

	{ return 0; }

	for (int i = 1; i <= n; i++)
	{
		poly = poly*(x - i + 1);
	}
	return poly;
}
float ch_polu_path_tree(int x, int k, int n)
{
	return x * pow((x - 1), n - 1);
}
float ch_polu_cycle(int x, int k, int n)
{

	return pow((x - 1), n) + pow((-1), n) * (x - 1);
}
void lab6()
{
	int g1 = 0;
	int type;
	int read;
	ifstream in("Grafs.txt", ios::binary);

	while (!in.eof())
	{
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

	


	int x;
	cout << "Введите кiлькiсть кольорiв" << endl;
	cin >> x;
	int ch_num=0;
	
	for (int i = 0; i < g.count_tops; i++)
	{
		for (int j = 0; j < g.count_tops; j++)
		{
			if (g.mat[i][j]== 0&&i!=j)
			{
				ch_num++;
			}
	}
	}
	
	ch_num /= 2;
	if (ch_num == 0 && g.count_tops != 0)
	{
		ch_num = g.count_tops;
	}
	cout << "Хроматичне число графа = " << ch_num << endl;
	switch (g.type)
	{
	case full:
		cout << "Хроматичний многочлен графа = " << ch_polu_full(x, ch_num, g.count_tops) << endl;
		break;
	case path:
		cout << "Хроматичний многочлен графа = " << ch_polu_path_tree(x, ch_num, g.count_tops) << endl;
		break;
	case cycle:
		cout << "Хроматичний многочлен графа = " << ch_polu_cycle(x, ch_num, g.count_tops) << endl;
		break;
	default:
		break;
	}
	

	
	}
	in.close();


}

int main()
{
	setlocale(LC_ALL, "rus");
	//fill();
	lab6();
	system("pause");
	return 0;
}