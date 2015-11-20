#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(long int input)
{
	for(long int i=2;i<sqrt(input);i++)
	{
		if(!(input % i)) return false;
	}
	return true;
}

int main()
{
	long int number = 600851475143;
	
	for(long int i=sqrt(number);i>0;i--)
	{
		if(!(number % i))
		{
			cout << "Passing: " << i << endl;
			if(isPrime(i)) 
			{
				cout << "Ans: " << i << endl;
				break;
			}
		}
	}
	return 0;
}


//speed = double square testing
