const unsigned long maxshort = 65535L;
const unsigned long multiplier = 1194211693L;
const unsigned long adder = 12345L;
#define RANDOMNUMBER_H
#define QUEEN_H 
#include"time.h"
#include "stdlib.h"

#include <iostream>
using namespace std;

class RandomNumber{
public:    // 当前种子    
	unsigned long randSeed;
public:    // 构造函数,默认值0表示由系统自动产生种子    
	RandomNumber(unsigned long s = 0);    // 产生0 ~ n-1之间的随机整数    
	unsigned short Random(unsigned long n);    // 产生[0, 1) 之间的随机实数    
	double fRandom();
};

RandomNumber::RandomNumber(unsigned long s)//产生种子??
{
	if(s==0)
	{	
	randSeed=time(0);//用系统时间产生种子
	}
	else
	{
	randSeed=s;//由用户提供种子
	}
}

unsigned short RandomNumber::Random(unsigned long n)//产生0：n-1之间的随机整数??
{
	randSeed=multiplier*randSeed+adder;//线性同余式
	return (unsigned short)((randSeed>>16)%n);
}
double RandomNumber::fRandom(void)//产生[0,1)之间的随机实数??
{
	return Random(maxshort)/double(maxshort);
}

class Queen
{	
	friend bool nQueen(int);
	private:	
		bool Place(int k);             
		// 测试皇后k置于第x[k]列的合法性	
		bool Backtrack(int t);         
		// 解n后问题的回溯法	
		bool QueensLV(int stopVegas);  
		// 随机放置n个皇后拉斯维加斯算法	
		int n, *x, *y;
}; 

bool Queen::Place(int k){    
	// 测试皇后k置于第x[k]列的合法性    
	for(int j = 1; j < k; ++ j)        
	if((abs(k-j) == abs(x[j]-x[k])) || (x[j]==x[k]))
		return false;    
		return true;
} 

bool Queen::Backtrack(int t)
{     // 解n后问题的回溯法    
	if(t > n)
	{        
		for(int i=1; i<=n; ++i)            
		y[i] = x[i];        
		return true;    
		}
	else       
		for(int i=1; i<=n; ++i)
		{           
			x[t] = i;           
			if(Place(t) && Backtrack(t+1))                
			return true;       
			}    
		return false;
}

bool Queen::QueensLV(int stopVegas){     
	// 随机放置n个皇后的拉斯维加斯算法     
	RandomNumber rnd;    // 随机数产生器     
	int k = 1;           // 下一个放置的皇后编号     
	int count = 1;     // 1 <= stopVegas <= n 表示允许随机放置的皇后数     
	while((k <= stopVegas) && (count > 0)){         
		count = 0;         
		for(int i = 1; i<=n; ++i)      // ----------- ①         
		{             
			x[k] = i;             
			if(Place(k))                
				y[count++] = i;         
		}         
		if(count > 0)                   // -------------②             
			x[k++] = y[rnd.Random(count)];   // 随机位置     
	}     
	return (count > 0);   // count > 0表示放置位置成功
}


bool nQueen(int n){     
	// 与回溯法结合的解n后问题的拉斯维加斯算法     
	Queen X;    // 初始化X    
	X.n = n;    
	int *p = new int[n+1];    
	int *q = new int[n+1];    
	for(int i=0; i<=n; ++i)
	{       
		p[i] = 0;       
		q[i] = 0;    
	}   
	X.y = q;    
	X.x = p;   // 设置随机放置皇后的个数    
	int stop = 8;    
	if(n > 15)      
		stop = n-15;    
	bool found = false;    
	while(! X.QueensLV(stop));     // 算法的回溯搜索部分   
		if(X.Backtrack(stop+1)){       
			for(int i=1; i<=n; ++i)       
				cout << p[i] << " ";       
				found = true;    
				}    
		cout << endl;    
	delete [] p;    
	delete [] q;    
	return found;
}

int main(){    
	nQueen(8);
	return 0; 
}

