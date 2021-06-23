
/*==================
Your Name: Reid Nagurka
Your Login ID: rgnag
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <iterator> 
using namespace std; 


void showData(vector<int> h)
{
  /*
    vector <int> :: iterator it; 
    for(it = h.begin(); it != h.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n';
  */

    for(int i=0; i < h.size(); ++i) 
        cout <<"  " << h[i]; 
    cout << '\n';

}

void merge(vector<int> &d, int leftIdx, int mid, int rightIdx) 
{ 

	//mid is end of left sub array. mid + 1 is beginning of right sub array
	
	//left and right sub arrays used for merging
	vector<int> left, right;
	//i is index of left sub array, j is index of right sub array. k is index of d
    int i, j, k; 
	//end of left sub array (for loop)
    int endLeft = mid - leftIdx + 1; 
	//end of right sub array (for loop)
    int endRight =  rightIdx - mid; 

    //copy data from d into the helper left and right sub arrays
    for (i = 0; i < endLeft; i++) 
        left.push_back(d[leftIdx + i]); 
    for (j = 0; j < endRight; j++) 
        right.push_back(d[mid + 1+ j]); 
  
    // standard merging algorithm to merge sub arrays back into d 
    i = 0; 
    j = 0; 
	//k starts at leftIdx b/c the sub arrays won't always start at beginning of d
    k = leftIdx; 
    while (i < endLeft && j < endRight) 
    { 
        if (left[i] <= right[j]) 
        { 
            d[k] = left[i]; 
            i++; 
        } 
        else
        { 
            d[k] = right[j]; 
            j++; 
        } 
		//always increment d loop counter
        k++; 
    } 
  
    // copy remaining elements from left sub array
    while (i < endLeft) 
    { 
        d[k] = left[i]; 
        i++; 
        k++; 
    } 
  
    // copy remaining elements from right sub array
    while (j < endRight) 
    { 
        d[k] = right[j]; 
        j++; 
        k++; 
    } 
} 

//mergeSort without using recursion
void mergeSort(vector<int> &d)
{
	int rightEnd;
	//for the size of the subarray to be sorted at each pass
	int currentSize; 
    //start index for the left sub array				   
   int leftStart; 
   // mid is the end of the first sub array (mid + 1 is start of right sub array)
  int mid;
   // Merge subdays in bottom up manner.  First merge subdays of 
   // size 1 to create sorted subdays of size 2, then merge subdays 
   // of size 2 to create sorted subdays of size 4, and so on. 
   for (currentSize=1; currentSize< d.size(); currentSize = 2*currentSize) 
   { 
       // Pick starting point of different subdays of current size 
       for (leftStart=0; leftStart<d.size()-1; leftStart += 2*currentSize) 
       { 
           // Find ending point of left subday. mid+1 is starting  
           // point of right 
           mid = leftStart + currentSize - 1; 
		   
		    // set right end to the minimum of either the end of the vector or the end of the sub array
			//this ensures if the end of the array is reached it will not go out of bounds
			if(leftStart + (2 * currentSize) - 1 < d.size() - 1)
				rightEnd = leftStart + 2 * currentSize - 1;
			else
				rightEnd = d.size()-1; 
  
           // helper function to merge the two subarrays back into d 
           merge(d, leftStart, mid, rightEnd); 
       } 
   } 
}

//helper method to clear buckets for radixSort
void clearBuckets(vector<vector<int> > &buckets)
{
	for(int count = 0; count < buckets.size(); count++)
	{
	  while(buckets[count].size() > 0)
		  buckets[count].pop_back();
	}
}
//numDigits tells the maximal digits of all the intergers you are sorting 
void radixSort(vector<int> & d, int numDigits)
{
int BUCKETS =10;
vector<vector<int> > buckets(BUCKETS);

  int place = 1;
  int sort, i, j, k;
  
  //sort according to ones digit
  for(int loop = 0; loop < numDigits; loop++)
  {
  
	for(i = 0; i < d.size(); i++)
	{
	  sort = (d[i] / place) % 10;
	  buckets[sort].push_back(d[i]);
	}
  
  //put back into original list
  //k is index in d
  k = 0;
  for(i = 0; i < buckets.size(); i++)
  {
	 for(j = 0; j < buckets[i].size(); j++)
	 {
		 d[k] = buckets[i][j];
		 // remove buckets[i][j] here?
		 k++;
	 }
  }
  
  //clear buckets, if individual value can be removed in above loop no need for this.
  clearBuckets(buckets);
  
  //increment digit to be sorted by (1s, 10s, 100s, 1000s)
  place*= 10;
  
  }
  
}



int main() 
{ 

  ifstream dataFile;
  vector<int> data1, data2;
  int num;
  int  maxDigits =4;

  // READING NUMBERS FROM A FILE
  dataFile.open("data3.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      {
      data1.push_back(num);
      data2.push_back(num);
      }
  dataFile.close();

  mergeSort(data1);
  showData(data1);

  radixSort(data2, maxDigits);
  showData(data2);
  
  return 0; 
  
} 
