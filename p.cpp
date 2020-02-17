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

class Tree
{
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
		
	
}

		
return 0;
}
