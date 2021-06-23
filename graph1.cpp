
/*==================
Your Name: Reid Nagurka
Your Login ID: rgnag
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <list> 
#include <iterator>
#include <queue> 
using namespace std; 

//add an edge (u1, u2) to adjacency list
void add_edge(vector<list<int> > & adj_list, int u1, int u2)
{
  adj_list[u1].push_back(u2);
}

void topological(vector<list<int> > & adj_list, vector<int> & indegree, vector<int> & marked)
{
	cout<<"topological ordering: ";
	queue<int> q;
	int v;
	//add all vertexes with indegree 0 to the queue
	for(int i = 0; i < indegree.size(); i++)
	{
		if(indegree[i] == 0)
			q.push(indegree[i]);
	}
	
	//while the queue is not empty
	while(!q.empty())
	{
		//get v
		v = q.front();
		q.pop();
		//if unmarked
		if(!marked[v])
		{
			//print v, mark v
			cout<<v<<" ";
			marked[v] = 1;
		}
		//for every edge, decrement indegree, if one of those becomes 0, add to queue
		for (auto x : adj_list[v]) 
		{
			indegree[x]--;
			if(indegree[x] == 0)
				q.push(x);
		}
		
	}
}


int main()
{

  ifstream dataFile;
  int NUM_VERTICES, v1, v2;

  //reading graph data 
  dataFile.open("gdata1.txt");

  if (!dataFile.is_open()) return 0;

  //first line of gdata.txt is number of vertices in the graph
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<"The graph has "<<NUM_VERTICES<<" vertices."<<endl;

/*
declare adjacency list and adjacency matrix. 
marked is for graph traversal
*/

  vector<list<int> > adj_list(NUM_VERTICES);
  vector<int> marked(NUM_VERTICES);

  
  while ((dataFile>>v1) && (dataFile>>v2))
    add_edge(adj_list, v1, v2);

 dataFile.close();
 
  for (int i=0; i<NUM_VERTICES; i++)
   marked[i]=0;

 vector<int> indegree;
 for(int i = 0; i < NUM_VERTICES; i++)
	  indegree.push_back(0);
 
  
  //showgraph, adds 1 to the index of each j value in (i, j), as that is how many indegrees there will be
  cout<<endl;
  for(int i=0; i<adj_list.size(); i++)
    {
      for (auto j : adj_list[i])
	  {
		cout<<"("<<i<<","<<j<<") ";
		indegree[j]++;
	  }
      cout<<endl;
	}
	
	
 //indegree[x] has number of indegrees for vertex x, etc.

 topological(adj_list, indegree, marked);

 return 0; 

}