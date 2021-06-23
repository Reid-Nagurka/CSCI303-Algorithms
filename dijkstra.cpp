
/*==================
Your Name: Reid Nagurka
Your Login ID: rgnag
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <list> 
#include <iterator> 
#include <utility>
#include <queue>
using namespace std; 

struct edge
{
  int out; //end vertex of the edge 
  int weight; //edge weight
};

struct Vertex
{
  list <edge> adj; //adjacency list
  bool known; //known shortest path?
  int dist; //shortest path distance
  int path; //pevious vertex in shortest path
  int heap_pos; //where is the vertex in the heap
};

void dijkstra(vector<Vertex> & nodes, int s)
{	
	int infinity = 10000;
	for(int i = 0; i < nodes.size(); i++)
	{
		nodes[i].dist = infinity;
		nodes[i].known = false;
		nodes[i].path = -1;
	}
	//int pair
	pair <int, int> p1;
	//make a priority queue with a pairs for elements
	priority_queue<pair<int, int>, vector <pair<int, int> >, greater <pair<int, int>> > heap;
	
	//push 0 for distance and s for the 0th vertex
	heap.push(make_pair(0, s));
	
	nodes[s].dist = 0;
	Vertex v = nodes[s];
	
	while(!heap.empty())
	{
		//x is the vertex number (0, 1, 2...)
		
		int x = heap.top().second;
		heap.pop();
		//mark the vertex at w index as known
		nodes[x].known = true;
		//use temporary Vertex v for ease, v is the index of the minimum unknown vertex
		v = nodes[x];
		
		//get all adjacent vertices, use adjacency list of v 
		list<edge> :: iterator it;
		for(it = v.adj.begin(); it != v.adj.end(); it++)
		{
			//w is the end vertex of the current edge 
			int w = it->out;
			int weight = it->weight;
			//make sure vertex is unknown
			if(!nodes[w].known)
			{
				if( v.dist + weight < nodes[w].dist)
				{
					//update w
					nodes[w].dist = v.dist + weight;
					nodes[w].path = x;
					//make a pair of w's distance and w (dist and index) and add to heap
					heap.push(make_pair(nodes[w].dist, w));
				}
			}
		}
	}

}

void show_graph(vector<Vertex> & nodes)
{
  cout<<endl;
  for(int i=0; i<nodes.size(); i++)
    {
      for (auto j : nodes[i].adj)
	cout<<"("<<i<<","<<j.out<<") "<<j.weight<<endl;
    }
}

//print the path for node v
void print_path(vector<Vertex> & nodes, int v)
{
  if (nodes[v].path>=0) print_path(nodes, nodes[v].path);
  cout<<v<<" ";
}

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2, v3;

  dataFile.open("gdata2.txt");

  if (!dataFile.is_open()) return 0;
 
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<NUM_VERTICES<<endl;

  vector<Vertex> nodes(NUM_VERTICES);



  while ((dataFile>>v1) && (dataFile>>v2) && (dataFile>>v3))
    {
      edge e;
      e.out = v2;
      e.weight = v3;
      nodes[v1].adj.push_back(e);
      cout<<v1<<" "<<v2<<" "<<e.weight<<endl; 	 
      }

 dataFile.close();


 show_graph(nodes);

 //run dijkstra
 dijkstra(nodes, 0);

 //print out paths
 for(int i=0; i<nodes.size(); i++)
   {
     print_path(nodes, i);
     cout<<endl;
   }

 return 0; 
 
} 