 /*==================
Your Name: Reid Nagurka
Your Login ID: rgnag
==================*/
#include <iostream> 
#include<fstream>
#include <vector> 
#include <list> 
using namespace std;

void printpretty(vector<vector<int>> & s, int i, int j, int &count)
{
	//if there is just one matrix in the chain, print it and increase count
	if(i == j)
	{
		cout<<"A"<<count;
		count++;
		return;
	}
	//find the breakpoint (calculated in optimalorder())
	int k = s[i][j];
	cout<<"(";
	//print up to first part of chain
	printpretty(s, i, k, count);
	//print second part of chain
	printpretty(s, k+1, j, count);
	cout<<")";
}

void optimalorder(vector<int> & c)
{
	//table is m in book and s is lastchange
	vector<vector <int> > table(c.size(), vector<int>(c.size()));
	vector<vector <int> > s(c.size(), vector<int>(c.size()));
	int i, j, left, k, cost, right;
	
	int n = c.size() - 1;

	//initalize matrices
	for(left = 1; left <= n; left++){
		table[left][left] = 0;
	}
	for(i = 0; i < s.size(); i++){
		for(j = 0; j < s[i].size(); j++){
			s[i][j] = 0;
		}
	}
	
	for(k = 1; k < n; k++) //k is right - left
	{
		for(left = 1; left <= n - k; left++)
		{
			//for each position
			right = left + k;
			table[left][right] = 9999;
			for(i = left; i < right; i++)
			{
				cost = table[left][i] + table[i+1][right] + c[left-1] * c[i] * c[right];
				if(cost < table[left][right])
				{
					table[left][right] = cost;
					//breakpoint for printing
					s[left][right] = i;
				}
			}
		}
	}
	//table[1][n] has the minimum multiplications
	cout<<"Number of multiplications: "<<table[1][n]<<"\n";
	//count is the matrix number, starts at 1 (A1, A2, A3...)
	int count = 1;
	//print the matrices with parantheses, starts at 1 b/c s is 1 indexed (from book) and goes through n
	printpretty(s, 1, n, count);
}

int main() 
{
  ifstream dataFile;
  int NUM_VERTICES, v1;

  //reading graph data 
  dataFile.open("mm-data.txt");

  if (!dataFile.is_open()) return 0;

  //first line of gdata.txt is number of vertices in the graph
  if (!(dataFile>>NUM_VERTICES)) return 0;

  //because it is 1 indexed, add on emore to the size to avoid out of bounds
  vector<int> v (NUM_VERTICES + 1);
  int i = 0;
  while ((dataFile>>v1))
  {
	  v[i] = v1;
	  i++;
  }

 dataFile.close();

optimalorder(v);

 return 0;
 
 }