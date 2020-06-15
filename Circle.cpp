#include <iostream>//Ԥ����
#include <math.h>
#define N 100  //�궨��
using namespace std;

void Swap(float& a, float& b)//��������ֵ
{
	int temp = a;
	a = b;
	b = temp;
}

class Circle
{
	friend float CirclePerm(int, float*);//�����Ѻ���
public:
	float Center(int t);//���㵱ǰ��ѡ���Բ�ڵ�ǰԲ������Բ�ĵĺ�����
	void Compute();//���㵱ǰԲ���еĳ���
	void Backtrack(int t);
	float min,	//��ǰ����ֵ
		  *x,   //��ǰԲ����Բ�ĺ�����
		  *r;   //��ǰԲ����
	int n;      //�����е�Բ�ĸ���
};

//����ֵ����ǰҪ���е�Բ�İ뾶
//���ֵ����ǰ��ѡԲ��Բ�ĺ�����
//���ã����㵱ǰ��ѡ��Բ��Բ�ĺ�����
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


//����ֵ����ǰ����Բ�ĺ�����Ͱ뾶
//���ֵ����ǰ����Բ���еĳ���
//����:���㵱ǰԲ���еĳ���
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

//����ֵ��1
//���ֵ����ǰԲ���е�����ֵ
//���ã����ҵ�ǰ����ֵ
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
			if (centerx + r[t] + r[1] < min)//�½�Լ��
			{
				x[t] = centerx;
				Backtrack(t + 1);
			}
			Swap(r[t], r[j]);
		}
	}
}

//����ֵ��n,a
//���ֵ����ǰ�ҵ���Բ����С����
//���ã������ҵ�����СԲ���г���
float CirclePerm(int n, float *a)
{
	Circle X;
	X.n = n;
	X.r = a;
	X.min = 100000;
	float *x = new float[n + 1];//����ռ�
	X.x = x;
	X.Backtrack(1);
	delete[]x;//�ͷſռ�
	return X.min;
}

//����ֵ����
//���ֵ��Բ���е���С����
//���ã����ø����ӳ�����������������ҳ���С����
int main()
{
	float a[N],k;
	int m, n;
	cout << "������Բ�ĸ���Ϊ��";
	cin >> n;
	cout << "��ֱ�����Բ�İ뾶��"<<endl;
	for (m = 1; m <= n; m++)
		cin >> a[m];
	cout << "��СԲ���г���Ϊ��";
	cout << CirclePerm(n, a) << endl;
	return 0;
}








