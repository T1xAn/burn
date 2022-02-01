#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
#define inf 1e8
struct line {
	int s;
	int e;
	double time;
};

void main() {
	ifstream fin("f.in");
	if (!fin.is_open()) {
		cout << endl << "File can not be opend";
		return;
	}
	int size;
	fin >> size;

	struct line** hline = new line * [size*2];		// структура, содержащая информация о спичках (координаты начала и конца спички и время горения)
		for (int count = 0; count < size*2; ++count)
			hline[count] = new line;
	int line_num = 0;
	vector <pair <int, int>> points;		// вектор координат точек фигуры
		for (int i = 0; i < size; i++) {
			int x1, y1, x2, y2, xm, ym;
			double t;
			fin >> x1 >> y1 >> x2 >> y2 >> t;	
			x1 *= 2; x2 *= 2; y1 *= 2; y2 *= 2; t /= 2;	 
			xm = (x1 + x2) / 2;		// деление спичек на половину, для упрощения дальнейших подсчётов 
			ym = (y1 + y2) / 2;		// сохранение координат середины считанной из файла спички

			int p, p1, p2, pm;
			p = find(points.begin(), points.end(), make_pair(x2, y2)) - points.begin(); // Проверка на наличие считанных координат в векторе точек, 
			if (p == points.size())  points.push_back({ x2,y2 });						// при их отсутствии добавление их в конец вектора (p1, p2, pm
			p2 = p;																		// соответвуют порядковому номеру координат в векторе)
			p = find(points.begin(), points.end(), make_pair(xm, ym)) - points.begin();
				if (p == points.size()) points.push_back({ xm,ym });
			pm = p;
			p = find(points.begin(), points.end(), make_pair(x1, y1)) - points.begin();
				if (p == points.size()) points.push_back({ x1,y1 });
			p1 = p;

		hline[line_num]->s = p1; // запись в структуру информации о первой половине спички (время преждевременно поделено на 2)
		hline[line_num]->e = pm;
		hline[line_num]->time = t;
		line_num++;

		hline[line_num]->s = pm; // запись в струкутру информации о второй половине спички 
		hline[line_num]->e = p2;
		hline[line_num]->time = t;
		line_num++;
	}
	fin.close();

	double ** arr = new double * [points.size()];	// выделение памяти под матрицу кратчайших расстояний для "графа" спичек
	for (int count = 0; count < points.size(); ++count)
		arr[count] = new double[points.size()];
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size(); j++) { 
			if (i == j) arr[i][j] = 0;
			else arr[i][j] = inf;
		}
	}

	for (int count = 0; count < points.size(); count++) { // поиск кратчайших расстояний в графе из полуспичек с помощью алгоритма форда-беллмана
		for (int i = 0; i < points.size(); i++) {
			bool stop = false;							  // переменная stop используется для ускорения алгоритма (если на какой то итерации цикла не   
			for (int j = 0; j < line_num; j++) {		  // произведено ни одно улучшение кратчайшего расстояния то дальнейшие итерации цикла бессмысленны
				if (arr[count][hline[j]->s] + hline[j]->time < arr[count][hline[j]->e]) { // поэтому если переменная остаётся = false, он прерывается)
					arr[count][hline[j]->e] = arr[count][hline[j]->s] + hline[j]->time;
					stop = true;
				}
				if (arr[count][hline[j]->e] + hline[j]->time < arr[count][hline[j]->s]) { // т.к данный поиск работает с ориентированными графами добавлено
					arr[count][hline[j]->s] = arr[count][hline[j]->e] + hline[j]->time;	  // второе условие проверки, но с переменой мест 
					stop = true;														  // "начала и конца линии" для имитации ориентированности графа
				}
			}
			if (!stop) break;
		}
	}

	int cords;
	double max = 0 , min = inf;  // поиск и улучшение максимального времени за которое может сгореть фигура относительно каждой точки
	for (int count = 0; count < points.size(); count++) {
		if (points[count].first % 2 == 0 && points[count].second % 2 == 0) { // т.к фигуру можно поджигать только в углах "клеток" есть смысл считать
			max = 0;														 // оптимальное время только для подобных точек
			for (int i = 0 ; i < line_num; i++) {
				double time = hline[i]->time;
				double ts = arr[count][hline[i]->s];
				double te = arr[count][hline[i]->e];
				if (ts > te) swap(ts, te);		// если  время начала горения "начала" больше времени начала "конца" спички, перемена их местами 
				time = ts + (te - ts) + (time - (te - ts)) / 2; // универсальная формула для подсчёта времени сгорания спички, 1. если спичка сгорела
				if (time > max) max = time;	// к моменту времени te то кратчайшее время приравнивается te 2.если спичка начала гореть с обоих концов
			}// одновременно то время гороения сокращается вдвое 3.если не одновременно то ищется момента времени в который спичка загорается с обоих концов  
			if (min >= max) { min = max; cords = count; } // поиск минимального времени из всех максимальных каждой точки, запись соответсвующих координат
		}
	 }
	for (int count = 0; count < points.size(); ++count)
		delete[] arr[count];
	delete[] arr;
	for (int count = 0; count < line_num; ++count)
		delete[] hline[count];
	delete[] hline;
	ofstream fon("f.out");
	fon.setf(ios::fixed);
	fon << points[cords].first / 2 << " " << points[cords].second /2 << endl << setprecision(3) << min;
	fon.close();
}