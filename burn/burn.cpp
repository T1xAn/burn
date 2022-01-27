
#include <stdio.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include <iomanip>

using namespace std;
#define inf 1e8
	
struct line {
	pair <int, int> s;
	pair <int, int> e;
	double time;
};


//void trash() {
//int *size = new int;
//	cout << endl << "Enter match num - ";
//	cin >> *size ;
//
//	vector <int> *arr = new vector <int> [*size];
//	/*for (int count = 0; count < *size; ++count)
//		arr[count] = new int[*size];*/
//	//vector <int> arr(*size);
//	int min = -1;
//	int max = 1;
//	for (int row = 0; row < *size; row++) {
//		int min = -1;
//			int x1 = min + rand()%((max + 1) - min); // для у ранжомить число от -1 до 1 и соответсвенно x прибавлять полученное число
//
//			//int buff = rand() % 3 - 1;
//
//
//
//			int Yzero = x1;
//			int y1 = (Yzero-1) + rand()%((Yzero)-(Yzero - 1)); // записывать напрямую в структуру и при проверке сравнивать сразу начало и конец спички
//			while (1) {
//				int x2 = min + rand() % ((max + 1) - min);
//				int Yzero = x2;
//				int y2 = (Yzero - 1) + rand() % ((Yzero)-(Yzero - 1));
//			}
//			//int time = rand()%200;
//			arr[row].push_back(x1);
//			arr[row].push_back(y1);
//			//arr[row].push_back(time);
//			for(int i= 0; i< 2 ;i++)
//			cout << arr[row].at(i) << " ";
//			cout << endl;
//			//найти минимум и максимум у X и Y, если они обновились, то увеличить или уменьшить максимум на 1
//	}
//
//	/*	vector <int> a = {12, 21};
//		vector <int> b = { 12, 21 };
//		if (a == b) {
//			cout << "cunt";
//				return;
//		}
//		cout << "Красава";*/
//
//	struct line** match = new line * [*size];
//	for (int count = 0; count < *size; ++count)
//		match[count] = new line;
//
//	int buff;
//	for (int i = 0; i < *size; i++) {
//		for (int j = 0; j < 5; j++) {
//			//fin >> buff;
//			match[0]->s.push_back(buff);
//		}
//	}
//}
//
 
void main() {
	//auto p1 = (find(points.begin(), points.end(), make_pair(x1, x2)) - points.begin());
	//trash();
	ifstream fin("f.in");
	if (!fin.is_open()) {
		cout << endl << "File can not be opend";
		return;
	}

	int size;
	fin >> size;

	struct line** hline = new line * [size*2];
		for (int count = 0; count < size*2; ++count)
			hline[count] = new line;
	
		int line_num = 0;

		vector <pair <int, int>> points;
		for (int i = 0; i < size; i++) {
			int x1, y1, x2, y2, xm, ym;
			float t;

			fin >> x1 >> y1 >> x2 >> y2 >> t;
			x1 *= 2;
			x2 *= 2;
			y1 *= 2;
			y2 *= 2;
			t /= 2;

			xm = (x1 + x2) / 2;
			ym = (y1 + y2) / 2;

			int p, p1, p2, pm;
			

			p = find(points.begin(), points.end(), make_pair(x2, x2)) - points.begin();
				if (p == points.size()) points.push_back({ x2,y2 });
			p2 = p;
			p = find(points.begin(), points.end(), make_pair(xm, xm)) - points.begin();
				if (p == points.size()) points.push_back({ xm,ym });
			pm = p;
			p = find(points.begin(), points.end(), make_pair(x1, x1)) - points.begin();
				if (p == points.size()) points.push_back({ x1,y1 });
			p1 = p;

			

		hline[line_num]->s = make_pair (x1, y1);
		hline[line_num]->e = make_pair(xm, ym);
		hline[line_num]->time = t;
		line_num++;
		hline[line_num]->s = make_pair(xm, ym);
		hline[line_num]->e = make_pair(x2, y2);
		hline[line_num]->time = t;
		line_num++;
	}

	for (int i = 0; i < size * 2; i++) {
		cout << hline[i]->s.first << " " << hline[i]->s.second << " " << hline[i]->e.first << " " << hline[i]->e.second << " " <<  hline[i]->time << endl;
	}

	// кусок говнокода

	double ** range = new double * [size * 2];
	for (int count = 0; count < size * 2; ++count)
		range[count] = new double;

	for (int i = 0; i < size * 2; i++) {
		for (int j = 0; j < size * 2; j++) {
			if (i == j)
				range[i][j] = 0;
			else
				range[i][j] = inf;
		}
	}
		

	for (int i = 0; i < size * 2; i++) {

	}

	/*int** arr = new int* [size];
	for (int count = 0; count < size; ++count)
		arr[count] = new int[5];

	cout << endl << size << endl;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 5; j++) {
			fin >> arr[i][j];
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
}