#include <iostream>//预编译
#include <math.h>
#define N 100  //宏定义
using namespace std;

void Swap(float& a, float& b)//交换两个值
{
	int temp = a;
	a = b;
	b = temp;
}

class Circle
{
	friend float CirclePerm(int, float*);//定义友好类
public:
	float Center(int t);//计算当前所选择的圆在当前圆排列中圆心的横坐标
	void Compute();//计算当前圆排列的长度
	void Backtrack(int t);
	float min,	//当前最优值
		  *x,   //当前圆排列圆心横坐标
		  *r;   //当前圆排列
	int n;      //待排列的圆的个数
};

//传入值：当前要排列的圆的半径
//输出值：当前所选圆的圆心横坐标
//作用：计算当前所选择圆的圆心横坐标
float Circle::Center(int t)
{
	float temp = 0;
	for (int j = 1; j < t; j++)
	{
		float valuex = x[j] + 2.0 * sqrt(r[t] * r[j]);
		if (valuex > temp)
			temp = valuex;
	}
	return temp;
}


//传入值：当前搜索圆的横坐标和半径
//输出值：当前搜索圆排列的长度
//作用:计算当前圆排列的长度
void Circle::Compute(void)
{
	float low = 0, high = 0;
	for (int i = 1; i <= n; i++)
	{
		if (x[i] - r[i] < low)
			low = x[i] - r[i];
		if (x[i] + r[i] > high)
			high = x[i] + r[i];
	}
	if (high - low < min)
		min = high - low;
}

//传入值：1
//输出值：当前圆排列的最优值
//作用：查找当前最优值
void Circle::Backtrack(int t)
{
	if (t > n)
		Compute();
	else
	{
		for (int j = t; j <= n; j++)
		{
			Swap(r[t], r[j]);
			float centerx = Center(t);
			if (centerx + r[t] + r[1] < min)//下界约束
			{
				x[t] = centerx;
				Backtrack(t + 1);
			}
			Swap(r[t], r[j]);
		}
	}
}

//传入值：n,a
//输出值：当前找到的圆的最小长度
//作用：计算找到的最小圆排列长度
float CirclePerm(int n, float *a)
{
	Circle X;
	X.n = n;
	X.r = a;
	X.min = 100000;
	float *x = new float[n + 1];//申请空间
	X.x = x;
	X.Backtrack(1);
	delete[]x;//释放空间
	return X.min;
}

//传入值：无
//输出值：圆排列的最小长度
//作用：调用各个子程序，输出所有排列中找出最小长度
int main()
{
	float a[N],k;
	int m, n;
	cout << "请输入圆的个数为：";
	cin >> n;
	cout << "请分别输入圆的半径："<<endl;
	for (m = 1; m <= n; m++)
		cin >> a[m];
	cout << "最小圆排列长度为：";
	cout << CirclePerm(n, a) << endl;
	return 0;
}








