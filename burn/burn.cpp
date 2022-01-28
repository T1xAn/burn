
#include <stdio.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include <iomanip>

using namespace std;
#define inf 1e8
	
struct line {
	int s;
	int e;
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
	ifstream fin("f.in");
	if (!fin.is_open()) {
		cout << endl << "File can not be opend";
		return;
	}

	int size;
	fin >> size;

	struct line** hline = new line * [size*4];
		for (int count = 0; count < size*4; ++count)
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
			
			p = find(points.begin(), points.end(), make_pair(x2, y2)) - points.begin();
				if (p == points.size()) points.push_back({ x2,y2 });
			p2 = p;
			p = find(points.begin(), points.end(), make_pair(xm, ym)) - points.begin();
				if (p == points.size()) points.push_back({ xm,ym });
			pm = p;
			p = find(points.begin(), points.end(), make_pair(x1, y1)) - points.begin();
				if (p == points.size()) points.push_back({ x1,y1 });
			p1 = p;

		hline[line_num]->s = p1;
		hline[line_num]->e = pm;
		hline[line_num]->time = t;
		line_num++;

		hline[line_num]->s = pm;
		hline[line_num]->e = p2;
		hline[line_num]->time = t;
		line_num++;
	}

	/*for (int i = 0; i < size * 2; i++) {
		cout << hline[i]->s << " "  << hline[i]->e << " " <<  hline[i]->time << endl;
	}*/

	double ** arr = new double * [size * 2];
	for (int count = 0; count < size * 2; ++count)
		arr[count] = new double;

	//double arr[6][6];

	for (int i = 0; i < size * 2; i++) {
		for (int j = 0; j < size * 2; j++) {
			if (i == j)
				arr[i][j] = 0;
			else
				arr[i][j] = inf;
		}
	}
		// со stop тоже работает, но хз быстрее или нет

	for (int count = 0; count < size * 2; count++) {
		for (int i = 0; i < size * 2; i++) {
			//bool stop = false;
			for (int j = 0; j < line_num; j++) {
				if (arr[count][hline[j]->s] + hline[j]->time < arr[count][hline[j]->e])
					arr[count][hline[j]->e] = arr[count][hline[j]->s] + hline[j]->time;
				if (arr[count][hline[j]->e] + hline[j]->time < arr[count][hline[j]->s])
					arr[count][hline[j]->s] = arr[count][hline[j]->e] + hline[j]->time;
				//stop = true;
			}
			//if (!stop) break;
		}
	}

	//for (int i = 0; i < size * 2; i++) {
	//	for (int j = 0; j < size * 2; j++) {
	//		cout << arr[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	// кусок говнокода
	int cords;
	double max = 0; 
	double min = inf;
	for (int count = 0; count < points.size(); count++) {
		int i = 0;
		if (points[count].first % 2 == 0 && points[count].second % 2 == 0) {
			cords = count;
			max = 0;
			for (i ; i < line_num; i++) {
				double time = hline[i]->time;
				double ts = arr[count][hline[i]->s];
				double te = arr[count][hline[i]->e];
				if (ts > te) swap(ts, te);
				if (te = ts + time) time = te;  //continue;
				if (ts - te == 0)  time = time / 2;
				if(ts-te != 0) time = ts - (time - te - ts) / 2;
				if (time > max) max = time;
			}
			if (min >= max) min = max; cords = count;
		}

	 }

	cout << points[cords].first << " " << points[cords].second << endl << max;
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
	return;
}