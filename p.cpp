#include <iostream>
#include <vector>

using namespace std;

class Node
{
    public:
  
    int weight; 			//weight of the node.
    Node* parent;			//parent of the node(only one parent is possible)
    
    vector<Node*> node_child;		//vector to store the children of the node.
	
    Node(int weight, Node* parent)	//constructor
    {
        this.weight=weight;
        this.parent=parent;
    }
  
    void add_child_in_node(Node* node)	//function to add the children of the node to a vector.
    {
        node_child.push_back(node);
    }
}

class Edge
{
public:
	int length;			//length of the edge.
	Node* firstNode;		//first node attached to the edge.
	Node* secondNode;		//second node attached to the edge.
	
	//constructor of the class Edge
	Edge(int length, Node* firstNode ,Node* secondNode)
	{
		this.length=length;
		this.firstNode=firstNode;
		this.secondNode=secondNode;
	}
}


class Tree
{
public:
	Node* root;			//root of the tree
	vector<Node*> tree_child;	//vector to store the elements of the tree.
	
	Tree(Node* root)		//constructor
	{	
		this.root=root;
	}
	
	//function to add nodes in tree
	void add_in_tree(Node* node)
	{
		tree_child.push_back(node);
	}
}

int main() 
{
// your code goes here
	int n; cin>>n;

	int graph[n][n]; 					//THIS IS DIRECTED TREE
	for(int i1=0;i1<n;i1++)
	{
		for(int j1=0;j1<n;j1++)
		{
		  int x; cin>>x;

		  graph[i1][j1]=x;
	}
	vector<int> weights; 					//WEIGHT OF EACH NODE
	for(int i11=0;i11<n;i11++)
	{
		int x;
		cin>>x;
		weights.push_back(x);
	}
	if(weights.size()!=0)
	{
		Node* root=new Root(weights[0]);

		Tree* tree=new Tree(root);	
			
	}
	else return -1;
}

		
return 0;
}
