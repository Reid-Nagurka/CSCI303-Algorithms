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

// To rebuild a subtree rooted with node i which is
// an index in d. size is size of heap
void rebuildHeap(vector<int> &d, int size, int i)
{

    int max = i; // Initialize biggest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2
 
    // If left child is bigger than root
    if (l < size && d[l] > d[max])
        max = l;
 
    // If right child is biggerer than biggest so far
    if (r < size && d[r] > d[max])
        max = r;
 
    // If biggest is not root
    if (max != i)
    {
        swap(d[i], d[max]);
 
        //Percolate: Recursively rebuild the affected sub-tree
        rebuildHeap(d, size, max);
    }
}
 
// heap sort
void heapSort(vector<int> &d)
{
  int size = d.size();

    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--)
        rebuildHeap(d, size, i);
 
    // get the biggest (root) element from heap
    for (int i=size-1; i>=0; i--)
    {
        // Move current root to end
        swap(d[0], d[i]);
 
        // call rebuild heap on the reduced heap
        rebuildHeap(d, i, 0);
    }
}
 

int main() 
{ 

  ifstream dataFile;
  vector<int> data;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      data.push_back(num);
 
  dataFile.close();

  heapSort(data);
  showData(data);


  return 0; 
  
} 

