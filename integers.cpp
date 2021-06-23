// Reid Nagurka 
#include <iostream> 
#include<fstream>
#include <vector> 
using namespace std;

void printVector(vector <int> v)
{	
	vector <int> :: iterator it; 
	for(it = v.begin(); it != v.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n'; 
}

int maxInt(vector <int> v)
{
	vector <int> :: iterator it; 
	int max = 0;
	for(it = v.begin(); it != v.end(); ++it) 
	{
		if(*it > max)
			max = *it;
	}
 
	return max;
}

int minInt(vector <int> v)
{
	vector <int> :: iterator it; 
	//use first value of v rather than 0
	int min = 100;
	for(it = v.begin(); it != v.end(); ++it) 
	{
		if(*it < min)
			min = *it;
	}
 
	return min;
}

int median(vector <int> v)
{
	/*
	make duplicate vector
		find minimum in duplicate vector size of vector / 2 - 1 if odd.
		delete that minimum
		return the value at the index (once the loop condition is finished.
	*/
	
	//duplicate vector
	vector <int> copy;
	vector <int> :: iterator cit;
	int c; 
	int min = 100;
	for(cit = v.begin(); cit != v.end(); ++cit)
	{
		c = *cit;
		copy.push_back(c);
	}
	
	//How many times:
	//if size is odd, index is size / 2 - 1. But will run one more time outside of loop so only go through 
	// size / 2. Handle even case later.
	vector <int> :: iterator cit2;
	if(v.size() %2 != 0)
	{
		int s = v.size() / 2;
		for(int i = 0; i < s; i++)
		{
		
			//find minimum in copy.
			min = 100;
			
			for(cit = copy.begin(); cit != copy.end(); ++cit) 
			{
				if(*cit < min)
				{
					min = *cit;
					//save index of minimum
					cit2 = cit;
				}
			}
			
			//delete minimum from copy
			copy.erase(cit2);
		
		}
		//just find minimum of copy one more time. This should be the minimum.
		return minInt(copy);
	}
	
	//if the vector has an even number of elements, find the two medians and average them
	else
	{
		int med1, med2;
		int s = v.size() / 2;
		for(int i = 0; i < s; i++)
		{
		
			//find minimum in copy.
			min = 100;
			
			for(cit = copy.begin(); cit != copy.end(); ++cit) 
			{
				if(*cit < min)
				{
					min = *cit;
					//save index of minimum
					cit2 = cit;
				}
			}
			
			//assing med1 to the minimum, so that the last time the loop runs the minimum is saved.
			med1 = min;
			//delete minimum from copy
			copy.erase(cit2);
		
		}
		//just find minimum of copy one more time. This should be the second minimum after the one saved above.
		med2 = minInt(copy);
		//average the two medians to get the true median
		return (med1+med2) / 2.0;
	}
	//if the size of the vector is neither odd nor even, return 0 (something went wrong)
	return 0;

}

int sum(vector <int> v)
{
	vector <int> :: iterator it; 
	int sum = 0;
	for(it = v.begin(); it != v.end(); ++it) 
	{
		sum+= *it;
	}
 
	return sum;
}

int main()
{
	
  ifstream dataFile;
  vector<int> v1;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data1.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      v1.push_back(num);
 
  dataFile.close();
  
  
  printVector(v1);
  cout << "Max: \t" << maxInt(v1);
  cout << "\nMin: \t" << minInt(v1);
  cout << "\nMedian: " << median(v1);
  cout << "\nSum: \t" << sum(v1);
  
}