#include <bits/stdc++.h>


using namespace std;
//name space std;


class Node
{
    public:
  
    int weight; 			        //weight of the node.
    Node* parent;			        //parent of the node(only one parent is possible)
    int post_order_number;
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
        node->post_order_number = node_number;
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
        obj = new ObjectL1(root, find_mv(root), nullptr, node_number+1);
        else
        obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number+1);

        node_number += 1;
        vec.push_back(obj);
        return;
    }

    //base case2: when the node is the leaf node.
    if((root->node_child).size() == 0){
        //cout<<"leaf node\n";
        ObjectL1* obj;

        if(node_number == 0)
        obj = new ObjectL1(root, find_mv(root), nullptr, node_number+1);
        else
        obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number+1);
        
        node_number += 1;
        vec.push_back(obj);
        return;
    }

    //recursive program.
    int size = (root->node_child).size();
    for(int i=0; i< size; i++){
        L1((root->node_child)[i], vec, node_number);
    }
    ObjectL1* obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number+1);
    node_number += 1;
    vec.push_back(obj);
    return;
}

int distance(Node* x, Node* u, vector<Edge*> edge_vector){

    Node* child = x;
    Node* parent = child->parent;
    int dist = 0;
    int  =0;
    while(parent!=u ){
        y = search_edge(child, parent, edge_vector);
        dist += x;
        child = parent;
        parent = child->parent;
    }

    y = search_edge(child, parent, edge_vector);
    dist += y;
    return dist;
    

}

int search_edge(Node* x, Node* u, vector<Edge*> edge_vector){//search whether an edge is present or not.

    int size = edge_vector.size();
    Edge* obj;
    if(size ==0)
    return -1;
    for(int i=0; i<size; i++){
        obj = edge_vector[i];
        Node* a = obj->firstNode;
        Node* b = obj->secondNode;
        if(a==x && b==u)
        return obj->length;
    }
    return -1;
}

void T_uv_Zero(Node* v, Node* u, int &value)
{
    //base case
    int size = (v->node_child).size();
    if(size==0){
        value += distance(v, u, edge_vector) * (v->weight);
        return ;
    }

    for(int i=0; i<size; i++){
        T_uv_Zero(node_child[i], u, value);
    }
    value += distance(v, u, edge_vector) * (v->weight);
    return;
}

int Tv1(Node* root, Node* Mv, vector<ObjectL1*> nodesFinal, vector<Edge*> edges) 
{
	int mv=Mv->postOrderNumber;
    int v=root->postOrderNumber;
    int d=0;
    for(int i=mv;i<v;i++)
    {
        
        Node* parent=Mv->parent;
        while(parent!=Root)
        {
            d+=distance(nodesFinal[i-1]->node, root, edges);      //add distance of child to parent
        }
    }
	return d;
}

int Ruv1(int v, int u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)
{
    ans=0;
    for(int i=v;i<u;i++)
    {
        int w=nodesFinal[i]->node->weight;
        ans+=w*distance(nodesFinal[i]->node, nodesFinal[u-1]->node, edges);
    }
    return ans;
}

int Luv0(int v, int u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)
{
    ans=0;
    int mv=nodesFinal[v-1]->mv;
    int mu=nodesFinal[u-1]->mv;
    for(int i=mu;i<mv-1;i++)
    {
        int w=nodesFinal[i]->node->weight;
        ans+=w*distance(nodesFinal[i]->node, nodesFinal[u-1]->node, edges);
    }
    return ans;
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
void addEdge(vector<int> adj[], int u, int v) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u); 
} 
  
// A utility function to print the adjacency list 
// representation of graph 
void printGraph(vector<int> adj[], int V) 
{ 
    for (int v = 0; v < V; ++v) 
    { 
        cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        for (auto x : adj[v]) 
           cout << "-> " << x; 
        printf("\n"); 
    } 
} 
int main() 
{
// your code goes here
	// Node* null_node = new Node(-1, NULL);
	//////////////////INPUT START///////////////////////
    int n=1000;
    vector<int> adj[n]; 
for(int i=0;i<n;i++)
{
    addEdge()
}
	// int n=7;   
	vector<Node*> nodes;
	Node* root = new Node(0, nullptr);
	nodes.push_back(root);
    Node* one = new Node(1, root);
    nodes.push_back(one);
    Node* two = new Node(2, root);
    nodes.push_back(two);
    Node* three = new Node(3, root);
    nodes.push_back(three);
    Node* four = new Node(4, root);
    nodes.push_back(four);
    Node* five = new Node(5, root);
    nodes.push_back(five);
    (root->node_child).push_back(one) ;
    (root->node_child).push_back(two) ;
    (root->node_child).push_back(three) ;
    (root->node_child).push_back(four);
    (root->node_child).push_back(five) ;
    Node* six = new Node(6, one);
    nodes.push_back(six);
    Node* seven = new Node(7, one);
    nodes.push_back(seven);
    (one->node_child).push_back(six);
    (one->node_child).push_back(seven);
    

	
    int graph[n][n];				//Adjaceny matrix of the tree
    
    // cin>>n;
    graph[1][0]=10;
    graph[2][0]=20;
    graph[3][0]=30;
    graph[4][0]=40;
    graph[5][0]=50;
    graph[6][1]=60;
    graph[7][1]=70;

    vector<vector<int>> graph1;
    vector<Edge*> edges;                //VECTOR CONTAINING EDGES
    for (int i = 0; i < n; i++)
    {
    	/* code */
        vector<int> v;
    	for (int i1 = 0; i1 < count; i1++)
    	{
    		/* code */
    		v.push_back(graph[i][i1]);
    		if(graph[i][i1]!=0)
    		{
    			Edge* e=new Edge(graph[i][i1], nodes[i], nodes[i1]);
    			edges.push_back(e);
    		}

    	}
        v.push_back(v);
    }
/////////////////////////////////INPUT OVER//////////////////////////////////////////////

/////////////////////////////////////L1//////////////////////////////////////////
    vector<ObjectL1*> vec;				//vector conataining nodes in post order
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
	cout<<"node number: "<<node_number<<endl;
        cout<<"post_order_number: "<<(obj->node)->post_order_number<<endl<<endl;
    }
    cout<<"size of vec is "<<vec.size()<<endl;
    for(int i=0;i<vec.size();i++)
    {
    	
    	cout<<"node "<<vec[i]->node->weight<<"number is"<<vec[i]->node_number;
    	if(vec[i]->node->parent!=nullptr)
    	cout<<" with its parent as "<<vec[i]->node->parent->weight;
    	cout<<endl;
    }
///////////////////////////////////////////L1////////////////////////////////
///////////////////////////////////////////L2/////////////////////////////////////
    int vec1[vec.size()];
    for (int u = 0; u < vec.size();u++)
    {
//////////////////////////////////////////////L2//////////////////////////
//////////////////////////////////////////////L3//////////////////////////
        int mvOfU=vec[u]->mv;
        for(int v=mv-1;v<u;v++)                 //v belongs to Tu
        {
            int mvv=vec[v]->mv;
            
//CHECK: if mv of some node is at mv-1 then only do the below
            int Tv11=Tv1(vec[v]->node, vec[vec[v]->mv-1],vec, edges);		//take inputs the length of each edge and prepare a adjacency matrix for that
                                            //also prepare a vector of weights of vertices
            int valTuv0=0;
            T_uv_Zero(vec[v]->node, vec[u],valTuv0 );    //value of valTuv0 is updated
            
            int ruv1=Ruv1(v, u, vec, edges);
            int luv0=Luv0(v, u,vec, edges);
        }
///////////////////////////////////////////////L3/////////////////////////
///////////////////////////////////////////////L4/////////////////////////
        for(int t=2;t<=k;t++)
        {
            int mvv=vec[u]->mv;
            ///////////////////////////////////L4//////////////////////
///////////////////////////////////////////////L5/////////////////////////////////////////            
            for (int v=mvv+1; v <=u-1 ; v++)
            {
///////////////////////////////////////////////L5//////////////////////////////////////////
///////////////////////////////////////////////L6//////////////////////////////////////////
                /* code */
                int mv=vec[v-1]->mv;
                if(v==mv)
                {
                    int luvt1=Luvt1;
                }

            }
///////////////////////////////////////////////L6///////////////////////////////////////////////            
///////////////////////////////////////////////L7/////////////////////////////////////////////
            int tut=Tut;
///////////////////////////////////////////////L7///////////////////////////////
        }

///////////////////////////////////////////////L8//////////////////////////
//CHECK: how to calculate Tvt for v=[1, u] & t=[1,k]            
        vec<int> valuesOfTvt;
        for (int v = 1; v <=u; v++)
        {
            /* code */
            for (int t = 1; t <=k; t++)
            {
                /* code */
                int tvt=Tut;
                valuesofTvt.push_back(tvt);
            }   
        }        
    }
////////////////////////////////////////////////L8/////////////////////////////
    


		
return 0;
}
