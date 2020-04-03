#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

// class definition of MyVector
struct TwoInt
{
	int i;
	int j;
};
class MyVector
{
friend const MyVector operator+(const MyVector& v, double d);
friend istream&operator>>(istream& in, MyVector& v);
private:
  int n; 
  double* m; 
public:
  MyVector();
  MyVector(int n, double m[]);  
  MyVector(const MyVector& v);
  ~MyVector();
  void print() const; 
  
  bool operator==(const MyVector& v) const;
  bool operator!=(const MyVector& v) const;
  bool operator<(const MyVector& v) const;
  double operator[](char* c) const;
  double& operator[](int i);
  double operator[](TwoInt num) const;
  const MyVector& operator=(const MyVector& v);
  const MyVector& operator+=(const MyVector& v);
  const MyVector operator+(const MyVector& v)const;
  
};
// end of class definition of MyVector

// global function headers

istream& operator>>(istream& in, MyVector& v);




// MyVector's instance functions
MyVector::MyVector(): n(0), m(NULL) 
{
}
MyVector::MyVector(int n, double m[])
{
  this->n = n;
  this->m = new double[n];
  for(int i = 0; i < n; i++)
    this->m[i] = m[i];
}
MyVector::MyVector(const MyVector& v)
{
  this->n = v.n;
  this->m = new double[n];
  for(int i = 0; i < n; i++)
    this->m[i] = v.m[i];	
}
MyVector::~MyVector() 
{ 
  delete [] m; 
}
void MyVector::print() const 
{
  cout << "(";
  for(int i = 0; i < n - 1; i++)
    cout << m[i] << ", ";
  cout << m[n-1] << ")\n";
}
// end of MyVector's instance functions

// MyVector's overloaded operators
bool MyVector::operator==(const MyVector& v) const
{
  if(this->n != v.n)
    return false;
  else
  {
    for(int i = 0; i < n; i++)
    {
      if(this->m[i] != v.m[i])
      return false;
    }
  }	
  return true;
}
bool MyVector::operator!=(const MyVector& v) const
{
  return !(*this == v);
}
bool MyVector::operator<(const MyVector& v) const
{
  if(this->n != v.n)
    return false;
  else
  {
  	for(int i = 0; i < n; i++)
  	{
  	  if(this->m[i] >= v.m[i])
  	    return false;
  	}
  }	
  return true;
}
double MyVector::operator[](char* c) const
{
  char* mark = NULL;
  mark = strchr(c , ':');
  int a = 0, b =0;
  
  for(int i = 0; i < (mark - c); i++ )
  	{ 
	  a =( c[i]-48) * pow(10, (mark - c) - i - 1);
    }
    
  for(int i = mark - c + 1; i < strlen(c) ; i++)
	{
		b = (c[i]-48) * pow(10, strlen(c)-(mark-c)-i);
	}
	
  if(a > b || b > n || a > n || a < 0 || b < 0)
  	return 0;
  else
  {
  	double sum = 0;
  	for(int i = a; i < b + 1; i++){
  		sum += this -> m[i];
	  }
	return sum ;
  }
  
}

double MyVector::operator[](TwoInt num) const
{
	int a = 0;
	int b = 0;
	a = num.i;
	b = num.j;
	
	if(a > b || b > n || a > n || a < 0 || b < 0)
  		return 0;
  	else
  {
  	double sum = 0;
  	for(int i = a; i < b + 1; i++){
  		sum += this -> m[i];
	  }
	return sum ;
  }
	
}

double& MyVector::operator[](int i) 
{
  if(i < 0 || i >= n)
    exit(1);
  return m[i];
}
const MyVector& MyVector::operator=(const MyVector& v)
{
  if(this != &v)
  {
    if(this->n != v.n)
    {
      delete [] this->m;
      this->n = v.n;
      this->m = new double[this->n];
    }
    for(int i = 0; i < n; i++)
      this->m[i] = v.m[i];
  }  
  return *this;
}
const MyVector& MyVector::operator+=(const MyVector& v)
{
  if(this->n == v.n)
  {
    for(int i = 0; i < n; i++)
      this->m[i] += v.m[i]; 
  }
  return *this;
}
// end of MyVector's overloaded operators

// global functions

const MyVector MyVector ::operator+(const MyVector& v)const
{
	MyVector sum(*this);
	int max=0;
	int min=0;
	if(this->n >= v.n)
		{
		 min=v.n;
		 max=this->n;
		 for(int i=min;i<max;i++)
		 {
		 	v.m[i]=v.m[i-min];
		 }
		 for(int i=0;i<max;i++)
		 { 
		 	sum.m[i]+=v.m[i];
		 }
		}
	else
		{
		 max=v.n;
		 min=this->n;
		 for(int i=min;i<max;i++)
		 {
		 	sum.m[i]=sum.m[i-min];
		 }
		 for(int i=0;i<max;i++)
		 { 
		 	sum.m[i]+=v.m[i];
		 }
		}
		
		return sum;
}

istream&operator>>(istream& in, MyVector& v)
{
	char newone[10000] = {0};
	int times = 1;
	
	cin>>newone;
	
	for(int i = 0;i < 10000;i ++)
	{
		if(newone[i] == ',')
			times ++;
	}
	
	v.n = times ;
	
	delete [] v.m;
	v.m = new double[v.n];
	
	char* marks = NULL;
	
	marks = strtok(newone , "<,>");
	int runtime = 0;
	
	while(marks != NULL)
	{
		v.m[runtime] = atoi(marks);
		runtime ++;
		marks = strtok(NULL , "<,>");
	}
	
	
	return in;
}
// end of global functions
// ===========================================================================

int main(){
	double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MyVector u(5, d);
	cin >> u;
	u.print();
	return 0;
}
