//LinearEqu.h  文件二，LinearEqu类定义
#ifndef _LINEAR_EQU_H
#define _LINEAR_EQU_H
#include "Matrix.h"
#include "vector"
class LinearEqu: public Matrix {	//公有派生类LinearEqu定义
public:	//外部接口
	LinearEqu(int size = 2);	//构造函数
	~LinearEqu();	//析构函数
	//方程赋值
	void setLinearEqu(const double *a, const double *b);
	bool solve();	//全选主元高斯消去法求解方程
	void printLinearEqu() const;	//显示方程
	void printSolution() const;	//显示方程的解
private:	//私有数据
	std::vector<double> sums;	//方程右端项
	std::vector<double> solution;	//方程的解
};
#endif //_LINEAREQU_H
