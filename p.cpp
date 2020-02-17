#include <iostream>
#include <vector>

using namespace std;

class Node
{
    public:
  
    int weight; 
    Node* parent;
    
    vector<Node*> chlid;
    Node(int weight, Node* parent)
    {
        this.weight=weight;
        this.parent=parent;
    }
  
    void add(Node* node)
    {
        child.push_back(node);
    }
}
class Edge
{
public:
	int length;
	Node* firstNode;
	Node* secondNode;
	
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
	Node* root;
	vector<Node*> child;
	Tree(Node* root)
	{	
		this.root=root;
	}
	
	void add(Node* node)
	{
		child.push_back(node);
	}
}

int main() 
{
// your code goes here
	int n; cin>>n;

	int graph[n][n];
	for(int i1=0;i1<n;i1++)
	{
		for(int j1=0;j1<n;j1++)
		{
		  int x; cin>>x;

		  graph[i1][j1]=x;
	}
	vector<int> weights;
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
