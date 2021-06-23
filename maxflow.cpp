/*==================
Your Name: Reid Nagurka
Your Login ID: rgnag
==================*/
/*
//Edmond-Karp Algorithm

set f-total = 0
repeat until there is no path from s to t
{
run bfs from s to find a flow path to t
let f be the minimum capacity value on the path
for each edge (u,v) on the path
{
increase flow f(u,v) by f
f(v,u)=-f(u,v)
decrease c(u,v) by f
increase c(v,u) by f
}
}
 */

#include <iostream> 
#include <fstream>
#include <vector> 
#include <queue>
#include <list> 
#include <iterator> 
using namespace std; 


struct Edge
{
  int capacity; //edge capacity
  int residual_capacity;
  int flow;
};

struct Vertex
{
  bool visited; //has been visited in BFS?
  int path; //previous node on the path
};


//run breadth first search to find an augmenting path
void bfs(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int s, int t)
{
  queue<int> bfs_queue;

  for (int i=0; i< nodes.size(); i++)
    {
      nodes[i].visited = 0;
      nodes[i].path = -1;
    }

  nodes[s].visited = 1;
  bfs_queue.push(s);


  //put your program here
  while(!bfs_queue.empty())
  {
	  //front of queue
	  int front = bfs_queue.front();
	  //traverse the adjacenty matrix
	  for(int i = 0; i < adj_matrix[front].size(); i++)
	  {
		  //if the adjacency matrix has more capacity and has not been visited 
		  if(adj_matrix[front][i].capacity > 0 && nodes[i].visited == 0
			&& adj_matrix[front][i].residual_capacity > 0)
		  {
			//update path, mark as visited and push location onto queue
			nodes[i].path = front;
			nodes[i].visited = 1;
			bfs_queue.push(i);
		  }
	  }
	  bfs_queue.pop();
  }


}

//find max-flow by modifying residual_capacity and flow
void max_flow(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int s, int t)
{

  //put your program here
  //f in pseudocode
  int curr_flow = 9999;
  //used to traverse the flow path, begins at t but do not want to change t
  int currentnode;
  while(!(nodes[t].path==-1))
  {
	//run bfs to get path
	bfs(nodes, adj_matrix, s, t);
	currentnode = t;
	while(nodes[currentnode].path!=-1)
	{
		//if the residual capacity is less than the current flow 
		if(adj_matrix[nodes[currentnode].path][currentnode].residual_capacity < curr_flow)
		{
			//update the current flow to that residual capacity
			curr_flow = adj_matrix[nodes[currentnode].path][currentnode].residual_capacity;
		}
		//update the current node
		currentnode = nodes[currentnode].path;
	}
	currentnode = t;
	//for each edge (u,v) on the path
	while(!(nodes[currentnode].path==-1))
	{
		//increase flow f(u,v) by f
		adj_matrix[nodes[currentnode].path][currentnode].flow += curr_flow;
		//f(v,u)=-f(u,v)
		adj_matrix[currentnode][nodes[currentnode].path].flow = adj_matrix[nodes[currentnode].path][currentnode].flow;
		//decrease residual capacity c(u,v) by f
		adj_matrix[nodes[currentnode].path][currentnode].residual_capacity -= curr_flow;
		//increase c(v,u) by f
		adj_matrix[currentnode][nodes[currentnode].path].residual_capacity += curr_flow;
		//update currentnode to continue traversing each edge (u,v)
		currentnode = nodes[currentnode].path;
	}
  }
  

}

void show_graph(vector<vector<Edge> > adj_matrix)
{
  cout<<"comes show"<<endl;

  for (int i=0;i<adj_matrix.size();i++)
    {
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  cout<<"["<<i<<","<<j<<"] "<<adj_matrix[i][j].capacity<<" "<<adj_matrix[i][j].residual_capacity<<" "<< adj_matrix[i][j].flow<<endl;
	}

    }
}

// show flow on each edge and show total flow
void show_flow(vector<vector<Edge> > adj_matrix, int s)
{
  cout<<"Flow on each edge:"<<endl;

  for (int i=0;i<adj_matrix.size();i++)
    {
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  if (adj_matrix[i][j].flow > 0) 
	  cout<<"["<<i<<","<<j<<"] "<<adj_matrix[i][j].capacity<<" "<<adj_matrix[i][j].residual_capacity<<" "<< adj_matrix[i][j].flow<<endl;
	}

    }

  int flow=0;
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  if (adj_matrix[s][j].flow > 0) 
	    flow += adj_matrix[s][j].flow;
	}

      cout<<"Total flow is "<<flow<<endl;

}

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2, v3;

  dataFile.open("gdata4.txt");

  if (!dataFile.is_open()) return 0;
 
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<NUM_VERTICES<<endl;

  vector<Vertex> nodes(NUM_VERTICES);

  vector<vector<Edge> > adj_matrix(NUM_VERTICES);


  cout<<"here1"<<endl;

  int source=4, sink=NUM_VERTICES-1;

  for (int i=0;i<NUM_VERTICES;i++)
    {
  cout<<"here2"<<endl;

      adj_matrix[i] = vector<Edge> (NUM_VERTICES);

      for (int j=0; j< NUM_VERTICES; j++)
	{
	  adj_matrix[i][j].capacity=0;
	  adj_matrix[i][j].residual_capacity=0;
	  adj_matrix[i][j].flow=0;
	}

    }

  cout<<"here"<<endl;

  while ((dataFile>>v1) && (dataFile>>v2) && (dataFile>>v3))
    {

      adj_matrix[v1][v2].capacity=v3;
      adj_matrix[v1][v2].residual_capacity=v3;
      adj_matrix[v1][v2].flow=0;
      }

 dataFile.close();


 show_graph(adj_matrix);


 //run mst
 max_flow(nodes, adj_matrix, source, sink);

 
 show_flow(adj_matrix, source);

 return 0; 
 
} 