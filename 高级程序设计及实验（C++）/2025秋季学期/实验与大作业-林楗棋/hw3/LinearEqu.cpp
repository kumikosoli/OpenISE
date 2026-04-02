//LinearEqu.cpp  文件四，LinearEqu类实现
#include "LinearEqu.h"	//包含类的定义头文件
#include <iostream>
#include <cmath>
using namespace std;
LinearEqu::LinearEqu(int size/* = 2 */) : Matrix(size) {	//用size调用基类构造函数
	sums.resize(size);	//为派生类数据成员分配内存
	solution.resize(size);
}
LinearEqu::~LinearEqu()	{ //派生类LinearEqu的析构函数
	sums.clear();	//释放内存
	solution.clear();
	//会自动调用基类析构函数
}
void LinearEqu::setLinearEqu(const double *a, const double *b) {	//设置线性方程组
	setMatrix(a);	//调用基类函数
	for(int i = 0; i < getSize(); i++)
		sums[i] = b[i];
}
void LinearEqu::printLinearEqu() const {//显示线性方程组
	cout << "The Line eqution is:" << endl;
	for (int i = 0; i < getSize(); i++) {
		for (int j = 0; j < getSize(); j++)
			cout << element(i, j) << " ";
			cout << "     " << sums[i] << endl;
		}
}
void LinearEqu::printSolution() const {//输出方程的解
	cout << "The Result is: " << endl;
	for (int i = 0; i < getSize(); i++)
		cout << "x[" << i << "] = " << solution[i] << endl;
}

inline void swap(double &v1, double &v2) {//交换两个实数
	double temp = v1;
	v1 = v2;
	v2 = temp;
}
bool LinearEqu::solve() {	//全选主元素高斯消去法求解方程
	int n = getSize();
	const double EPS = 1e-12;

	for (int k = 0; k < n; ++k) {
		// 在第 k 列中选取绝对值最大的主元行
		int pivot = k;
		double maxv = std::fabs(element(k, k));
		for (int i = k + 1; i < n; ++i) {
			double v = std::fabs(element(i, k));
			if (v > maxv) { maxv = v; pivot = i; }
		}
		// 如果主元接近 0，则矩阵奇异或方程无唯一解
		if (maxv < EPS) return false;

		// 交换当前行和主元行
		if (pivot != k) {
			for (int j = 0; j < n; ++j)
				swap(element(k, j), element(pivot, j));
			swap(sums[k], sums[pivot]);
		}

		double akk = element(k, k);
		for (int i = k + 1; i < n; ++i) {
			double factor = element(i, k) / akk;
			for (int j = k; j < n; ++j)
				element(i, j) -= factor * element(k, j);
			sums[i] -= factor * sums[k];
		}
	}

	// 回代求解
	for (int i = n - 1; i >= 0; --i) {
		double s = sums[i];
		for (int j = i + 1; j < n; ++j)
			s -= element(i, j) * solution[j];
		double aii = element(i, i);
		if (std::fabs(aii) < EPS) return false;
		solution[i] = s / aii;
	}
	return true;
}
