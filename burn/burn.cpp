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
	struct line** hline = new line * [size*2];
		for (int count = 0; count < size*2; ++count)
			hline[count] = new line;
	int line_num = 0;
	vector <pair <int, int>> points;
		for (int i = 0; i < size; i++) {
			int x1, y1, x2, y2, xm, ym;
			double t;
			fin >> x1 >> y1 >> x2 >> y2 >> t;
			x1 *= 2; x2 *= 2; y1 *= 2; y2 *= 2; t /= 2;
			xm = (x1 + x2) / 2;
			ym = (y1 + y2) / 2;

			int p, p1, p2, pm;
			p = find(points.begin(), points.end(), make_pair(x2, y2)) - points.begin();
			if (p == points.size())  points.push_back({ x2,y2 }); 
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
	fin.close();

	double ** arr = new double * [points.size()];
	for (int count = 0; count < points.size(); ++count)
		arr[count] = new double[points.size()];
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size(); j++) {
			if (i == j) arr[i][j] = 0;
			else arr[i][j] = inf;
		}
	}

	for (int count = 0; count < points.size(); count++) {
		for (int i = 0; i < points.size(); i++) {
			bool stop = false;
			for (int j = 0; j < line_num; j++) {
				if (arr[count][hline[j]->s] + hline[j]->time < arr[count][hline[j]->e]) {
					arr[count][hline[j]->e] = arr[count][hline[j]->s] + hline[j]->time;
					stop = true;
				}
				if (arr[count][hline[j]->e] + hline[j]->time < arr[count][hline[j]->s]) {
					arr[count][hline[j]->s] = arr[count][hline[j]->e] + hline[j]->time;
					stop = true;
				}
			}
			if (!stop) break;
		}
	}

	int cords;
	double max = 0 , min = inf; 
	for (int count = 0; count < points.size(); count++) {
		if (points[count].first % 2 == 0 && points[count].second % 2 == 0) {
			max = 0;
			for (int i = 0 ; i < line_num; i++) {
				double time = hline[i]->time;
				double ts = arr[count][hline[i]->s];
				double te = arr[count][hline[i]->e];
				if (ts > te) swap(ts, te);
				time = ts + (te - ts) + (time - (te - ts)) / 2;
				if (time > max) max = time;
			}
			if (min >= max) { min = max; cords = count; }
		}
	 }
	ofstream fon("f.out");
	fon.setf(ios::fixed);
	fon << points[cords].first / 2 << " " << points[cords].second /2 << endl << setprecision(3) << min;
	fon.close();
}