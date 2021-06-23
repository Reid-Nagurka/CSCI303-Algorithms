
/*==================
Your Name: Reid Nagurka
Your Login ID: rgnag
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <list> 
#include <iterator> 
#include <stack>
#include <queue>
using namespace std; 

//add an edge (u1, u2) to adjacency list
void add_edge(vector<list<int> > & adj_list, int u1, int u2)
{
  adj_list[u1].push_back(u2);
  adj_list[u2].push_back(u1);
}

//recursively traverse the graph
void traverse(vector<list<int> > & adj_list, vector<int> & marked, int v)
{
  if (marked[v]==1) return;
  cout<<v<<" ";
  marked[v]=1;

  for(auto x : adj_list[v])
    traverse(adj_list, marked, x);

}

//use non-recursive method to implement bfs
void bfs(vector<list<int> > & adj_list, int v)
{
	cout<<"BFS: ";
	queue<int> q;
	int size = adj_list.size();
	vector<int> marked(size);
	
	//make everything unmarked
	for (int i=0; i<size; i++)
		marked[i]=0;
	//put first element in bag
	
	q.push(v);
	
	//while the bag is not empty
	while(!q.empty())
	{
		//take v from bag
		v = q.front();
		q.pop();
		
		//if v is unmarked
		if(!marked[v])
		{
			cout<<v<< " ";
			//mark v 
			marked[v] = 1;
			
			//for each (v,w) put (v, w) into bag
			for (auto x : adj_list[v]) 
			{
				q.push(x);
			}
		}
		
	}
	
	
	//account for unconnected
	for (auto x : adj_list[v]) 
	{
		if(!marked[x])
			cout<<x<<" ";
	}
	
}

//use non-recursive method to implement dfs
void dfs(vector<list<int> > & adj_list, int v)
{
	cout<<"DFS: ";
	stack<int> stack;
	int size = adj_list.size();
	vector<int> marked(size);
	
	//make everything unmarked
	for (int i=0; i<size; i++)
		marked[i]=0;
	//put first element in bag
	
	stack.push(v);
	
	//while the bag is not empty
	while(!stack.empty())
	{
		//take v from bag
		v = stack.top();
		stack.pop();
		
		//if v is unmarked
		if(!marked[v])
		{
			cout<<v<< " ";
			//mark v 
			marked[v] = 1;
			
			//for each (v,w) put (v, w) into bag
			for (auto x : adj_list[v]) 
			{
					stack.push(x);
			}
		}
		
	}
	
	//account for unconnected
	for (auto x : adj_list[v]) 
	{
		if(!marked[x])
			cout<<x<<" ";
	}
	
}



//fill in the adjacency matrix based on adjacency list
void convert2matrix(vector<list<int> > & adj_list, vector<vector<int> > & adj_matrix)
{
	//traverse the adj_list
	for(int i=0; i<adj_list.size(); i++)
	{
		for (auto j : adj_list[i])
		{
			//assign matrix value accordingly
			adj_matrix[i][j] = 1;
		}
	}
	
	
	

}

//show a square matrix NxN
void show_matrix( vector<vector<int> > & matrix)
{
    cout<<endl;
    for(int i=0; i<matrix.size(); i++)
    {
      for (int j=0; j<matrix.size(); j++)
	cout<<matrix[i][j]<<" ";
      cout<<endl;
    }

}

// print out all edges from adjacency list
void show_graph(vector<list<int> > & adj_list)
{
  cout<<endl;
  for(int i=0; i<adj_list.size(); i++)
    {
      for (auto j : adj_list[i])
	cout<<"("<<i<<","<<j<<") ";
      cout<<endl;
}
}

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2;

  //reading graph data 
  dataFile.open("gdata.txt");

  if (!dataFile.is_open()) return 0;

  //first line of gdata.txt is number of vertices in the graph
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<"The graph has "<<NUM_VERTICES<<" vertices."<<endl;

/*
declare adjacency list and adjacency matrix. 
marked is for graph traversal
*/

  vector<list<int> > adj_list(NUM_VERTICES);
  vector<vector<int> > adj_matrix(NUM_VERTICES, vector<int> (NUM_VERTICES, 0) );
  vector<int> marked(NUM_VERTICES);

  while ((dataFile>>v1) && (dataFile>>v2))
    add_edge(adj_list, v1, v2);

 dataFile.close();

 for (int i=0; i<NUM_VERTICES; i++)
   marked[i]=0;

 traverse(adj_list, marked, 0);
 show_graph(adj_list);

 dfs(adj_list, 0);
 bfs(adj_list, 0);

 convert2matrix(adj_list, adj_matrix);
 show_matrix(adj_matrix);

 return 0; 
  
} 