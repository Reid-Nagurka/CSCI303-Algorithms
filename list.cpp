//Reid Nagurka
#include <iostream> 
#include<fstream>
#include <list> 
#include <iterator> 
using namespace std; 
  
//function for printing the elements in a list 
void showlist(list <int> g) 
{ 
    list <int> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n'; 
} 

void list_intersection(list <int> & l1,list <int> & l2, list <int> & l3)
{
	/*algorithm:
	iterate through both lists.
	compare elements at the same iteration
	(1) if there is a common element, add that to l3 and increment iterator for both
	if no common element:
		(2) if element in l1 > element in l2, increment iterator for l2 and repeat
		(3) else do the opposite
	*/

  list <int> :: iterator it1;
  list <int> :: iterator it2;
  it1 = l1.begin(); it2 = l2.begin();
  //while both iterators have not reached the end
  while(it1 != l1.end() && it2 != l2.end())
  {
	  // (1) - from algorithm above
	  if (*it1 == *it2)
	  {
		l3.push_back(*it1);
		it1++; it2++;
	  }
	  // (2)
	  else if(*it1 > *it2)
	  {
		  it2++;
	  }
	  // (3)
	  else 
	  {
		  it1++;
	  }
  }
  

}

void list_union(list <int> & l1,list <int> & l2, list <int> & l3)
{
  
  /* algorithm:
  iterate through both lists
  if the element is in both lists, add one and increment both
  else if element in l1 is smaller, add that and increment it1
  else add *it2 and increment it2
  */
  
  list <int> :: iterator it1;
  list <int> :: iterator it2;
  it1 = l1.begin(); it2 = l2.begin();
  //while both iterators have not reached the end
  while(it1 != l1.end() && it2 != l2.end())
  {
	  // if in both
	  if (*it1 == *it2)
	  {
		l3.push_back(*it1);
		it1++; it2++;
	  }
	  // if the element in l1 is smaller
	  else if(*it1 < *it2)
	  {
		  l3.push_back(*it1);
		  it1++;
	  }
	  // if the element in l2 is smaller
	  else 
	  {
		  l3.push_back(*it2);
		  it2++;
	  }
  }

}
  
int main() 
{ 

  ifstream dataFile;
  list<int> list1, list2, list3, list4;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data1.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      list1.push_back(num);
 
  dataFile.close();


  dataFile.open("data2.txt");

  if (dataFile.is_open())
    while (dataFile>>num)
      list2.push_back(num);

  dataFile.close();


  list1.sort();
  list2.sort();

  list_intersection(list1,list2,list3);
  showlist(list3);

  list_union(list1,list2,list4);
  showlist(list4);


    return 0; 
  
} 