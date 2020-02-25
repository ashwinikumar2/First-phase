#include <bits/stdc++.h>
#include <fstream>
#include <string>
#define MAX_SIZE INT_MAX
using namespace std;
//name space std;


class Node
{
    public:
    int initialid; //initial id given in input file
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

int Luvt(int t, Node* v, Node* u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges);



Node* find_mv(Node* current_node)
{
    if((current_node->node_child).size() == 0){
        return current_node;
    }
    
    return find_mv((current_node->node_child)[0]);
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
    int  y=0;
    if(x==u){
        return 0;
    }
    while(parent!=u ){
        y = search_edge(child, parent, edge_vector);
        dist += y;
        child = parent;
        parent = child->parent;
    }

    y = search_edge(child, parent, edge_vector);
    dist += y;
    return dist;
    

}

int T_uv_Zero(Node* u, Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edge_vector)
{
    Node* Mv = find_mv(v);
    int i = Mv->post_order_number;
    int j = v->post_order_number;
    int ans = 0;

    for(int k=i; k<=j; k++){
        int wt = nodesFinal[k-1]->node->weight;
        ans += wt * distance(nodesFinal[k-1]->node, u, edge_vector);
    }
    return ans;

}

int Tv1(Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edges) 
{
    Node* Mv = find_mv(v);
	int mv = Mv->post_order_number;
    int j = v->post_order_number;
    int d = 0;
    for(int i = mv; i <= j; i++)
    {
        d += distance(nodesFinal[i-1]->node, v, edges) * nodesFinal[i-1]->node->weight;      //add distance of child to parent
    }

	return d;
}

int Ruv1(Node* u, Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)   //u: parent node;, v: child node
{
    int ans=0;
    int i = u->post_order_number;
    int j = v->post_order_number;

    for(int k=j+1;k<i;k++)
    {
        int w=nodesFinal[k-1]->node->weight;
        ans+=w * distance(nodesFinal[k-1]->node, u, edges);
    }
    return ans;
}

int Luv0(Node* u, Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)
{
    int ans=0;
    int i = v->post_order_number;
    int j = u->post_order_number;
    int mv=((nodesFinal[i-1])->mv)->post_order_number;
    int mu=((nodesFinal[j-1])->mv)->post_order_number;
    for(int k=mu; k<mv; k++)
    {
        int w=nodesFinal[k-1]->node->weight;
        ans+=w * distance(nodesFinal[k-1]->node, nodesFinal[j-1]->node, edges);
    }
    return ans;
}

int minimum(int a, int b){
    if(a<b)
    return a;
    else b;
}
int maximum(int a, int b){
    if(a<b)
    return b;
    return a;
}

int tree_size(int u, vector<ObjectL1* > vec)
{
    
    int mu = (vec[u-1])->mv->post_order_number;
    return u-mu+1;
}

int LuvSize(int u, int v, vector<ObjectL1*> nodesFinal){
    int mv = nodesFinal[v-1]->mv->post_order_number;
    int mu = nodesFinal[u-1]->mv->post_order_number;
    return mv-mu;
}


int T_u_t(int t, Node* u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)
{   
// cout<<"t: "<<t<<endl;
    if(t>= (u->post_order_number - find_mv(u)->post_order_number + 1))
    return 0;
    //base case.
    if(t == 1){
        int x = Tv1(u, nodesFinal, edges);
        return x;
    }

    //recursive
    int mu = find_mv(u)->post_order_number;
    int j = u->post_order_number;
    int y=MAX_SIZE;
    for(int i=mu; i<j; i++)
    {

        int x=MAX_SIZE;
        
        for(int l = maximum(1, t-1-LuvSize(j, i, nodesFinal)); l<minimum(t, tree_size(i,nodesFinal)); l++){
            // cout<<"l: "<<l<<endl;
            int a = T_u_t(l, (nodesFinal[i-1])->node, nodesFinal, edges);
            // cout<<"a: "<<a<<"  "<<"t-l-1: "<<t-l-1<<endl;
            a = a + Luvt(t-l-1, (nodesFinal[i-1])->node, u, nodesFinal, edges);
            // cout<<"a after Luvt: "<<a<<endl;
            a = a + Ruv1(u, (nodesFinal[i-1])->node, nodesFinal, edges);
            // cout<<"a after Ruv1: "<<a<<endl;
            if(a<x) x=a;


        }
        if(x<y)
        y=x;
    }

    return y;
}

int Luvt(int t, Node* v, Node* u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){
    //negative case
    if(t<0)
    return 0;

    if(t>= (find_mv(v)->post_order_number - find_mv(u)->post_order_number))
        return 0;

    //base case
    if(t==0){
        return Luv0(u, v, nodesFinal, edges);
    }
    int mu = find_mv(u)->post_order_number;
    int mv = find_mv(v)->post_order_number;
    int net_min =MAX_SIZE;
    for(int x=mu; x<mv; x++){
        int min = MAX_SIZE;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x, nodesFinal)); i<minimum(t, tree_size(x, nodesFinal)); i++){
            Node* ex = nodesFinal[x-1]->node;
            int a = T_u_t(i, ex, nodesFinal, edges);
            a = a + Luvt(t-i, ex, u, nodesFinal, edges);
            a = a + Ruv1(u, ex, nodesFinal, edges);
            a = a - Ruv1(u, v, nodesFinal, edges);
            a = a - T_uv_Zero(u, v, nodesFinal, edges);

            if(a<min)   min= a;
        }
        if(min<net_min) net_min = min;
    }
    // cout<<"happy"<<endl;
    if(net_min != MAX_SIZE)
    return net_min;
    // cout<<"see"<<endl;
    return 0;
}

int A_uvt(Node* u, Node* v, int t, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){

    int post_v = v->post_order_number;
    int a = Luvt(t, nodesFinal[post_v -1]->mv_prime, u, nodesFinal, edges);
    a = a + Ruv1(u, nodesFinal[post_v -1]->mv_prime, nodesFinal, edges);
    a = a + T_uv_Zero(u, nodesFinal[post_v -1]->mv_prime, nodesFinal, edges);
    a = a - Ruv1(u, v, nodesFinal, edges);
    a = a - T_uv_Zero(u, v, nodesFinal, edges);
    return a;

}

int B_uvt(Node* u, Node* v, int t, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){

    if(t>= (find_mv(v)->post_order_number - find_mv(u)->post_order_number))
        return 0;

    //base case
    if(t==0){
        return Luv0(u, v, nodesFinal, edges);
    }
    int mu = find_mv(u)->post_order_number;
    int mv = find_mv(v)->post_order_number;
    int net_min =MAX_SIZE;
    for(int x=mv-1; x<mv; x++){
        int min = MAX_SIZE;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x, nodesFinal)); i<minimum(t, tree_size(x, nodesFinal)); i++){
            Node* ex = nodesFinal[x-1]->node;
            int a = T_u_t(i, ex, nodesFinal, edges);
            a = a + Luvt(t-i, ex, u, nodesFinal, edges);
            a = a + Ruv1(u, ex, nodesFinal, edges);
            a = a - Ruv1(u, v, nodesFinal, edges);
            a = a - T_uv_Zero(u, v, nodesFinal, edges);

            if(a<min)   min= a;
        }
        if(min<net_min) net_min = min;
    }
    return net_min;

}

int L_uvt_theo3(Node* u, Node* v, int t, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){
    int a = A_uvt(u, v, t, nodesFinal, edges);
    int b = B_uvt(u, v, t, nodesFinal, edges);
    return minimum(a, b);
}

void Proxies(Node* u, int t, vector<ObjectL1*> vec, vector<edges> edge_vec)
{
    if(t==1)
    {
        cout<<u->post_order_number<<endl;
        return;
    }
    else
    {
        int mv=vec[u->post_order_number-1]->mv->post_order_number;      //post order no of Mv of u
        for(int v=mv;v<=u->post_order_number;v++)
        {
            int tv1=Tv1(vec[u->post_order_number-1]->node, vec, edge_vec);
            int tuv0=T_uv_Zero(u, vec[v-1]->node, vec, edge_vec);
            int ruv1=Ruv1(u,  vec[v-1]->node, vec, edge_vec);
            int luv0=Luv0(u,  vec[v-1]->node, vec, edge_vec);


        }

        for(int t=2;t<=k;t++)
        {
            for(int v=mv;v<=u->post_order_number;v++)
            {
                if(v==mv)
                {
                    int luvtt=L_uvt_theo3(u,  vec[v-1]->node,t-1, vec, edge_vec);
                    //Calculate x and c

                }
            }
        }


    }


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
        	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	        // int n=1000;
            // vector<int> adj[n]; 	
	        // vector<Node*> allnodes;	
	        // for(int i=0; i<1000; i++)	
	        // {	
	        //     Node* n = new Node(-1, nullptr);	
	        //     (n->initialid) = i;	
	        //     allnodes.push_back(n);	
	        // }	
	        // //taking inputs start	
	        // int k = 10;//edge value	
	        // ifstream infile; //taking input of all parent-child nodes	
	        // infile.open("/home/ash/Downloads/trace.tree", in);	
	        // string line;	
	        // while(getline(infile, line))	
	        // {	
	        //     stringstream check1(line);	
	        //     int parent;	
	        //     check1 >> parent;	
	        //     string arrow;	
	        //     check1>>arrow;	
	        //     vector<int> child_nodes;	
	        //     int child;	
	        //     while(check1>>child)	
	        //     {	
	        //         child_nodes.push_back(child);	
		
	        //         (allnodes[child]->parent) = allnodes[parent];	
	        //         (allnodes[parent]-> node_child).push_back(allnodes[child]);	
	        //     }	
	        // }	
	        // Node* root = allnodes[0];	
	        // infile.close();	
	        // ifstream infile2; //taking input of the weight of the nodes	
	        // infile2.open("/home/ash/Downloads/trace.cost", in);	
	        // while(getline(infile2, line))	
	        // {	
	        //     stringstream check1(line);	
	        //     int n; //index of node in allnodes	
	        //     int weight; //weight of nth node in allnodes	
	        //     string arrow;	
	        //     check1>>n;	
	        //     check1>>arrow;	
	        //     check1>>weight;	
	        //     (allnodes[n]->weight) = weight;	
	        // }	
	        // //taking inputs over	
	        // //creating graph (adjacency matrix)	
	        // int graph[1000][1000];	
	        	
	        // for(int i=0; i<1000; i++)	
	        // {	
	        //     int a[1000];	
	        //     for(int j=0; j<1000; j++)	
	        //     {	
	        //         graph[i][j] = 0;	
	        //     }	
	        // }	
		
		
		
		
		
		
		
	        // for(int i=0; i<allnodes.size(); i++)	
	        // {	
	        //     for(int j=0; j<(allnodes[i]->node_child).size(); j++)	
	        //     {	
	        //         graph[(allnodes[i]->node_child)[j].initialid][i] = k;	
	        //     }	
		
	        // }		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int k=9;
        // cout<<"give k: "<<endl;
        // cin>>k;
        int n=10;
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
	        Node* eight = new Node(8, five);
	        Node* nine = new Node(9, eight);
	        five->node_child.push_back(eight);
	        eight->node_child.push_back(nine);

            	        vector <Edge*> edge_vec;
	        Edge* one_ = new Edge(1, one, root);
	        Edge* two_ = new Edge(1, two, root);
	        Edge* three_ = new Edge(1, three, root);
	        Edge* four_ = new Edge(1, four, root);
	        Edge* five_ = new Edge(1, five, root);
	        Edge* six_ = new Edge(1, six, one);
	        Edge* seven_ = new Edge(1, seven, one);
	        Edge* eight_ = new Edge(1, eight, five);
	        Edge* nine_ = new Edge(1, nine, eight);
	        
	        edge_vec.push_back(one_);
	        edge_vec.push_back(two_);
	        edge_vec.push_back(three_);
	        edge_vec.push_back(four_);
	        edge_vec.push_back(five_);
	        edge_vec.push_back(six_);
	        edge_vec.push_back(seven_);
	        edge_vec.push_back(eight_);
	        edge_vec.push_back(nine_);

        
        int graph[n][n];				//Adjaceny matrix of the tree
        
        // cin>>n;
        graph[1][0]=10;
        graph[2][0]=10;
        graph[3][0]=10;
        graph[4][0]=10;
        graph[5][0]=10;
        graph[6][1]=10;
        graph[7][1]=10;
        vector<Edge*> edges;                //VECTOR CONTAINING EDGES
        for (int i = 0; i < n; i++)
        {
            /* code */
            // vector<int> v;
            for (int i1 = 0; i1 < n; i1++)
            {
                /* code */
                // v.push_back(graph[i][i1]);
                if(graph[i][i1]!=0)
                {
                    Edge* e=new Edge(graph[i][i1], nodes[i], nodes[i1]);
                    edges.push_back(e);
                }

            }

            //  cout<<"node number: "<<obj->node_number<<endl;
            // graph1[i]=v;
        }
    /////////////////////////////////INPUT OVER//////////////////////////////////////////////

    /////////////////////////////////////L1//////////////////////////////////////////
         vector<ObjectL1*> vec;				//vector conataining nodes in post order
	        int node_number = 0;
	        // cout<<"start\n";
	        L1(root, vec, node_number);
	        int size = vec.size();
	        if(size==node_number){
	            // cout<<"hurrah!\n";
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
	            // cout<<"weight of node: "<<wt<<"\n";
	            // cout<<"weight of mv: "<<wt1<<"\n";
	            // cout<<"weight of mv_prime: "<<wt2<<"\n";
	            // cout<<"node number: "<<obj->node_number<<endl;
	            // cout<<"post_order_number: "<<(obj->node)->post_order_number<<endl<<endl;
	        }
	
	        // cout<<"size of vec is "<<vec.size()<<endl;
	        // for(int i=0;i<vec.size();i++)
	        // {
	            
	        //     cout<<"node "<<vec[i]->node->weight<<", number is "<<vec[i]->node_number;
	        //     if(vec[i]->node->parent!=nullptr)
	        //     cout<<", with its parent as "<<vec[i]->node->parent->weight;
	        //     cout<<endl;
	        // }
	
	        //check T_uv_zero
	        int apple =0;
	        // apple = T_uv_Zero(root, three, vec, edge_vec);
	        // cout<<"T_uv_zero for node four: "<<apple<<endl;
	
	        // apple = Tv1(root, vec, edge_vec);
	        // cout<<"Tv1 for root: "<<apple<<endl;
	        // apple = Ruv1(root, three, vec, edge_vec);
	        // cout<<"Ruv1 for node four: "<<apple<<endl;
	        // apple = Luv0(root, three, vec, edge_vec);
	        // cout<<"Luv0 for node four: "<<apple<<endl;
	
	        int Tv1Array[size];
	        int T_uv_0Array[size];
	        int Ruv1Array[size];
	        int Luv0Array[size];
	        //initialization
	        for(int i=0; i<size; i++){
	            Tv1Array[i] = -1;
	            T_uv_0Array[i] = -1;
	            Ruv1Array[i] = -1;
	            Luv0Array[i] = -1;
	        }

	        //array dec
	        int array[size][k];
	        
	        for (int u = 1; u <= size;u++)
	        {	
	    //////////////////////////////////////////////L2//////////////////////////
	        	
	    //////////////////////////////////////////////L3//////////////////////////
	            int mvOfU=vec[u-1]->mv->post_order_number;
	            cout<<"FOR NODE "<<u<<" WHOSE MV= "<<mvOfU<<":"<<endl;
	            // cout<<"Entering into the subtree Tu=T"<<u<<" :"<<endl;
	            for(int v=mvOfU;v<=u;v++)                 //v belongs to Tu
	            {	
	            	// cout<<"node under observation is "<<v<<endl;
	                int mvv = (vec[v-1]->mv)->post_order_number;
	                
	                int Tv11=Tv1(vec[v-1]->node, vec, edge_vec);		//take inputs the length of each edge and prepare a adjacency matrix for that
	                                                //also prepare a vector of weights of vertices
	                // cout<<"||Tv||1= "<<Tv11<<endl;
	                int valTuv0 = T_uv_Zero(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);    //value of valTuv0 is updated
	                // cout<<"||Tu,v||0= "<<valTuv0<<endl;
	                int ruv1=Ruv1(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);
	                // cout<<"||Ru,v||1= "<<ruv1<<endl;
	                int luv0=Luv0(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);
					// cout<<"||Lu,v||0= "<<luv0<<endl;
	                //storing T_uv_Zero
	                Tv1Array[u-1] = Tv11;
	                // cout<<"value of Tv1Array set to "<<Tv1Array[u-1]<<endl;
	                T_uv_0Array[u-1] = valTuv0;
	                // cout<<"value of T_uv_0Array set to "<<T_uv_0Array[u-1]<<endl;
	                Ruv1Array[u-1] = ruv1;
	                // cout<<"value of Ruv1Array set to "<<Ruv1Array[u-1]<<endl;
	                Luv0Array[u-1] = luv0;
	                // cout<<"value of Luv0Array set to "<<Luv0Array[u-1]<<endl;

	                // cout<<"v is "<<vec[v-1]->node->post_order_number<<" with mv= "<<mvv<< " ||Tv||1= "<<Tv11<<" value of ||Tu,v||0= "<<valTuv0<<" ||Ru, v||1="<<ruv1<<" ||Lu,v||0= "<<luv0<<endl;



	            }
	    ///////////////////////////////////////////////L3/////////////////////////
	    ///////////////////////////////////////////////L4///////////////////////
				cout<<"u= "<<u<<endl;
	            for(int t=2;t<=k;t++)
	            {
	                int mvv=vec[u-1]->mv->post_order_number ;
                    cout<<"t= "<<t<<endl;
	    ///////////////////////////////////L4/////////////////////////////////
	    ///////////////////////////////////////////////L5/////////////////////            
	                if(t>=u-mvv+1){
						int T_ut=0;

						cout<<"||Tu||t= "<<T_ut<<endl;
						break;
	                }
					
					else{
		                for (int v = mvv+1; v <= u-1 ; v++)
		                {
		    ///////////////////////////////////////////////L5//////////////////////////////////////////
		    ///////////////////////////////////////////////L6//////////////////////////////////////////
		                    /* code */
		                    int mv=vec[v-1]->mv->post_order_number;
		                    if(v==mv)
		                    {

		                        int luvt1=L_uvt_theo3(vec[u-1]->node, vec[v-1]->node, t-1, vec, edge_vec);
		                      	cout<<"For node v= "<<v<<" ||Luv||"<<t-1<<"= "<<luvt1<<endl;
		                    }
		                }
		    ///////////////////////////////////////////////L6///////////////////////////////////////////////
		                
		    ///////////////////////////////////////////////L7/////////////////////////////////////////////
		                int T_ut = T_u_t(t, vec[u-1]->node, vec, edge_vec);
		                array[u-1][k-1] = T_ut;

		                cout<<"For t= "<<t<<" value of T_ut= "<<T_ut<<endl;
	            	}
	    ///////////////////////////////////////////////L7///////////////////////////////
	            }
				
	    ///////////////////////////////////////////////L8//////////////////////////
	    //CHECK: how to calculate Tvt for v=[1, u] & t=[1,k]            
	            for(int j=0; j<size; j++){
	                int tv1 = Tv1(vec[j]->node, vec, edge_vec);
	                array[j][0] = tv1;
	            }
	            cout<<endl<<endl;
	    	}
	    ////////////////////////////////////////////////L8/////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            //                  PHASE 2

            // Node* ro=vec[0]->node;
            // Proxies(ro, k, vec, edge_vec);

            

	return 0;

}
