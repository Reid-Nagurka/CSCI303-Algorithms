
/*==================
Your Name: Reid Nagurka
Your Login ID: rgnag
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <iterator> 
using namespace std; 

void showHeap(vector<int> h)
{
  /*
    vector <int> :: iterator it; 
    for(it = h.begin(); it != h.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n';
  */

    for(int i=0; i < h.size(); ++i) 
        cout << '\t' << h[i]; 
    cout << '\n';

}


void buildHeap1(vector<int> &h1)
{
  //Insert integers one by one
  
  //if child index is known: parent index = (child - 1) / 2
  
	int copy, parent, i;
	
	for(int j = 1; j < h1.size(); j++)
	{
		int parent = (j - 1) / 2;
		
		int i = j;
		
		while (parent >= 0 && h1[i] < h1[parent])
		{
			//swap h[i] and h[parent]
			copy = h1[i];
			h1[i] = h1[parent];
			h1[parent] = copy;
			
			i = parent;
			parent = (i - 1) / 2;
		
		}
	}
}

void buildHeap2(vector<int> &h2)
{
  //Build a heap in linear time.
  int currentSize = h2.size() - 1;

 for(int i = currentSize / 2; i >= 0; i--)
  {
	  //percolatedown(i)
	  //i is the index at which the percolation begings (hole in book)
	  int child;
	  int temp = h2[i];
	  
	  for(; (i * 2) <= currentSize; i = child)
	  {
		  child = i * 2 ;
		 
		  //lower value will now be at index child
		if( child != currentSize && h2[ child +1]< h2[ child ] )
			++child;
		
		
		if( h2[ child ] < temp ) // temp should be the parent value
		{
			//swap child w/ parent
			h2[i] = h2[child];
			h2[child] = temp;
			
		}	
		else
			break;
	  }
	  
	  h2[i] = temp;
	
  }
	  
  
}


/*====================================================
Compare the running time of both algorithms in a and b 
for sorted, reverse-ordered, and random inputs. 

For random inputs, both have an average run-time of O(N).

For sorted, both algorithms have an average run-time of O(N).

For reverse-ordered (worst-case scenario), the first algorithm has O(NlogN) run-time, while the second algorithm has O(N) run-time.



====================================================*/


int findKthLargest(vector<int> &h, int k)
{
  // first build a heap with the first k numbers
  
  vector<int> copy; 
  for(int i = 0; i < k; i++)
  {
	  copy.push_back(h[i]);
  }
  
  buildHeap2(copy);
  //int parent = 0;
  
  	//compare the new number with the top and 
	  //decide whether we should insert the new number.
	for(int i = k; i < h.size(); i++)
	{
		//if the next element in h[i] is greater than the smallest number in copy
		if(h[i] > copy[0])
		{ 
			copy[0] = h[i];
			//puts the new element in proper heap order
			buildHeap2(copy);
		}
	}
	
  return copy[0];
}


//helper function to use Recursion for problem 1d 
void findAllLessThanXRecursive(vector<int> &h, int x, int idx, vector<int> &n)
{
	//check to make sure not out of bounds
	if(idx >= h.size())
		return;
	
	if(h[idx] < x)
	{
		//add to nodes for printing at end
		n.push_back(h[idx]);
		
		//left child:
		idx = idx * 2 + 1;
		findAllLessThanXRecursive(h, x, idx, n);
		
		//right child
		idx++;
		findAllLessThanXRecursive(h, x, idx, n);
	}
}

void findAllLessThanX(vector<int> &h, int x)
{
	
	//assume h is already sorted
	vector<int> nodes;
	
	//start from root of the heap
	int parent = 0;
	
	if(h[parent] < x)
	{
		findAllLessThanXRecursive(h, x, parent, nodes);
	}
	
	showHeap(nodes);	
}



int main() 
{ 

  ifstream dataFile;
  vector<int> heap, heap1, heap2;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      {
      heap.push_back(num);
      heap1.push_back(num);
      heap2.push_back(num);
      }
  dataFile.close();

  buildHeap1(heap1);
  showHeap(heap1);

  buildHeap2(heap2);
  showHeap(heap2);

  int k, x;
  cout<<"Please input a number k: ";
  cin>>k;

  cout<<k<<"-th largest number is "<<findKthLargest(heap,k)<<endl;

  cout<<"Please input a number X: ";
  cin>>x;
  findAllLessThanX(heap1, x);

  return 0; 
  
} 