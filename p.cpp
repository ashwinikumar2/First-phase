#include <bits/stdc++.h>


using namespace std;



class Node
{
    public:
  
    int weight; 			        //weight of the node.
    Node* parent;			        //parent of the node(only one parent is possible)
    
    vector<Node*> node_child;		//vector to store the children of the node.
	
    Node(int weight, Node* parent)	//constructor
    {
        this->weight = weight;
        this->parent = parent;
    }
  
    void add_child_in_node(Node* node)	//function to add the children of the node to a vector.
    {
        node_child.push_back(node);
    }
};

class Edge
{
public:
	int length;			                //length of the edge.
	Node* firstNode;		            //first node attached to the edge.
	Node* secondNode;		            //second node attached to the edge.
	
	//constructor of the class Edge
	Edge(int length, Node* firstNode ,Node* secondNode)
	{
		this->length = length;
		this->firstNode = firstNode;
		this->secondNode = secondNode;
	}
};


class Tree
{
public:
	Node* root;			    //root of the tree
	vector<Node*> tree_child;	//vector to store the elements of the tree.
	
	Tree(Node* root)		//constructor
	{	
		this->root = root;
	}
	
	//function to add nodes in tree
	void add_in_tree(Node* node)
	{
		tree_child.push_back(node);
	}
};

class ObjectL1
{
public:
    Node* node;     //reference node. 
    int node_number;    
    Node* mv;       // Node mv
    Node* mv_prime; //Node mv' 

    ObjectL1(Node* node, Node* mv, Node* mv_prime, int node_number)
    {
        this->node = node;
        this->mv = mv;
        this->mv_prime = mv_prime;
        this->node_number = node_number;
    }

};

Node* find_mv(Node* current_node)
{
    if((current_node->node_child).size() == 0){
        return current_node;
    }
    
    return find_mv((current_node->node_child)[0]);
}

void L1(Node* root, vector<ObjectL1*> &vec, int &node_number)    //array is passed by reference.
{
    //base case1: when the only node is root

    // cout<<"into the loop\n";
    // cout<<"node_number"<<node_number<<endl;
    if((root->node_child).size() == 0 &&  (root->parent) == nullptr){
        // cout<<"only root\n";
        ObjectL1* obj ;
        if(node_number == 0)
        obj = new ObjectL1(root, find_mv(root), nullptr, node_number);
        else
        obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number);

        node_number += 1;
        vec.push_back(obj);
        return;
    }
    
    //base case2: when the node is the leaf node.
    if((root->node_child).size() == 0){
        //cout<<"leaf node\n";
        ObjectL1* obj;

        if(node_number == 0)
        obj = new ObjectL1(root, find_mv(root), nullptr, node_number);
        else
        obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number);
        
        node_number += 1;
        vec.push_back(obj);
        return;
    }

    //recursive program.
    int size = (root->node_child).size();
    for(int i=0; i< size; i++){
        L1((root->node_child)[i], vec, node_number);
    }
    ObjectL1* obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number);
    node_number += 1;
    vec.push_back(obj);
    return;
}

/*
int main() 
{
// your code goes here
	
	//////////////////////////////INPUT STARTS////////////////////////////////////////////////
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
		
	///////////////////////////////INPUT OVER///////////////////////////////////////////////////////
	if(n!=0)					//if Number of nodes are >0 (Obviously)
	{
		Node* root=new Root(weights[0]);

		Tree* tree=new Tree(root);
		//Post-Order Traversal							
		ObjectL1 postOrderTraversal[n]=L1(graph*);		//Create a class ObjectL1. THIS OBJECT CONTAINS A NODE(REFERENCE), Mv, Mv'
									//An array made of objects of class ObjectL1 is returned
		
		
			
	}
	else return -1;
}

		
return 0;
}
*/

//this main is to test the L1 function
int main() 
{
// your code goes here
	// Node* null_node = new Node(-1, NULL);
	Node* root = new Node(0, nullptr);
    Node* one = new Node(1, root);
    Node* two = new Node(2, root);
    Node* three = new Node(3, root);
    Node* four = new Node(4, root);
    Node* five = new Node(5, root);
    (root->node_child).push_back(one) ;
    (root->node_child).push_back(two) ;
    (root->node_child).push_back(three) ;
    (root->node_child).push_back(four);
    (root->node_child).push_back(five) ;
    Node* six = new Node(6, one);
    Node* seven = new Node(7, one);
    (one->node_child).push_back(six);
    (one->node_child).push_back(seven);

    vector<ObjectL1*> vec;
    int node_number = 0;
    cout<<"start\n";
    L1(root, vec, node_number);
    int size = vec.size();
    if(size==node_number){
        cout<<"hurrah!\n";
    }
    for(int i=0; i<size; i++){
        ObjectL1* obj = vec[i];
        int wt = (obj->node)->weight;
        int wt1 = (obj->mv)->weight;
        int wt2;
        if(obj->mv_prime == nullptr)
        wt2 =-1;
        else
        wt2 = (obj->mv_prime)->weight;
        cout<<"weight of node: "<<wt<<"\n";
        cout<<"weight of mv: "<<wt1<<"\n";
        cout<<"weight of mv_prime: "<<wt2<<"\n";
    }

		
return 0;
}
