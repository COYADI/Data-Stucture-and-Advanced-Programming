#include <iostream>
#include <string>

using namespace std;

class BigInt
{
	friend istream& operator>>(istream& in, BigInt& n);
	friend ostream& operator<<(ostream& out, BigInt& n);
	
	private:
		string num;
	
	public:
		string name;
		BigInt();           
		BigInt(string, string);
		~BigInt();
		BigInt abs();
		BigInt inverse();
		BigInt& getnum(string num);
		BigInt& print();
		const BigInt& operator=(string& str);

		const BigInt& operator=(BigInt n);	
		const BigInt operator+(BigInt& n)const;
		const BigInt operator-();
		
};

istream& operator>>(istream& in, BigInt& n);
ostream& operator<<(ostream& out, BigInt& n);

BigInt::BigInt()
{
	this->name = "";
	this->num = "";
}

BigInt::BigInt(string name, string num)
{
	this->name = name;
	this->num = num;
}

BigInt::~BigInt()
{
}

BigInt& BigInt::getnum(string num)
{
	num.pop_back();
	this->num = num;	
}

const BigInt& BigInt::operator=(string& str)
{
	this->num = str;
	return *this;
}

const BigInt& BigInt::operator=(BigInt n)
{
	this->num = n.num; 
	return *this;
}




const BigInt BigInt ::operator+(BigInt& n)const
{
	BigInt sum(*this);
	int thislen = 0;
	int nlen = 0;
	int minlen = 0;
	int maxlen = 0;
	
	thislen = this->num.length();
	nlen = n.num.length();
	
	if(thislen > nlen)
	{
		minlen = nlen;
		maxlen = thislen;
		for(int i = 0; i < (thislen - nlen); i++)
			n.num.insert(0 , "0");
	}
	else if(thislen < nlen)
	{
		minlen = thislen;
		maxlen = nlen;
		for(int i = 0; i < (nlen - thislen); i++)
			sum.num.insert(0 , "0");
    }	
    else
	{
    	maxlen = nlen;
	}
    
	bool pls = false;
	for(int i = 0; i < maxlen; i++)
	{
		if(pls == true)
		{
			sum.num[maxlen - i] += 1;
			pls = false;
		}
		
		sum.num[maxlen - i] += n.num[maxlen - i];
		if(sum.num[maxlen - i] > 57)
		{
			sum.num[maxlen - i] -= 10;
			pls = true;
		}
	}
	
	return sum;
}

BigInt BigInt::inverse()
{
	BigInt result(*this);
	if(result.num[0] == '-')
		result.num.erase(0,1);
	else
		result.num.insert(0,1,'-');
	
	return result;
}

BigInt BigInt::abs()
{
	BigInt result(*this);
	if(result.num[0] == '-')
		result.num.erase(0,1);

	return result;
}

BigInt& BigInt::print()
{
	cout << this->num << "\n";
}

istream& operator>>(istream& in, BigInt& n)
{
	in >> n.num;
	return in;
}

ostream& operator<<(ostream& out, BigInt& n)
{
	out << n.num;
	return out; 
}

const BigInt BigInt::operator-()
{
	BigInt result(*this);
	if(result.num[0] == '-')
		result.num.erase(0,1);
	
	else
		result.num.insert(0,1,'-');
	
	return result;
}

int main()
{
	string type;
	int Bnum = 0;
	BigInt bigint[100];
	while(cin >> type)
	{
		if(type == "int")
		{
			string name;
			string equal;
			string num;
			cin >> name >> equal >> num;
			bigint[Bnum].name = name;
			bigint[Bnum].getnum(num);
			Bnum ++;
		}
		
		else if(type == "cout")
		{
			string non;
			string dos;
			cin >> non;
			cin >> dos;
			dos.pop_back();
			
			if(dos.find("abs") != string::npos)
			{
				int target = 0;
				size_t found = dos.find(".abs()");
	
				dos.erase(found, 6);
				
				for(int i = 0; i < 100; i++)
				{
					if(dos == bigint[i].name)
						target = i;
				}
				
				bigint[target].abs().print();
			}
			
			else if(dos.find("-") != string::npos)
			{
				int target = 0;
				size_t found = dos.find("-");
				
				dos.erase(found, 1);
				
				for(int i = 0; i < 100; i++)
				{
					if(dos == bigint[i].name)
						target = i;
				}
				bigint[target].inverse().print();
			}
			
			else
			{
				int target = 0;
				for(int i = 0; i < 100; i++)
				{
					if(dos == bigint[i].name)
						target = i;
				}
				bigint[target].print();
			}
		}
		
		else
		{	
				string equal;
				string dos;
				cin >> equal;
				cin >> dos;
				dos.pop_back();
				
				if(dos.find("abs") != string::npos)
				{
					int target = 0;
					int modee = 0;
					size_t found = dos.find(".abs()");
					
					dos.erase(found, 6);
					
					for(int i = 0; i < 100; i++)
					{
						if(dos == bigint[i].name)
							target = i;
					}
					for(int i = 0; i < 100; i++)
					{
						if(type == bigint[i].name)
							modee = i;
					}
					bigint[modee] = bigint[target].abs();
				}
				
				else if(dos.find("-") != string::npos)
				{
					int target = 0;
					int modee = 0;
					size_t found = dos.find("-");
					
					dos.erase(found, 1);
					
					for(int i = 0; i < 100; i++)
					{
						if(dos == bigint[i].name)
							target = i;
					}
					for(int i = 0; i < 100; i++)
					{
						if(type == bigint[i].name)
							modee = i;
					}
					bigint[modee] = bigint[target].inverse();
				}
				else
				{
					
					
					int target;
					int modee;
					for(int i = 0; i < 100; i++)
					{
						if(type == bigint[i].name)
							target = i;
					}
					for(int i = 0; i < 100; i++)
					{
						if(dos == bigint[i].name)
							modee = i;
					}
					
					bigint[target] = bigint[modee];
				}
		}	
	}
	
	
	
	return 0;
} 
