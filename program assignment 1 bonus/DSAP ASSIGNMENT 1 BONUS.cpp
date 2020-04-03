#include <iostream>
#include <vector>

using namespace std;

class myv
{	
	private:
		int vec[100];
	
	public:
		int numCnt;
		char name;
		myv();
		~myv();
		myv& newv(char, int, int[]);
		myv& assign(int, int[]);
		bool compare(char, myv)const;
		myv& index(int, int);
		myv& sum(myv);
		myv& minus(myv);
};

myv::myv()
{
	int numCnt = 0;
}

myv::~myv()
{
}

myv& myv::newv(char name, int n, int num[])
{
	this->name = name;
	this->numCnt = n;
	for(int i = 0; i < n; i++)
	{
		this->vec[i] = num[i];
	}
}

myv& myv::assign(int n, int num[])
{
	for(int i = 0; i < this->numCnt; i++)
	{
		this->vec[i] = 0;
	}
	this->numCnt = n;
	for(int i = 0; i < n; i++)
	{
		this->vec[i] = num[i];
	}
	return *this;
}

bool myv::compare(char shurui, myv ushiro)const
{
	myv mae(*this);
	if(mae.numCnt != ushiro.numCnt)
	{
		int max, min = 0;
		if(mae.numCnt > ushiro.numCnt)
		{
			max = mae.numCnt;
			min = ushiro.numCnt;
			for(int i = min; i < max; i++)
			{
				ushiro.vec[i] = ushiro.vec[i - min];
			}
			
		}
		else
		{
			max = ushiro.numCnt;
			min = mae.numCnt;
			for(int i = min; i < max; i++)
			{
				mae.vec[i] = mae.vec[i - min];
			}
		}
		
		
	}
	if(shurui == 'E')
	{
		int times = 0;
		if(mae.numCnt > ushiro.numCnt)
			times = mae.numCnt;
		else
			times = ushiro.numCnt;
		for(int i = 0; i < times; i++)
		{
			if(mae.vec[i] != ushiro.vec[i])
				return false;
		}
		return true;
	}
	
	else if(shurui == 'L')
	{
		int times = 0;
		if(mae.numCnt > ushiro.numCnt)
			times = mae.numCnt;
		else
			times = ushiro.numCnt;
		for(int i = 0; i < times; i++)
		{
			if(mae.vec[i] > ushiro.vec[i])
				return false;
		}
		return true;
	}
	
	else if(shurui == 'G')
	{
		int times = 0;
		if(mae.numCnt > ushiro.numCnt)
			times = mae.numCnt;
		else
			times = ushiro.numCnt;
		for(int i = 0; i < times; i++)
		{
			if(mae.vec[i] < ushiro.vec[i])
				return false;
		}
		return true;
	}
}

myv& myv::index(int no, int num)
{
	this->vec[no - 1] = num;
}

myv& myv::sum(myv sum)
{
	myv temp(*this);
	for(int i = 0; i < this->numCnt; i++)
	{
		this->vec[i] = 0;
	}
	if(temp.numCnt != sum.numCnt)
	{
		int max, min = 0;
		if(temp.numCnt > sum.numCnt)
		{
			max = temp.numCnt;
			min = sum.numCnt;
			for(int i = min; i < max; i++)
			{
				sum.vec[i] = sum.vec[i - min];
			}
			
		}
		else
		{
			max = sum.numCnt;
			min = temp.numCnt;
			for(int i = min; i < max; i++)
			{
				temp.vec[i] = temp.vec[i - min];
			}
		}	
	}
	
	int Cnt = 0;
	if(temp.numCnt > sum.numCnt)
		Cnt = temp.numCnt;
	else
		Cnt = sum.numCnt;
	
	for(int i = 0; i < Cnt; i++)
	{
		this->vec[i] = temp.vec[i] + sum.vec[i];
	}
	
	this->numCnt = Cnt;
	return *this;
}

myv& myv::minus(myv minu)
{
	myv temp(*this);
	for(int i = 0; i < this->numCnt; i++)
	{
		this->vec[i] = 0;
	}
	if(temp.numCnt != minu.numCnt)
	{
		int max, min = 0;
		if(temp.numCnt > minu.numCnt)
		{
			max = temp.numCnt;
			min = minu.numCnt;
			for(int i = min; i < max; i++)
			{
				minu.vec[i] = minu.vec[i - min];
			}
			
		}
		else
		{
			max = minu.numCnt;
			min = temp.numCnt;
			for(int i = min; i < max; i++)
			{
				temp.vec[i] = temp.vec[i - min];
			}
		}	
	}
	
	int Cnt = 0;
	if(temp.numCnt > minu.numCnt)
		Cnt = temp.numCnt;
	else
		Cnt = minu.numCnt;
	
	for(int i = 0; i < Cnt; i++)
	{
		this->vec[i] = temp.vec[i] - minu.vec[i];
	}
	
	this->numCnt = Cnt;
	return *this;
}

int main()
{
	cout << "!";
	char type;
	myv array[100];
	int runtime = 0;
	while(cin >> type)
	{
		if(type == 'N')
		{
			char name;
			int n = 0;
			int num[100] = {0};
			cin >> name;
			cin >> n;
			for(int i = 0; i < n; i++)
			{
				cin >> num[i];
			}
			array[runtime].newv(name, n, num);
			runtime ++;
		}
		
		else if(type == 'A')
		{
			char name;
			int n = 0;
			int num[100] = {0};
			int target = 0;
			cin >> name;
			cin >> n;
			for(int i = 0; i < n; i++)
			{
				cin >> num[i];
			}
			for(int i = 0; i < runtime; i++)
			{
				if(array[runtime].name == name)
					target = i;
			}
			array[target].assign(n, num);
		}
		
		else if(type == 'C')
		{
			char shurui;
			char mae;
			char ushiro;
			int front, back = 0;
			
			cin >> shurui >> mae >> ushiro;
			
			for(int i = 0; i < runtime; i++)
			{
				if(mae == array[i].name)
					front = i;
				if(ushiro == array[i].name)
					back = i;
			}
			
			bool result = false;
			result = array[front].compare(shurui, array[back]);
			cout << result;
		}
		
		else if(type == 'I')
		{
			char target;
			int aite;
			int no;
			int num;
			cin >> target >> no >> num;
			
			for(int i = 0; i < runtime; i++)
			{
				if(target == array[i].name)
					aite = i;
			}
			array[aite].index(no, num);
		}
		
		else if(type == 'S')
		{
			int numbers = 0;
			char aite;
			int target;
			int sum;
			char summers[100] = {0};
			cin >> numbers >> aite;
			
			for(int i = 0; i< runtime; i++)
			{
				if(aite == array[i].name)
					target = i;
			}
			for(int i = 0; i < numbers - 1; i++)
			{
				cin >> summers[i];
				for(int j = 0; j < runtime; j++)
				{
					if(summers[i] == array[runtime].name)
						sum = j;
				}
				array[target].sum(array[sum]);
			}
			
			
		}
		
		else if(type == 'M')
		{
			int numbers = 0;
			char aite;
			int target;
			int min;
			char summers[100] = {0};
			cin >> numbers >> aite;
			
			for(int i = 0; i< runtime; i++)
			{
				if(aite == array[i].name)
					target = i;
			}
			for(int i = 0; i < numbers - 1; i++)
			{
				cin >> summers[i];
				for(int j = 0; j < runtime; j++)
				{
					if(summers[i] == array[runtime].name)
						min = j;
				}
				array[target].minus(array[min]);
			}
			
			
		}
	}
	
	return 0;
} 
