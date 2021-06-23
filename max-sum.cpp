/*
NAME: Reid Nagurka
CS Account id: rgnag
 */

#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

int maxSubSum( const vector<int> & a )
{
    int maxSum = 0, thisSum = 0;

    for( int j = 0; j < a.size( ); ++j )
    {
        thisSum += a[ j ];

        if( thisSum > maxSum )
            maxSum = thisSum;
        else if( thisSum < 0 )
            thisSum = 0;
    }

    return maxSum;
}

// O(n)
int minSubSum(const vector<int> & a)
{
  //YOUR PROGRAM
  int minSum = 0, thisSum = 0;
  for (int j = 0; j < a.size(); ++j)
  {
	thisSum += a[j];
	if(thisSum < minSum)
		minSum = thisSum;
	else if(thisSum > 0)
		thisSum = 0;
  }

  return minSum;
}

int maxSubProduct(const vector<int> & a)
{
  //YOUR PROGRAM
    int maxProd = 0, thisProd = 1, zeroProd = 1, negProd = 1, negCount = 0;

	
	for(int j = 0; j < a.size(); j++)
	{
		//check to see if a[j] is zero
		if(a[j] != 0)
		{
			//check if a[j] is negative and check running total of negative.
			if(a[j] < 0 && negCount % 2 == 0)
			{
				//If the negCount is even (starting at zero), save the sum and increment negCount
				negProd = thisProd;
				negCount++;
			}
			//if the negCount is odd, just increment negCount b/c it means the resulting sum will be positive.
			else if(a[j] < 0 && negCount % 2 != 0)
			{
				negCount++;
			}
			
			//in any event, multiply thisProd by a[j]
			thisProd *= a[j];
			
		}
		else if(a[j] == 0)
		{
			zeroProd = thisProd;
			thisProd = 1;
		}
		
		//check all prods and make the largest maxProd
		if(thisProd > maxProd)
			maxProd = thisProd;
		if(negProd > maxProd)
			maxProd = negProd;
		if(zeroProd > maxProd)
			maxProd = zeroProd;
		
		
	}
	return maxProd;
/*
	  
	for( int j = 0; j < a.size( ); ++j )
    {
        thisSum += a[ j ];

        if( thisSum > maxSum )
            maxSum = thisSum;
        else if( thisSum < 0 )
            thisSum = 0;
    }

*/
}


int main()
{
  int num;
  ifstream dataFile;
  vector<int> data;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) {
    while (dataFile>>num)
      data.push_back(num);
  }

  dataFile.close();

  //  for (int i=0; i<data.size(); i++)
  //    cout<<"Number "<<i<<" is "<< data[i]<<endl;


  int result;
  result = maxSubSum( data );
  cout << "Max sum is " <<  result << endl;
  result = minSubSum( data );
  cout << "Min sum is " <<  result << endl;
  result = maxSubProduct( data );
  cout << "Max product is " <<  result << endl;

  return 0;
}