#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

struct dimen
{
	int x;
	int y;
};

class car
{
	protected:
		int cond = 0;
		int minprize = 0;
		int plusprize = 0;
		dimen nowat;
		int pointCnt = 0;
		int point = 0;
		char direc;
		bool personal[20];
		int time = 0;
		int okotteru = 0;
		
	public:
		car();
		string name;
		int money = 0;
		string thepass;
		void print();
		void online(int, int, char, int);
		virtual void move() ;
		int search(int, int, int, int, int, bool[], int, int);
		void turn(char);
		void mission(string);
		void getpass(int);
		virtual void arrive(int, int, bool[], int, char, int, int);
		void offline();
		
};
car::car()
{
}
void car::online(int x, int y, char direc, int time)
{
	this->cond = 1;
	this->nowat.x = x;
	this->nowat.y = y;
	this->direc = direc;
	this->time = time;
}
void car::turn(char direc)
{
	this->direc = direc;
}
void car::print()
{
	cout << this->name << " " << this->cond << " " << this->point << " " << this->pointCnt;
	if(this->cond == 1)
		cout << " " << this->nowat.x << " " << this->nowat.y;
	else if(this->cond == 2 || this->cond == 3)
	{
		cout << " " << this->thepass;
	}
	
	cout << "\n";
}
void car::move()
{
}
int car::search(int x, int y, int K, int n, int k, bool personall[], int h, int p)
{
	if((abs(this->nowat.x - x)) + abs(this->nowat.y - y) <= K)
	{
		int total = 0;
		int chas = 0;
		for(int i = 0; i < n; i++)
		{
			if(this->personal[i] == true && personall[i] == true)
				chas++;
		}
		total = this->point - (k * this->pointCnt) + (chas * h) - ((abs(this->nowat.x - x)) + abs(this->nowat.y - y) * p);
		return total;
	}
	
	else 
		return -1;
}
void car::mission(string pass)
{
	this->cond = 2;
	this->thepass = pass;
	cout << this->thepass;
}
void car::getpass(int time)
{
	this->cond = 3;
	if(time > 10 && time <= 20)
		this->okotteru++;
	
	if(time > 20)
		{
			this->okotteru += 2;
		}
}
void car::arrive(int time, int dist, bool charac[20], int n, char direc, int x, int y)
{
}
void car::offline()
{
	this->cond = 0;
}

class passenger
{
	private:
		int cond = 0;
		dimen nowat;
		char wants;
		int time = 0;
		string thecar;

		
	public:
		passenger();
		passenger& newpass(string, string, string[], int);
		string name;
		bool personal[20];
		void print();
		void online(string, int, int, int);
		int waited(int);
		int moved(int, int);
		void offline();
		
};
passenger::passenger()
{
}
passenger& passenger::newpass(string name, string personality, string charac[20], int n)
{
	this->cond = 0;
	this->name = name;
	
	for(int i = 0; i < n; i++)
	{
		size_t found;
		found = personality.find(charac[i]);
		if(found != string::npos)
			this->personal[i] = true;
		else
			this->personal[i] = false;
	}
}
void passenger::online(string thecar, int time, int x, int y)
{
	this->cond = 1;
	this->thecar = thecar;
	this->time = time;
	this->nowat.x = x;
	this->nowat.y = y;
}
int passenger::waited(int time)
{
	int num = 0;
	this->cond = 2;
	num = time - this->time;
	this->time = time;

	return num;
}
int passenger::moved(int x, int y)
{
	int total = abs(this->nowat.x - x) + abs(this->nowat.y - y);
	return total;
}
void passenger::offline()
{
	this->cond = 0; 
}
void passenger::print()
{
	cout << this->cond;
	
	if(this->cond != 0)
		cout << this->thecar;
	
	cout << "\n";
}

class carR : public car
{
	private:
		const int SPEED = 1;
	public:
		carR();
		carR& newcarr(int, int, string, string, string[], int);
		void move(int);
		void arrive(int, int, bool[], int, char, int, int);
};
carR::carR()
{
}
carR& carR::newcarr(int aR, int bR, string name, string personality, string charac[20], int n)
{
	this->cond = 0;
	this->minprize = aR;
	this->plusprize = bR;
	this->name = name;
	
	for(int i = 0; i < n; i++)
	{
		size_t found;
		found = personality.find(charac[i]);
		if(found != string::npos)
			this->personal[i] = true;
		else
			this->personal[i] = false;
	}
}
void carR::move(int time)
{
	if(this->cond == 1)
	{
		if(this->direc == 'N')
		{
			this->nowat.y += this->SPEED * (time - this->time);
			this->time = time;
		}
		else if(this->direc == 'S')
		{
			this->nowat.y -= this->SPEED * (time - this->time);
			this->time = time;
		}
		else if(this->direc == 'E')
		{
			this->nowat.x += this->SPEED * (time - this->time);
			this->time = time;
		}
		else if(this->direc == 'W')
		{
			this->nowat.x -= this->SPEED * (time - this->time);
			this->time = time;
		}
	}
}
void carR::arrive(int time, int dist, bool charac[20], int n, char direc, int x, int y)
{
	int pointthistime = 0;
	pointthistime += 4;
	pointthistime -= this->okotteru;
	this->pointCnt += 1;
	if(time > (3 * dist))
	{
		this->okotteru += 2;
		pointthistime -= 2;
	}
	else if(time > (2 * dist) && time <= (3 * dist))
	{
		pointthistime -= 1;
	}
	
	for(int i = 0; i < n; i++)
	{
		if(this->personal[i] == true && charac[i] == true)
			pointthistime += 1;
	}
	if(pointthistime > 5)
		pointthistime = 5;
	else if(pointthistime < 1)
		pointthistime = 1;
		
	this->point += pointthistime;
	
	if(this->okotteru > 1)
		this->money += 0;
	else if(this->okotteru <= 1)
		this->money += this->minprize + (this->plusprize * dist);
		
	this->okotteru = 0;
	this->nowat.x = x;
	this->nowat.y = y;
	this->cond = 1;
	this->direc = direc;
	this->thepass = {};
}

class carL : public car
{
	private:
		const int SPEED = 2;
	public:
		carL();
		carL& newcarl(int, int, string, string, string[], int);
		void move(int);
		void arrive(int, int, bool[], int, char, int, int);
};
carL::carL()
{
}
carL& carL::newcarl(int aL, int bL, string name, string personality, string charac[20], int n)
{
	this->cond = 0;
	this->minprize = aL;
	this->plusprize = bL;
	this->name = name;
	
	for(int i = 0; i < n; i++)
	{
		size_t found;
		found = personality.find(charac[i]);
		if(found != string::npos)
			this->personal[i] = true;
		else
			this->personal[i] = false;
	}
} 
void carL::move(int time)
{
	if(this->cond == true)
	{
		if(this->direc == 'N')
		{
			this->nowat.y += this->SPEED * (time - this->time);
			this->time = time;
		}
		else if(this->direc == 'S')
		{
			this->nowat.y -= this->SPEED * (time - this->time);
			this->time = time;
		}
		else if(this->direc == 'E')
		{
			this->nowat.x += this->SPEED * (time - this->time);
			this->time = time;
		}
		else if(this->direc == 'W')
		{
			this->nowat.x -= this->SPEED * (time - this->time);
			this->time = time;
		}
	}
}
void carL::arrive(int time, int dist, bool charac[], int n, char direc, int x, int y)
{
	int pointthistime = 0;
	pointthistime += 4;
	pointthistime -= this->okotteru;
	this->pointCnt += 1;
	if(time > (1.5 * dist))
	{
		this->okotteru += 2;
		pointthistime -= 2;
	}
	else if(time > (1 * dist) && time <= (3 * dist))
	{
		pointthistime -= 1;
	}
	
	for(int i = 0; i < n; i++)
	{
		if(this->personal[i] == true && charac[i] == true)
			pointthistime += 1;
	}
	if(pointthistime > 5)
		pointthistime = 5;
	else if(pointthistime < 1)
		pointthistime = 1;
		
	this->point += pointthistime;
	
	if(this->okotteru > 1)
		this->money += 0;
	else if(this->okotteru <= 1)
		this->money += this->minprize + (this->plusprize * dist);
		
	this->okotteru = 0;
	this->nowat.x = x;
	this->nowat.y = y;
	this->cond = 1;
	this->direc = direc;
	this->thepass = {};
}

int main()
{
	int K = 0, ar = 0, br = 0, al = 0, bl = 0, k = 0, h = 0, p = 0, n = 0;
	string per[20];
	
	cin >> K >> ar >> br >> al >> bl >> k >> h >> p >> n;
	
	
	for(int i = 0; i < n-1; i++)
		getline(cin, per[i], ';');
				
	getline(cin, per[n], '\n');
	
	
	passenger pass[100];
	carR carr[100];
	carL carl[100];
	int passCnt = 0;
	int carRCnt = 0;
	int carLCnt = 0;
	
	while(1)
	{
		int hour = 0;
		char trash;
		int min = 0;
		
		cin >> hour >> trash >> min;
		
		int time = hour * 60 + min;
		
		int max = 0;
		if(carRCnt > carLCnt)
			max = carRCnt;
		else
			max = carLCnt;
		
		for(int i = 0; i < max; i++)
		{
			carr[i].move(time);
			carl[i].move(time);
		}
		
		string type;
		
		getline(cin, type, ':');
	//	cout << type <<endl;
		size_t finder = type.find("SR");
		
		if(type.find("SR") != string::npos)
		{
			int totalmoney = 0;
			for(int i = 0; i < carRCnt; i++)
			{
				totalmoney += carr[i].money;
			}
			for(int i = 0; i < carLCnt; i++)
			{
				totalmoney += carl[i].money;
			}
			
			cout << totalmoney << "\n";
			
			type.erase(0,4);
			
			hour = stoi(type);
			cin >> min;
			time = hour * 60 + min;
			getline(cin, type, ':');
		}
		
		cout << type << endl;
		if(type == " NP")
		{
			string name;
			string charac;
			getline(cin, name, '(');
		
			getline(cin, charac, '\n');
			
			charac.pop_back();
			pass[passCnt].newpass(name, charac, per, n);
			passCnt ++;
		}
		
		else if(type == " NC")
		{
			string name;
			string charac;
			char shurui;
			getline(cin, name, '(');
			getline(cin, charac, ')');
			cin >> shurui;
			
			if(shurui == 'R')
			{
				carr[carRCnt].newcarr(ar, br, name, charac, per, n);
				carRCnt++;
			}
			else if(shurui == 'L')
			{
				carl[carLCnt].newcarl(al, bl, name, charac, per, n);
				carLCnt++;
			}
			
		}
		
		else if(type == " OC")
		{
			string name;
			int x;
			int y;
			char dot;
			char trash;
			char direc;
			
			getline(cin, name, '(');
			cin >> x >> dot >> y >> trash >> direc;
			
			for(int i = 0; i < max; i++)
			{
				if(name == carr[i].name)
				{
					carr[i].online(x, y, direc, time);
				}
				else if(name == carl[i].name)
				{
					carl[i].online(x, y, direc, time);
				}
			}
		}
		
		else if(type == " EC")
		{
			string name;
			char direc;
			char trash;
			
			getline(cin, name, '(');
			cin >> direc >> trash;

			
			for(int i = 0; i < max; i++)
			{
				if(carr[i].name == name)
				{
					carr[i].turn(direc);
				}
				if(carr[i].name == name)
				{
					carr[i].turn(direc);
				}
			}
		}
		
		else if(type == " OP")
		{
			string name;
			int x;
			int y;
			char dot;
			char trash;
			char require;
			
			getline(cin, name, '(');
			cin >> x >> dot >> y >> trash >> require;
			
			int target = -1;
			for(int i = 0; i < passCnt; i++)
			{
				if(name == pass[i].name)
					target = i;
			}
			
			if(require == 'R')
			{
				int theone = -1;
				int theonenum = -1;
				
				for(int i = 0; i < carRCnt; i++)
				{
					if(carr[i].search(x, y, K, n, k, pass[target].personal, h, p) > theone)
					{
						theone = carr[i].search(x, y, K, n, k, pass[target].personal, h, p);
						theonenum = i;
					}	
				}
				
				if(theonenum = -1)
				{
				}
				else
				{
					//派車.上線
					carr[theonenum].mission(pass[target].name);
					pass[target].online(carr[theonenum].name, time, x, y);
				}
			}
			
			if(require == 'L')
			{
				int theone = -1;
				int theonenum = -1;
				
				for(int i = 0; i < carLCnt; i++)
				{
					if(carl[i].search(x, y, K, n, k, pass[target].personal, h, p) > theone)
					{
						theone = carl[i].search(x, y, K, n, k, pass[target].personal, h, p);
						theonenum = i;
					}	
				}
				
				if(theonenum = -1)
				{
				}
				else
				{
					//派車.上線
					carl[theonenum].mission(pass[target].name);
					pass[target].online(carl[theonenum].name, time, x, y);
				}
			}
			
		}
		
		else if(type == " CP")
		{
			string name;
			getline(cin, name, '\n');
			
			for(int i = 0; i < max; i++)
			{
				if(carr[i].name == name)
				{
					for(int j = 0; j < passCnt; j++)
					{
						if(carr[i].thepass == pass[j].name)
						{
							pass[j].waited(time);
							carr[i].getpass(pass[j].waited(time));
						}
					}
					
				}
				if(carl[i].name == name)
				{
					for(int j = 0; j < passCnt; j++)
					{
						if(carl[i].thepass == pass[j].name)
						{
							pass[j].waited(time);
							carl[i].getpass(pass[j].waited(time));
						}
					}
				}
			}
		}
		
		else if(type == " AD")
		{
			string name;
			int x;
			int y;
			char dot;
			char trash;
			char direc;
			
			getline(cin, name, '(');
			cin >> x >> dot >> y >> trash >> direc;
			//	cout <<" " << name;
			
			for(int i = 0; i < max; i++)
			{
				if(carr[i].name == name)
				{
					for(int j = 0; j < passCnt; j++)
					{
						if(carr[i].thepass == pass[j].name)
						{
							carr[i].arrive(pass[j].waited(time), pass[j].moved(x, y), pass[j].personal, n, direc, x, y);
							pass[j].offline();
						}
					}
				}
				if(carl[i].name == name)
				{
					for(int j = 0; j < passCnt; j++)
					{
						if(carl[i].thepass == pass[j].name)
						{
							carl[i].arrive(pass[j].waited(time), pass[j].moved(x, y), pass[j].personal, n, direc, x, y);
							pass[j].offline();
						}
					}
				}
			}
		}
		
		else if(type == " SC")
		{
			string name;
			getline(cin, name, '\n');
			bool printed = false;

			for(int i = 0; i < max; i++)
			{
				if(name == carr[i].name)
				{
					carr[i].print();
					printed = true;
				}
				else if(name == carl[i].name)
				{
					carl[i].print();
					printed = true;
				}
			}
			if(printed == false)
				cout << name << ": no registration!\n";
		}
		
		else if(type == " SP")
		{
			string name;
			getline(cin, name, '\n');
			bool printed = false;

			for(int i = 0; i < passCnt; i++)
			{
				if(name == pass[i].name)
				{
					pass[i].print();
					printed = true;
				}
			}
			if(printed == false)
				cout << name << ": no registration!\n";
		}
		
		else if(type == " LC")
		{
			string name;
			getline(cin, name, '\n');
			
			for(int i = 0; i < max; i++)
			{
				if(name == carr[i].name)
				{
					carr[i].offline();
				}
				else if(name == carl[i].name)
				{
					carl[i].offline();
				}
			}
		}
		
		
	}
	
	return 0;
}
