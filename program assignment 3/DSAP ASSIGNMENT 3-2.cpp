#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template<class ItemType>
struct Node
{
	ItemType item;
	Node<ItemType>* next;
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
};

template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
	item(anItem), next(nextNodePtr)
{
}

template<class ItemType>
class StackInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool push(const ItemType& newEntry) = 0;
	virtual bool pop() = 0;
	virtual ItemType peek() const = 0;
};

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
private:
	Node<ItemType>* topPtr;
public:
	LinkedStack();
	LinkedStack(const LinkedStack<ItemType>& aStack);	
	~LinkedStack();
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;
};

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
}

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
	Node<ItemType>* origChainPtr = aStack.topPtr;
	if (origChainPtr == nullptr)
		topPtr = nullptr;
	else
	{	// copy first node
		Node<ItemType>* newChainPtr = topPtr;
		newChainPtr = new Node<ItemType>(origChainPtr->item);

		// copy remaining nodes
		origChainPtr = origChainPtr->next;
		while (origChainPtr != nullptr)
		{
			newChainPtr->next = new Node<ItemType>(origChainPtr->item);
			newChainPtr = newChainPtr->next;
			origChainPtr = origChainPtr->next;
		}

		newChainPtr->next = nullptr; // Flag end of new chain
	}
}

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	while (!isEmpty())
		pop();
}

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return (topPtr == nullptr);
}

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;

	return true;
}

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
	if (!isEmpty())
	{
		Node<ItemType>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->next;

		nodeToDeletePtr->next = nullptr;
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		return true;
	}
	return false;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
	if (isEmpty())
		throw logic_error("Precondition Violated Exception: peek() called with an empty stack.\n");

	return topPtr->item;
}


class Polynomial
{
	private:
		double array[105] = {0};
	
	public:
		Polynomial()
		{
		};
		Polynomial(int scalar, int multi)
		{
			this->array[multi] = scalar;
		};
		~Polynomial()
		{
			for(int i = 0; i < 105; i++)
				this->array[i] = 0;
			
		};
		Polynomial plus(Polynomial a);
		Polynomial minus(Polynomial a);
		Polynomial multiply(Polynomial a);
		Polynomial division(Polynomial a,int type);
		Polynomial square(Polynomial a);
		int getmulti();
		void print();
		
};
Polynomial Polynomial::plus(Polynomial a)
{
	Polynomial result;
	for(int i = 0; i < 105; i++)
	{
		result.array[i] = a.array[i] + this->array[i];
	}
	return result;
}
Polynomial Polynomial::minus(Polynomial a)
{
	Polynomial result;
	for(int i = 0; i < 105; i++)
	{
		result.array[i] = a.array[i] - this->array[i];
	}
	return result;
}
Polynomial Polynomial::multiply(Polynomial a)
{
	Polynomial result;
	for(int i = 0; i <= a.getmulti(); i++)
	{
		for(int j = 0; j <= this->getmulti(); j++)
		{
			result.array[i + j] += (a.array[i] * this->array[j]);
		}
	}
	return result;
}
Polynomial Polynomial::square(Polynomial a)
{
	Polynomial result = a;
	Polynomial temp = a;
	int times = this->array[0];
	for(int i = 0; i < times - 1; i++)
		result = result.multiply(temp);
	return result;
}
Polynomial Polynomial::division(Polynomial a,int type)
{
	Polynomial result;
	if(a.getmulti() < this->getmulti())
	{
		if(type == 1)
			return result;
		else if(type == 2)
		{
			result = a;
			return result;
		}
	}
	int times = a.getmulti();
	int dividee = this->getmulti();
	while(times >= dividee)
    {
        int num = times;
        double temp = a.array[times] / this->array[dividee];
        result.array[num - dividee] = temp;
        for(int i = dividee; i >= 0; i --)
        {
        //	cout<<temp<<" "<<this->array[i]<<endl;
            if(num > dividee)
				a.array[num] -= (temp * this->array[i]);
			else
				a.array[num] -= (static_cast<int>(temp) * this->array[i]);
            num --;
        }
        
        //cout<<a.array[0]<<endl;
        times --;
        
    }
    for(int i = 0; i < 105; i ++)
    {
        int totrans = result.array[i];
        double posttrans = totrans;
        result.array[i] = posttrans;
    }
    if(type == 1)
    	return result;
    if(type == 2)
    {
    	result = a;
    	return result;
	}
} 
int Polynomial::getmulti()
{
	for(int i = 104; i > -1; i--)
	{
		if(this->array[i] != 0)
			return i;
	}
	return 0;
}
void Polynomial::print()
{
	bool printed = false;
	for(int i = 104; i > -1; i--)
	{
		if(this->array[i] != 0)
		{
			if(this->array[i] > 1)
			{
				if(printed == false)
				{
					if(i > 1)
						cout << static_cast<int>(this->array[i]) << "x^" << i;
					else if(i == 0)
						cout << static_cast<int>(this->array[i]);
					else
						cout << static_cast<int>(this->array[i]) << "x";
				}
				else 
				{
					if(i > 1)
						cout << "+" << static_cast<int>(this->array[i]) << "x^" << i;
					else if(i == 0)
						cout << "+" << static_cast<int>(this->array[i]);
					else
						cout << "+" << static_cast<int>(this->array[i]) << "x";
				}
			}
			
			else if(this->array[i] < -1)
			{
				if(i > 1)
					cout << static_cast<int>(this->array[i]) << "x^" << i;
				else if(i == 0)
					cout << static_cast<int>(this->array[i]);
				else
					cout << static_cast<int>(this->array[i]) << "x";
			}
			
			else if(this->array[i] == 1)
			{
				if(printed == false)
				{
					if(i > 1)
						cout << "x^" << i;
					else if(i == 0)
						cout << static_cast<int>(this->array[i]);
					else
						cout << "x";
				}
				else
				{
					if(i > 1)
						cout << "+" << "x^" << i;
					else if(i == 0)
						cout << "+" << static_cast<int>(this->array[i]);
					else
						cout << "+x";
				}
			}
			
			else if(this->array[i] == -1)
			{
				if(i > 1)
					cout << "-x^" << i;
				else if(i == 0)
					cout << static_cast<int>(this->array[i]);
				else
					cout << "-x";
			}
			printed = true;	
		}
	}
	if(!printed)
		cout << "0";
}

bool isOperator(char c);
int priority(char c);
void printpostfix(string c);

int main()
{
	string in;
	string postfix;
	LinkedStack<char> infixstack;
	cin >> in;
	string space = " ";
	
	for(int i = 0; i < in.length(); i ++)
	{
		if(isOperator(in[i]))
		{
			if(infixstack.isEmpty())
				infixstack.push(in[i]);
			
			else if(infixstack.peek() == '(')
				infixstack.push(in[i]);
			
			else
			{
				while(priority(in[i]) <= priority(infixstack.peek()))
				{
					postfix += infixstack.peek();
					postfix += space;
					infixstack.pop();
					if(infixstack.isEmpty())
						break;
				}
				infixstack.push(in[i]);
			}
		}
		
		else if(in[i] == '(')
			infixstack.push(in[i]);
		
		else if(in[i] == ')')
		{
			while(infixstack.peek() != '(')
			{
				postfix += infixstack.peek();
				postfix += space;
				infixstack.pop();
			}
			infixstack.pop();
		}
		
		else if(in[i] != 'x' && !isOperator(in[i]))
		{
			int j = 0;
			while(!isOperator(in[i + j]) && in[i + j] != 'x' && in[i + j] != '(' && in[i + j] != ')' && (i + j + 1) <= in.length())
			{
				postfix += in[i + j];
				j++;
			}
			i += j-1;
			postfix += space;
		}
		
		else 
		{
			postfix += in[i];
			postfix += space;
		}
		
		/*cout << postfix << endl;
		if(!infixstack.isEmpty())
			cout << infixstack.peek() << endl;	*/
	}
	
	while(!infixstack.isEmpty())
	{
		postfix += infixstack.peek();
		postfix += space;
		infixstack.pop();
	}
	
	postfix.pop_back();
	
	//cout << postfix;
	cout << postfix << endl;
	LinkedStack<Polynomial> polystack;
	
	//cout << "no error!";
	
	for(int i = 0; i < postfix.length(); i++)
	{
		if(postfix[i] == ' ')
		{
		}
		else if(!isOperator(postfix[i]))
		{
			if(postfix[i] != 'x')
			{
				double result = 0;
				int j = 0;
				while(postfix[i + j] != ' ' && (i + j) < postfix.length())
				{
					result *= 10;
					result += (postfix[i + j] - '0');
					j ++;
				//	cout<<j<<" "<<result<<endl;
				}
				i += j;
				//cout<<result<<endl;
				Polynomial scalar(result, 0);
				polystack.push(scalar);
			}
			else
			{
				Polynomial x(1, 1);
				polystack.push(x);
			}
		}
		else if(isOperator(postfix[i]))
		{
			Polynomial operandA;
			Polynomial operandB;
			Polynomial result;
			
			if(postfix[i] == '+')
			{
				operandA = polystack.peek();
				polystack.pop();
				operandB = polystack.peek();
				polystack.pop();
				result = operandA.plus(operandB);
				polystack.push(result);
			}
			else if(postfix[i] == '-')
			{
				operandA = polystack.peek();
				polystack.pop();
				operandB = polystack.peek();
				polystack.pop();
				result = operandA.minus(operandB);
				polystack.push(result);
			}
			else if(postfix[i] == '*')
			{
				operandA = polystack.peek();
				polystack.pop();
				operandB = polystack.peek();
				polystack.pop();
				result = operandA.multiply(operandB);
				polystack.push(result);
			}
			else if(postfix[i] == '^')
			{
				operandA = polystack.peek();
				polystack.pop();
				operandB = polystack.peek();
				polystack.pop();
				result = operandA.square(operandB);
				polystack.push(result);
			}
			else if(postfix[i] == '/')
			{
				operandA = polystack.peek();
				polystack.pop();
				operandB = polystack.peek();
				polystack.pop();
				result = operandA.division(operandB,1);
				polystack.push(result);
			}
			else if(postfix[i] == '%')
			{
				operandA = polystack.peek();
				polystack.pop();
				operandB = polystack.peek();
				polystack.pop();
				result = operandA.division(operandB,2);
				polystack.push(result);
			}
		}
	}
		
	Polynomial result = polystack.peek();
	result.print(); 

	return 0;
}

bool isOperator(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
		return true;	
	return false;
}
int priority(char c)
{
	if(c == '+' || c == '-')
		return 1;
	else if(c == '/' || c == '*' || c == '%')
		return 2;
	else if(c == '^')
		return 3;
		
	return 0;
}
void printpostfix(string c)
{
	for(int i = 0; i < c.length(); i++)
	{
		if(isOperator(c[i]))
			cout << " " << c[i];		
		else if(i == 0)
			cout << c[i];	
		else
		{
			if(c[i] == 'x')
				cout << " " << c[i];		
			else if(c[i - 1] != 'x' && !isOperator(c[i - 1]))
				cout << c[i];		
			else 
				cout << " " << c[i];
		}
	}
	cout << endl;
} 
