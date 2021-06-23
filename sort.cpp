
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

//merge d[low,middle] and d[middle+1,high]
void merge(vector<int> &d, int low, int middle, int high)
{
	//temporary vector 
	vector<int> temp;
	//copy d to temp.
	for(int i = 0; i < d.size(); i++)
		temp.push_back(d[i]);
	
	int i = low;
	int j = middle + 1;
	int k = low;
	
	while (i <= middle && j <= high)
	{
		//assign lower value to temp[k] and imcrement k
		if(d[i] < d[j])
		{
			temp[k++] = d[i++];
		}
		
		else
		{
			temp[k++] = d[j++];
		}
	
	}
	
	//copy remaining elements from left half to temp
	while(i <= middle)
	{
		temp[k++] = d[i++];
	}
	//copy remaining elements from right half to temp
	while(j <= high)
	{
		temp[k++] = d[j++];
	}
	//copy temp back to d
	for(int i = low; i <= high; i++)
	{
		d[i] = temp[i];
	}
}


void mergeSort(vector<int> &d, int low, int high)
{
  int middle;

  if(low < high)
	{
	  middle = (low + high) / 2;
	  mergeSort(d, low, middle);
	  mergeSort(d, middle+1, high);
	  
	  //merge the sorted into one sorted array
	 merge(d, low, middle, high);

	}
  
  //if(low == high)
	  //return;
  
}

//partition d[low,high] into (left, pivot, right)
//return the position of the pivot such that all smaller numbers 
// are on the left and all bigger numbers on the right
int partition(vector<int> &d, int low, int high)
{ 
	int i = low, j = high, temp;
	//set pivot to this b/c starting in the middle is good for avg run-time
	int pivot = d[(low + high) / 2]; 
	
	while(i < high)
	{
		while(d[i] < pivot)
		{
			i++;
		}
		
		while(d[j] > pivot)
		{
			j--;
		}
		
		if(i < j)
		{
			temp = d[i];
			d[i] = d[j];
			d[j] = temp;
		}
		else
		{
			temp = pivot;
			pivot = d[i];
			d[i] = temp;
			break;
		}
	}
	//the pivot should be in j now, and if not then
	//the last element will be used
	return j;
	
}

void quickSort(vector<int> &d, int low, int high)
{
	
	//int pivot = partition(d, low, high);
  int pivot;
  if(low < high)
  {
	  pivot = partition(d, low, high);
	  quickSort(d, low, pivot-1);
	  quickSort(d, pivot+1, high);
  }
  
}


int main() 
{ 
  ifstream dataFile;
  vector<int> data1, data2;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      {
      data1.push_back(num);
      data2.push_back(num);
      }
  dataFile.close();

  mergeSort(data1, 0, data1.size()-1);
  showData(data1);

  quickSort(data2, 0, data2.size()-1);
  showData(data2);

  return 0; 
  
} 