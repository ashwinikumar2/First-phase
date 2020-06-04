#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#define MAX_SIZE INT_MAX
#define ARR_SIZE 1024
using namespace std;

void INITIALIZATION(int u_num);

int Cu[ARR_SIZE], Nu[ARR_SIZE], Tut[ARR_SIZE][ARR_SIZE];
int nodes_array[ARR_SIZE] ;

int TV1[ARR_SIZE], TUV0[ARR_SIZE], RUV1[ARR_SIZE], LUV0[ARR_SIZE];
int LUVt[ARR_SIZE][ARR_SIZE];   //first is v and second is t
int XUVt[ARR_SIZE][ARR_SIZE], CUVt[ARR_SIZE][ARR_SIZE];
vector<int> proxyList;
vector<int> CuList;
vector<int> NuList;
set<int> proxyL;
void initCu_And_Nu(){

    for(int j=0; j<ARR_SIZE; j++){
        Cu[j] = 0;
        Nu[j] = 0;
            //Tut[i][j] = -1;
    }
}

void init_TUt(){
    for(int i=0; i<ARR_SIZE; i++){
        for(int j=0; j<ARR_SIZE; j++){
            Tut[i][j] = 0;
        }
    }
}

void initialize_TV1_TUV0_RUV1_LUV0(){
    for(int i=0; i<ARR_SIZE; i++){
        TV1[i] = 0;
        TUV0[i] = 0;
        RUV1[i] = 0;
        LUV0[i] = 0;
    }
}

void init_LUVt(){
    for(int i=0; i<ARR_SIZE; i++){
        for(int j=0; j<ARR_SIZE; j++){
            LUVt[i][j] = 0;
        }
    }
}

void init_XUVt_CUVt(){
    for(int i=0; i<ARR_SIZE; i++){
        for(int j=0; j<ARR_SIZE; j++){
            XUVt[i][j] = 0; CUVt[i][j] = 0;
        }
    }
}

void display(){

    // for(int i=0; i<1024; i++){
    //     if(nodes_array[i]!= -1){
    //         cout<<"nodes_array["<<nodes_array[i]<<"], ";
    //     }
    // }
    // cout<<endl;
    // for(int i=0; i<1024; i++){
    //     if(Cu[i] != -1)  cout<<"Cu["<<i<<"]: "<<Cu[i]<<endl;
    //     if(Nu[i] != -1)  cout<<"Nu["<<i<<"]: "<<Nu[i]<<endl;
    //     for(int j=0; j<1024; j++){
            
    //         if(Tut[i][j] != 0)  cout<<"Tut["<<i<<"]["<<j<<"]: "<<Tut[i][j]<<endl;
    //     }
    // }
}

class Node
{
    public:
    // int initial_id;                      //initial id given in input file
    int weight;                         //weight of the node.
    Node* parent;
    int pre_order_number;                       //parent of the node(only one parent is possible)
    int post_order_number;
    vector<Node*> node_child;           //vector to store the children of the node.
    Node(int weight, Node* parent, int pre_order_number)        //constructor
    {
        this->weight = weight;
        this->parent = parent;
        this->pre_order_number = pre_order_number;
        post_order_number=0;                                    //check when is post order no. is calculated
    }
    
    string To_string(){
        string line = "pre-order no.= : " + to_string(this->pre_order_number)+ "and post order no.= "+ to_string(this->post_order_number);
        line = line + ", weight: " + to_string(this->weight) + ")";
        return line;
    }

    string to_string1(){
        string line = "pre-order no.= " + to_string(this->pre_order_number);
        line = line + ", weight: " + to_string(this->weight) + ")";
        return line;
    }
};

class Edge
{
public:
    int length;                         //length of the edge.
    Node* firstNode;                    //first node attached to the edge.
    Node* secondNode;                   //second node attached to the edge.
    
    //constructor of the class Edge
    Edge(int length, Node* firstNode ,Node* secondNode)
    {
        this->length = length;
        this->firstNode = firstNode;
        this->secondNode = secondNode;
    }

    string To_string(){
        string line = "(First Node: " + this->firstNode->To_string() + ", Second Node: ";
        line = line + this->secondNode->To_string() + ")";
        return line;
    }
};


class ObjectL1
{
public:
    Node* node;                         //reference node. 
    int post_order_number;    
    Node* mv;                           // Node mv
    Node* mv_prime = nullptr;                     //Node mv' 
    bool isLeaf;
    ObjectL1(Node* node, Node* mv, int post_order_number, bool isLeaf)
    {
        this->node = node;
        this->mv = mv;
        this->post_order_number = post_order_number;
        node->post_order_number = post_order_number;
        this->isLeaf = isLeaf;
    }

    string To_string(){
        string line  = "Node: " + node->To_string() + "\n";
        line = line + "MV: " + mv->To_string() + "\n";
        if(mv_prime != nullptr)
        line += "MV': " + mv_prime->To_string() + "\n";
        else line += "MV': does not exist\n";
        if(isLeaf)  line += "isLeaf: true\n";
        else    line += "isLeaf: false\n";
        line += "Post order number: " + to_string(post_order_number) + "\n";
        return line;
    }

};

int Luvt(int t, Node* v, Node* u);
//global declarations starts..
vector<Edge*> edge_vec;
vector<ObjectL1*> obj_vec;      //contains nodes in POST ORDER TRAVERSAL

Node* nodes_list[ARR_SIZE];     //elements are acc to pre_order_number
int nodes_count = 0;            //keep track of the number of nodes..
int nodes_mv_list[ARR_SIZE];    //ith element is for ith pre order no. node's MV
int nodes_mv_prime_list[ARR_SIZE];//ith element is for ith pre order no. node's MV'
//global declarations ends..



// //function to display tree
// void display_tree(Node* root){
//     if(root->node_child.size() == 0){
//         string a = root->To_string();
//         cout<<a<<endl;
//         return ;
//     }
//     string a = root->To_string();
//     cout<<a<<endl;
//     int s = root->node_child.size();
//     for(int i= 0; i<s; i++){
//         display_tree(root->node_child[i]);
//     }
//     return;
// }

// void display_edges(vector<Edge*> &edge_vec){
//     int s = edge_vec.size();
//     for(int i=0; i<s; i++){
//         Edge* obj = edge_vec[i];
//         string a = obj->To_string();
//         cout<<a<<endl;
//     }
// }

int find_mv(Node* current_node)
{
    if((current_node->node_child).size() == 0){
        return current_node->pre_order_number;
    }
    
    return find_mv((current_node->node_child)[0]);
}

int find_mv_prime(Node* current_node){
    //write your code here
    int mv_pos = nodes_mv_list[current_node->pre_order_number];
    Node* mv_node = nodes_list[mv_pos];
    int post_num_mv = mv_node->post_order_number;
    if(post_num_mv > 1){
        int i = -1;
        for(i = post_num_mv - 2; i>=0; i--){
            if(obj_vec[i]->isLeaf)
            break;
        }
        int mv_prime_pos = obj_vec[i]->node->pre_order_number;
        return mv_prime_pos;
    }
    return -1;
}

void L1(Node* root, int &node_number)    //array is passed by reference.
{

    // cout<<"into the loop\n";
    // cout<<"node_number"<<node_number<<endl;

    //base case1: when the only node is root
    if((root->node_child).size() == 0 &&  (root->parent) == nullptr){
        // cout<<"only root\n";
        ObjectL1* obj ;
        if(node_number == 0)
        obj = new ObjectL1(root, nodes_list[nodes_mv_list[root->pre_order_number]], node_number+1, true);
        else
        obj = new ObjectL1(root, nodes_list[nodes_mv_list[root->pre_order_number]], node_number+1, true);

        node_number += 1;
        obj_vec.push_back(obj);
        return;
    }

    //base case2: when the node is the leaf node.
    else if((root->node_child).size() == 0){
        //cout<<"leaf node\n";
        ObjectL1* obj;

        if(node_number == 0)                    //will this case exist it indicates the leaf is the only node in tree which is covered in previous base case
        obj = new ObjectL1(root, nodes_list[nodes_mv_list[root->pre_order_number]], node_number+1, true);
        else
        obj = new ObjectL1(root, nodes_list[nodes_mv_list[root->pre_order_number]], node_number+1, true);
        
        node_number += 1;
        obj_vec.push_back(obj);
        return;
    }

    //recursive program.
    int size = (root->node_child).size();
    for(int i=0; i< size; i++){
        L1((root->node_child)[i], node_number);
    }
    ObjectL1* obj = new ObjectL1(root, nodes_list[nodes_mv_list[root->pre_order_number]], node_number+1, false);
    node_number += 1;
    obj_vec.push_back(obj);
    return;
}

int search_edge(Node* x, Node* u){//search whether an edge is present or not.

    int size = edge_vec.size();
    Edge* obj;
    if(size ==0)
    return -1;
    for(int i=0; i<size; i++){
        obj = edge_vec[i];
        Node* a = obj->firstNode;
        Node* b = obj->secondNode;
        if(a==x && b==u)
        return obj->length;
    }
    return -1;
}

int distance(Node* x, Node* u){

    Node* child = x;
    Node* parent = child->parent;
    int dist = 0;
    int  y=0;
    if(x==u){
        return 0;
    }
    while(parent!=u ){
        y = search_edge(child, parent);
        dist += y;
        child = parent;
        parent = child->parent;
    }

    y = search_edge(child, parent);
    dist += y;
    return dist;
}

int T_uv_Zero(Node* u, Node* v)
{
    Node* Mv = nodes_list[nodes_mv_list[v->pre_order_number]];
    int i = Mv->post_order_number;
    int j = v->post_order_number;
    int ans = 0;

    for(int k=i; k<=j; k++){
        int wt = obj_vec[k-1]->node->weight;
        ans += wt * distance(obj_vec[k-1]->node, u);
    }
    return ans;

}

int Tv1(Node* v) 
{
    Node* Mv = nodes_list[nodes_mv_list[v->pre_order_number]];
    int mv_num = Mv->post_order_number;
    int v_num = v->post_order_number;
    int d = 0;
    for(int i = mv_num; i <= v_num; i++)
    {
        d += distance(obj_vec[i-1]->node, v) * obj_vec[i-1]->node->weight;      //add distance of child to parent
    }

    return d;
}

int Ruv1(Node* u, Node* v)   //u: parent node;, v: child node
{
    int ans=0;
    int u_post_num = u->post_order_number;
    int v_post_num = v->post_order_number;

    for(int k = v_post_num + 1; k < u_post_num; k++)
    {
        int w = obj_vec[k-1]->node->weight;
        ans += w * distance(obj_vec[k-1]->node, u);
    }
    return ans;
}

int Luv0(Node* u, Node* v)
{
    int ans=0;
    int v_post_num = v->post_order_number;
    int u_post_num = u->post_order_number;
    int mv_num = ((obj_vec[v_post_num-1])->mv)->post_order_number;
    int mu_num = ((obj_vec[u_post_num-1])->mv)->post_order_number;
    for(int k = mu_num; k < mv_num; k++)
    {
        int w = obj_vec[k-1]->node->weight;
        ans += w * distance(obj_vec[k-1]->node, obj_vec[u_post_num-1]->node);
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

int tree_size(int u)
{
    
    int mu = (obj_vec[u-1])->mv->post_order_number;
    return u-mu+1;
}
// void L4ForPhaseOne(int u_post_order_num, int k){
//     int mu_num = obj_vec[u_post_order_num -1]->mv->post_order_number;
//     for(int t=2; t<=k; t++){
//         for(int v_num = mu_num + 1; v_num < u_post_order_num; v_num++){
//             if(v_num == obj_vec[v_num-1]->mv->post_order_number){
//                 LUVt[v_num][t-1] = Luvt(t-1, obj_vec[v_num-1]->node, obj_vec[u_post_order_num -1]->node);
//             }
//         }
//         //L7..
//         Tut[u_post_order_num][t] = T_u_t(t, obj_vec[u_post_order_num-1]->node);
//     }
// }
int LuvSize(int u, int v){
    int mv = obj_vec[v-1]->mv->post_order_number;
    int mu = obj_vec[u-1]->mv->post_order_number;
    return mv-mu;
}

int T_u_t(int t, Node* u)
{   
// cout<<"t: "<<t<<endl;
    // cout<<"FINDING Tut FOR NODE= "<<u->post_order_number<<" WITH t= "<<t<<endl;
    if(t >= (u->post_order_number - nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number + 1)){
        Nu[u->post_order_number]=u->post_order_number-1;
        Cu[u->post_order_number]=tree_size(u->post_order_number)-1;
    return 0;
    }
    //base case.
    if(t == 1){
        int x = Tv1(u);
        Tut[u->post_order_number][t] = x;
        // cout<<"root is the only proxy in tree."<<endl;
        return x;
    }

    //recursive
    int mu_num = nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number ;
    int u_num = u->post_order_number;
    int y=MAX_SIZE;
    for(int i = mu_num; i < u_num; i++)
    {   
        // cout<<"node: "<<i<<"checked "<<endl;

        int x=MAX_SIZE;
        // cout<<"maximum(1, t-1-LuvSize(u_num, i)) = "<<maximum(1, t-1-LuvSize(u_num, i))<<endl;
        // cout<<"maximum(1, t-1-LuvSize(u_num, i))= "<<maximum(1, t-1-LuvSize(u_num, i))<<" minimum(t, tree_size(i))= "<<min(t, tree_size(i))<<endl;
        int tDash=1; 
        for(int l = maximum(1, t-1-LuvSize(u_num, i)); l<min(t, tree_size(i)+1); l++){  //try min instead of minimum
            // cout<<"l: "<<l<<endl;
            int a = 0;
            // cout<<"Tut["<<i<<"]["<<l<<"]= "<<Tut[i][l]<<endl;
            if(Tut[i][l] == 0)
            a = T_u_t(l, (obj_vec[i-1])->node);
            else a = Tut[i][l];

            // cout<<"a: "<<a<<"  "<<" t-l-1: "<<t-l-1<<endl;
            if(LUVt[i][t-l-1] == 0)
            a = a + Luvt(t-l-1, (obj_vec[i-1])->node, u);
            else a = a + LUVt[i][t-l-1];
            // cout<<"a after Luvt: "<<a<<endl;

            if(RUV1[i] == 0)
            a = a + Ruv1(u, (obj_vec[i-1])->node);
            else a += RUV1[i];

            // cout<<"a after Ruv1: "<<a<<endl;
            if(a<x) 
            {
                x=a; 
                tDash=l;
                // Cu[1] = l;
                // cout<<"node= "<<(obj_vec[i-1])->node->post_order_number<<" is a proxy with its Tut= "<<a<<endl;
            }

        }
        if(x<y) 
        {
            // cout<<"x= "<<x<<" y= "<<y<<endl;
            // cout<<"Tut of "<<i<<" subtree is included in Tut of "<<u->post_order_number<<endl;
            // cout<<"x= "<<x<<" y= "<<y<<endl;
            y=x; 
            Nu[u->post_order_number] = i;               //i is Nu,1 for u
            Cu[u->post_order_number]=tDash;             //tDash is the number of proxies in Ti 
            // cout<<"value of Nu["<<u->post_order_number<<"]= "<<Nu[u->post_order_number]<<" and tDash= "<<tDash<<endl;
        }

    }

    return y;
}

// void display_Cu(){
//     for(int j=0; j<1024; j++){
//         if(Cu[j]!= 0) cout<<"Cu["<<j<<"]: "<<Cu[j]<<endl;
//     }
    
// }

// void display_Nu(){
//     for(int i=0; i<1024; i++){
//         if(Nu[i]!= 0) cout<<"Nu["<<i<<"]: "<<Nu[i]<<endl;
//     }{

// }

int Luvt_2(int t, Node* v, Node* u)
{
    // cout<<"value of mu-u = "<<nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number - nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number<<endl;
    if(t<0)
    return 0;

    if(t>(nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number - nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number))
        return 0;

    //base case
    if(t==0){
        // cout<<"returned Luv0"<<endl;
        return Luv0(u, v);
    }
    int mu = nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number;
    int mv = nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number;
    int mvprime=obj_vec[v->post_order_number-1]->mv_prime->post_order_number;
    int net_min =MAX_SIZE;
    int x1=v->post_order_number;
    int t2=t-1;
    for(int x = mu; x < mv; x++){
        int min = MAX_SIZE;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x)); i<=minimum(t, tree_size(x)); i++){
            Node* ex = obj_vec[x-1]->node;
            int a = 0;

            //if(TUt[x][i] == -1)
            a = T_u_t(i, ex);
            //else a = TUt[x][i];

            if(LUVt[x][t-i] == 0)
            a = a + Luvt(t-i, ex, u);
            else a = a + (LUVt[x][t-i]);
            
            if(RUV1[x]== 0)
            a = a + Ruv1(u, ex);
            else a = a + RUV1[x];

            if(RUV1[v->post_order_number] == 0)
            a = a - Ruv1(u, v);
            else a = a - RUV1[v->post_order_number];

            if(TUV0[v->post_order_number] == 0)
            a = a - T_uv_Zero(u, v);
            else a = a - TUV0[v->post_order_number];

            if(a<min)  
            { 
                t2=i;
                min= a;
            }
        }
        if(min<net_min) 
            {
                x1=x;
                XUVt[v->post_order_number][t]=x;
                // cout<<"   IN LUVT_2  SET XUVt["<<v->post_order_number<<"]["<<t<<"]= "<<XUVt[v->post_order_number][t]<<endl;
                // cout<<"          XUVt["<<v->post_order_number<<"]["<<t<<"]= "<<XUVt[v->post_order_number][t]<<endl;
                CUVt[v->post_order_number][t]=t2;
                net_min = min;
            }
    }
     // cout<<"AUVT= "<<A_uvt(u,v,t)<<endl;
    // cout<<"happy"<<endl;
    if(net_min != MAX_SIZE)
    return net_min;
    // cout<<"see"<<endl;
    return 0;
}


int A_uvt(Node* u, Node* v, int t){


    if(t<0)
    return 0;

    if(t>(nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number - nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number))
        return 0;

    //base case
    if(t==0){
        // cout<<"returned Luv0"<<endl;
        return Luv0(u, v);
    }
    int post_v = v->post_order_number;
    int MvPrimeOfvNum = obj_vec[post_v -1]->mv_prime->post_order_number;
    int a = Luvt_2(t, obj_vec[post_v -1]->mv_prime, u);

    if(RUV1[MvPrimeOfvNum] == 0)
    a = a + Ruv1(u, obj_vec[post_v -1]->mv_prime);
    else a = a + RUV1[MvPrimeOfvNum];

    if(TUV0[MvPrimeOfvNum] == 0)
    a = a + T_uv_Zero(u, obj_vec[post_v -1]->mv_prime);
    else a = a + TUV0[MvPrimeOfvNum];

    if(RUV1[v->post_order_number] == 0)
    a = a - Ruv1(u, v);
    else a = a - RUV1[v->post_order_number];

    if(TUV0[v->post_order_number] == 0)
    a = a - T_uv_Zero(u, v);
    else a = a - TUV0[v->post_order_number];

    XUVt[v->post_order_number][t]=XUVt[post_v-1][t];
    // // cout<<"           XUVt["<<v->post_order_number<<"]["<<t<<"]= "<<XUVt[v->post_order_number][t]<<endl;
    CUVt[v->post_order_number][t]=CUVt[post_v-1][t];
    return a;

}

int Buvt(int t, Node* v, Node* u){
    //negative case
    // cout<<"t recieved for Luvt = "<<t<<endl;
    // cout<<"value of mu-u = "<<nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number - nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number<<endl;
    if(t<0)
    return 0;

    if(t>(nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number - nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number))
        return 0;

    //base case
    if(t==0){
        // cout<<"returned Luv0"<<endl;
        return Luv0(u, v);
    }
    int mu = nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number;
    int mv = nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number;
    int mvprime=obj_vec[v->post_order_number-1]->mv_prime->post_order_number;
    int net_min =MAX_SIZE;
    int x1=v->post_order_number;
    int t2=t-1;
    // cout<<"for v="<<v->post_order_number<<" mvprime= "<<mvprime<<endl;
    for(int x = mvprime; x < mv; x++){
        int min = MAX_SIZE;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x)); i<=minimum(t, tree_size(x)); i++){
            Node* ex = obj_vec[x-1]->node;
            int a = 0;

            //if(TUt[x][i] == -1)
            a = T_u_t(i, ex);
            //else a = TUt[x][i];

            if(LUVt[x][t-i] == 0)
            a = a + Luvt_2(t-i, ex, u);
            else a = a + (LUVt[x][t-i]);
            
            if(RUV1[x]== 0)
            a = a + Ruv1(u, ex);
            else a = a + RUV1[x];

            if(RUV1[v->post_order_number] == 0)
            a = a - Ruv1(u, v);
            else a = a - RUV1[v->post_order_number];

            if(TUV0[v->post_order_number] == 0)
            a = a - T_uv_Zero(u, v);
            else a = a - TUV0[v->post_order_number];

            if(a<min)  
            { 
                t2=i;
                min= a;
            }
        }
        if(min<net_min) 
            {
                x1=x;
                XUVt[v->post_order_number][t]=x;
                // cout<<"      SET XUVt["<<v->post_order_number<<"]["<<t<<"]= "<<XUVt[v->post_order_number][t]<<endl;
                CUVt[v->post_order_number][t]=t2;
                net_min = min;
            }
    }
     // cout<<"AUVT= "<<A_uvt(u,v,t)<<endl;
    // cout<<"happy"<<endl;
    if(net_min != MAX_SIZE)
    return net_min;
    // cout<<"see"<<endl;
    return 0;
}


int Luvt(int t, Node* v, Node* u)
{
    int mu=obj_vec[u->post_order_number-1]->mv->post_order_number;
    int mv=obj_vec[v->post_order_number-1]->mv->post_order_number;
    // cout<<"for u="<<u->post_order_number<<" and v= "<<v->post_order_number<<" A_uvt= "<<A_uvt(u,v,t)<<" Buvt= "<<Buvt(t,v,u)<<" Luvt2= "<<Luvt_2(t,v,u)<<endl;
        // cout<<"for u="<<u->post_order_number<<" and v= "<<v->post_order_number<<" A_uvt= "<<A_uvt(u,v,t)<<" Buvt= "<<Buvt(t,v,u)<<endl;

    if(mv== mu){
         // cout<<"For u="<<u->post_order_number<<" and v= "<<v->post_order_number<<" Buvt selected"<<endl;
        return 0;
       
    }
    else{
        // if(min(A_uvt(u,v,t), Buvt(t,v,u)) == A_uvt(u,v,t))
            // cout<<"For u="<<u->post_order_number<<" and v= "<<v->post_order_number<<" Auvt selected"<<endl;
        // else
            // cout<<"For u="<<u->post_order_number<<" and v= "<<v->post_order_number<<" Buvt selected"<<endl;
        int a=A_uvt(u,v,t);
        int b=Buvt(t,v,u);
        int x=min(a,b);
        // cout<<"x= "<<x<<" a= "<<a<<" b= "<<b<<endl;
        if(x==a )
            A_uvt(u,v,t);
        else 
            Buvt(t,v,u);
        return min(A_uvt(u,v,t), Buvt(t,v,u));
    }
}
// int B_uvt(Node* u, Node* v, int t){
//     cout<<"BUVT called"<<endl;
//     cout<<"mv num: "<<nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number<<endl;
//     cout<<"mu num: "<<nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number<<endl;
//     // if(t>= (nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number - nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number))
//     //     return 0;

//     //base case
//     if(t==0){
//         return Luv0(u, v);
//     }
//     int mu = nodes_list[nodes_mv_list[u->pre_order_number]]->post_order_number;
//     int mv = nodes_list[nodes_mv_list[v->pre_order_number]]->post_order_number;
//     //if(mu== obj_vec[u->post_order_number-1]->mv->post_order_number)cout<<"hurrah!"<<endl;
//     int net_min =MAX_SIZE;
//     int xuvt = 0; int cuvt = 0;
//     int mv_prime = nodes_list[nodes_mv_prime_list[v->pre_order_number]]->post_order_number;
//     cout<<"mv_prime"<<mv_prime<<endl;
//     for(int x = mv_prime; x < mv; x++){
//         int min = MAX_SIZE;
//         for(int i = maximum(1, t-LuvSize(u->post_order_number, x)); i < minimum(t, tree_size(x)); i++){
//             cout<<"second loop enters\n";
//             Node* ex = obj_vec[x-1]->node;
//             int a = 0;

//             if(Tut[x][i] == 0)
//             a = T_u_t(i, ex);
//             else a = Tut[x][i];
            
//             if(LUVt[x][t-i] == 0)
//             a = a + Luvt(t-i, ex, u);
//             else a = a + LUVt[x][t-i];

//             if(RUV1[x] == 0)
//             a = a + Ruv1(u, ex);
//             else a = a + RUV1[x];

//             if(RUV1[v->post_order_number] == 0)
//             a = a - Ruv1(u, v);
//             else a = a - RUV1[v->post_order_number];

//             if(TUV0[v->post_order_number] == 0)
//             a = a - T_uv_Zero(u, v);
//             else a = a - TUV0[v->post_order_number];

//             if(a<min)   {min= a; cuvt = i;}
//         }
//         if(min<net_min) {net_min = min; xuvt = x; cout<<"\nx: "<<x<<endl;}
//     }
//     XUVt[v->post_order_number][t] = xuvt;
//     CUVt[v->post_order_number][t] = cuvt;
//     cout<<"XUVt["<<v->post_order_number<<"]["<<t<<"]: "<<xuvt<<endl;
//     cout<<"CUVt["<<v->post_order_number<<"]["<<t<<"]: "<<cuvt<<endl;
//     return net_min;

// }

// int L_uvt_theo3(Node* u, Node* v, int t){
//     int a = A_uvt(u, v, t);
//     int b = B_uvt(u, v, t);
//     return minimum(a, b);
// }


void Proxies(Node* u, int t)
{
    //L1: If t = 1 then return {u};
    //here u is a node.
    // if(u->post_order_number==obj_vec.size() && t<1)
    // {
    //  return;
    // }
    if(t==1)
    {
        // cout<<"here u is: "<<u->post_order_number<<endl;
        //nodes_array[u->post_order_number] = u->post_order_number;
        // proxyList.push_back(u->post_order_number);
        // NuList.push_back(u->post_order_number);
        // NuList.push(u->post_order_number);
        // CuList.push_back(t);
        proxyList.push_back(u->post_order_number);
        // // proxyL.push_back(u->post_order_number);
        proxyL.insert(u->post_order_number);
        cout<<"u becomes proxy"<<endl;
        // if(u->post_order_number!=obj_vec.size())
        // NuList.push_back(u->post_order_number);
        return;
    }
    // proxyList.push_back(u->post_order_number);
    //L2: Initialization: For each v belongs to Tu, 
    //compute ||Tv1||, ||Tuv0||, ||Ruv1|| and ||Luv0||.
    // if(t>=tree_size(u))
    // {
    //  int j=tree_size(u)-1;
    //  for(int i=(u->mv)->post_order_number;i<u;i++)
    //  {
            
    //      proxyList.push_back(i);
    //      NuList.push_back(i);
    //      CuList.push_back(j);

    //      j--;
    //  }
    // }
    
    int mu_num = obj_vec[u->post_order_number-1]->mv->post_order_number;      //mv = post order no of Mv of u
    
    INITIALIZATION(u->post_order_number);
    /*
    int sizeOfTreeU = u->post_order_number - mu_num + 1;
    int tv1[sizeOfTreeU], tuv0[sizeOfTreeU], ruv1[sizeOfTreeU];
    int luv0[sizeOfTreeU];
    

    for(int v_num = mu_num; v_num <= u->post_order_number; v_num++)
    {   
        cout<<"number: "<<v_num<<endl;
        tv1[v_num]  = Tv1(obj_vec[u->post_order_number-1]->node);
        tuv0[v_num] = T_uv_Zero(u, obj_vec[v_num-1]->node);
        ruv1[v_num] = Ruv1(u, obj_vec[v_num-1]->node);
        luv0[v_num] = Luv0(u, obj_vec[v_num-1]->node);
        cout<<"tv1: "<<tv1[v_num]<<" tuv0: "<<tuv0[v_num]<<" ruv1: "<<ruv1[v_num]<<" luv0: "<<luv0[v_num]<<endl<<endl;
    }
    */
    //int xuv_t[ARR_SIZE], cuv_t[ARR_SIZE];   //cuv_t_minus_one is the number of proxies in the tree rotted at
    //int luv_t_minus_one[ARR_SIZE];
    // cout<<"A"<<endl;
    // for(int i=1;i<=tree_size(u->post_order_number)-1;i++)
    // {
    //  for(int j=1;j<t;j++)
    //  {
    //      cout<<"XUVt["<<i<<"]["<<j<<"]= "<<XUVt[i][j]<<"  CUVt["<<i<<"]["<<j<<"]= "<<CUVt[i][j]<<endl;
    //  }
    // }
    // cout<<"v_num = "<<mu_num + 1<<" to "<<u->post_order_number-1<<endl;
    // L4ForPhaseOne(u->post_order_number, t);

    for(int t1=2;t1<=t;t1++)            //FIXME check when t<tree_size(x) or mu<=mv
    {
        for(int v_num = mu_num + 1; v_num < u->post_order_number; v_num++)
        {   

            if(v_num == obj_vec[v_num-1]->mv->post_order_number)
            {
                
                LUVt[v_num][t1-1] = Luvt(t1-1, obj_vec[v_num-1]->node, obj_vec[u->post_order_number -1]->node);
                // cout<<"v_num = "<<v_num<<" mv= "<<obj_vec[v_num-1]->mv->post_order_number<<" LuvT= "<<LUVt[v_num][t1-1]<<endl;
                // cout<<"Luv called for u= "<<u->post_order_number<<" v= "<<v_num<<" t= "<<t1-1<<" with Luvt= "<<LUVt[v_num][t1-1]<<endl;
            }
        }
    }

    for(int i=1;i<=tree_size(u->post_order_number)-1;i++)
    {
        for(int j=1;j<t;j++)
        {
            cout<<"XUVt["<<i<<"]["<<j<<"]= "<<XUVt[i][j]<<"  CUVt["<<i<<"]["<<j<<"]= "<<CUVt[i][j]<<endl;
        }
    }

    int nu1=Nu[u->post_order_number];
    int cu1=Cu[u->post_order_number];
    // cout<<"Nu= "<<nu1<<" Cu= "<<cu1<<" t= "<<t<<endl;
    cout<<nu1<<" pushed into NuList and proxyList"<<endl;
    NuList.push_back(nu1);
    CuList.push_back(cu1);
    proxyList.push_back(nu1);
    proxyL.insert(nu1);
    int iTemp=2;
    

    // proxyList.push_back(nu1);
    // int count=0;
    int nuBefore=nu1;
    int tTemp=t-cu1-1;

    // cout<<"tTemp= "<<tTemp<<" nuBefore= "<<nuBefore<<endl;
    // cout<<"XUVt[nuBefore][tTemp];= "<<XUVt[nuBefore][tTemp]<<endl;
    // cout<<"CUVt[nuBefore][tTemp];= "<<CUVt[nuBefore][tTemp]<<endl;
    while(tTemp>0)
    {
        int nui=XUVt[nuBefore][tTemp];
        int cui=CUVt[nuBefore][tTemp];
                // cout<<"cui= "<<cui<<" nui= "<<nui<<endl;
        if(cui!=0 && nui!=0)            //i.e. we are at the leftmost node for proxies
        {
            
            cout<<nui<<" pushed into NuList and proxyList"<<endl;
            NuList.push_back(nui);
            CuList.push_back(cui);
            proxyList.push_back(nui);
            proxyL.insert(nui);
            nuBefore=nui;
            tTemp=tTemp-cui;
        iTemp++;

            // cout<<"          last element added to NuList is "<<nui<<endl;
            // cout<<"          last element added to CuList is "<<CuList[CuList.size()-1]<<endl;
            // cout<<"After while loop tTemp= "<<tTemp<<" iTemp= "<<iTemp<<endl;
        }
        else
        break; 
    }

    // cout<<"tTemp= "<<tTemp<<" iTemp= "<<iTemp<<endl;
    // int iTemp2=0;
// 
    // cout<<"After while loop NuList becomes: "<<endl;
    
// Proxies(obj_vec[NuList[0]]->node, CuList[0]);
    // int initSizeOfNuList=NuList.size();
    // if(iTemp<=2)                         //i.e. no element is added in nulist
        // initSizeOfNuList=initSizeOfNuList-1;
    
//     for(int i=initSizeOfNuList-1;i<iTemp-1;i++)
//     {
//      cout<<"i= "<<i<<endl;
//      cout<<"going to call proxies for node : "<<NuList[i]<<" with Cu= "<<CuList[i]<<endl;
//      Proxies(obj_vec[NuList[i]-1]->node, CuList[i]);
//      cout<<"NuList size = "<<NuList.size()<<" NuList[0]= "<<NuList[0]<<endl;
//         // cout<<"proxyList size= "<<proxyList.size()<<" proxyList[0]= "<<proxyList[0]<<endl;

//         for(int j=0;j<NuList.size();j++)
//         {
//          cout<<"             NuList["<<j<<"]= "<<NuList[j]<<endl;
//         }
//     }
//     cout<<"AFTER CALLING PROXIES FOR EVERY NODES OF NuList WE HAVE: "<<endl;
    
// cout<<"vfsklnkldg"<<endl;
    // for(int i1=0;i1<proxyList.size();i1++)
    // {
    //  cout<<"proxyList["<<i1<<"]= "<<proxyList[i1]<<endl;
    // }
    // for(int v_num = mu_num + 1; v_num < u->post_order_number; v_num++)
    // {   cout<<"C"<<endl;
    //     if(v_num == obj_vec[v_num-1]->mv->post_order_number)
    //     {   cout<<"u has post num: "<<u->post_order_number<<endl;
    //         cout<<"mv==v for post number: "<<v_num<<" and pre number: "<<obj_vec[v_num-1]->mv->pre_order_number<<endl;
    //         cout<<"t-1 here: "<<t-1<<endl;
    //         LUVt[v_num][t-1] = Luvt(u,  obj_vec[v_num-1]->node, t-1);
    //         cout<<"luv_t_minus_one: "<<LUVt[v_num][t-1]<<endl;
    //     }
    //     // else{
    //     //     LUVt[v_num][t-1] = L_uvt_theo3(u,  obj_vec[v_num-1]->node, t-1);
    //     // }
    // }
    

    // if(Tut[u->post_order_number][t] == -1)
    // Tut[u->post_order_number][t] = T_u_t(t, u);
    
    //     int i=2; 
    //     cout<<"CU[1]: "<<Cu[1]<<" and intial t: "<<t<<endl;
    //     t = t - Cu[1] - 1;
    //     cout<<"t: "<<t<<endl;
    //     while(t != 0){
    //         sleep(1);
    //         cout<<"loop of t: "<<t<<endl;
    //         int beta = Nu[i-1];
    //         Cu[i] = XUVt[beta][t];
    //         Nu[i] = CUVt[beta][t];
    //         t = t - Cu[i];
    //         if(Nu[i] == 0)  break;
    //         cout<<"Cu["<<i<<"]: "<<Cu[i]<<endl;
    //         i++;
    //     }
    
    //     initialize_TV1_TUV0_RUV1_LUV0();
    //     init_XUVt_CUVt();
    //     init_LUVt();
        
    //     cout<<"i: "<<i<<endl;
    //     proxies.push_back(u->pre_order_number);
    //     for(int j= 1; j< i; j++){
    //         cout<<"Nu["<<j<<"]: "<<Nu[j]<<endl;
    //         cout<<"Cu["<<j<<"]: "<<Cu[j]<<endl;
    //         cout<<"B"<<endl;
    //         Proxies(obj_vec[(Nu[j])-1]->node, Cu[j]);
    //     }
        return;

}



void init_mv_list(){
    for(int i=0; i<ARR_SIZE; i++){
        if(nodes_list[i]!=nullptr){                             //assuming all elements of the arrau are nullptr
            int x = find_mv(nodes_list[i]);
            nodes_mv_list[nodes_list[i]->pre_order_number] = x;
        }
    }
}

void init_mv_prime_list(){
    for(int i=0; i<ARR_SIZE; i++){
        if(nodes_list[i]!=nullptr){
            int x = find_mv_prime(nodes_list[i]);
            nodes_mv_prime_list[nodes_list[i]->pre_order_number] = x;
        }
    }
}

void display_MV_and_MV_prime(){
    for(int i=0; i<ARR_SIZE; i++){
        if(nodes_list[i] != nullptr){
            string line1 = nodes_list[nodes_mv_list[i]]->To_string();
            string line = nodes_list[i]->To_string();
            string line2;
            if(nodes_mv_prime_list[i] != -1)
            line2 = nodes_list[nodes_mv_prime_list[i]]->To_string();
            else line2 = "Does not exist";
            cout<<"Node: "<<line<<", MV: "<<line1<<", MV': "<<line2<<endl;
        }
        // else 
            // break;
    }

    // cout<<endl;

}

void store_mv_prime_in_Object(){
    int size = obj_vec.size();
    for(int i=0; i<size; i++){
        ObjectL1* obj = obj_vec[i];
        Node* mv_prime;
        int a = nodes_mv_prime_list[(obj->node)->pre_order_number];
        // cout<<"a: "<<a<<endl;
        if(a==-1)   mv_prime = nullptr;
        else    mv_prime = nodes_list[a];
        obj->mv_prime = mv_prime;
    }
}

void display_obj_list(){
    int s = obj_vec.size();
    string line;
    for(int i=0; i<s; i++){
        line = obj_vec[i]->To_string();
        cout<<"for i= "<<i<<" "<<line<<endl;
    }
}

void INITIALIZATION(int u_post_order_num){
    int mu_num = obj_vec[u_post_order_num - 1]->mv->post_order_number;
    for(int i = mu_num; i <= u_post_order_num; i++){
        TV1[i] = Tv1(obj_vec[i-1]->node);
        TUV0[i] = T_uv_Zero(obj_vec[u_post_order_num - 1]->node, obj_vec[i - 1]->node);
        RUV1[i] = Ruv1(obj_vec[u_post_order_num - 1]->node, obj_vec[i - 1]->node);
        LUV0[i] = Luv0(obj_vec[u_post_order_num - 1]->node, obj_vec[i - 1]->node);
    }
    for(int i = mu_num; i <= u_post_order_num; i++)
    {
        // cout<<"T"<<i<<"1= "<<TV1[i]<<endl; 
        Tut[i][1]=TV1[i];
    }
}

void L4ForPhaseOne(int u_post_order_num, int k){
    int mu_num = obj_vec[u_post_order_num -1]->mv->post_order_number;
    for(int t=2; t<=k; t++){
        for(int v_num = mu_num + 1; v_num < u_post_order_num; v_num++){
            if(v_num == obj_vec[v_num-1]->mv->post_order_number){
                
                LUVt[v_num][t-1] = Luvt(t-1, obj_vec[v_num-1]->node, obj_vec[u_post_order_num -1]->node);
                // cout<<"Luv called for u= "<<u_post_order_num<<" v= "<<v_num<<" t= "<<t-1<<" with Luvt= "<<LUVt[v_num][t-1]<<endl;
            }
        }

        //L7..
        // if(u_post_order_num==10)
        // cout<<"finding Tut for node_post_order number= "<<u_post_order_num<<" and t= "<<t<<endl;
        Tut[u_post_order_num][t] = T_u_t(t, obj_vec[u_post_order_num-1]->node);
        // cout<<"for node u= "<<u_post_order_num<<" and t="<<t<<": Tut= "<<Tut[u_post_order_num][t]<<" Nu= "<<Nu[u_post_order_num]<<" Cu= "<<Cu[u_post_order_num]<<endl;
        // cout<<endl;
    }
    // cout<<"L4 ends"<<endl;
    // cout<<endl<<endl;
}

void check_tree()
{
    cout<<"Root of tree is "<<nodes_list[0]->to_string1()<<endl;
    cout<<"1st child is "<<nodes_list[0]->node_child[0]->to_string1()<<endl;
    cout<<"2nd child is "<<nodes_list[0]->node_child[1]->to_string1()<<endl;
    cout<<"3rd child is "<<nodes_list[0]->node_child[2]->to_string1()<<endl;
    cout<<"4th child is "<<nodes_list[0]->node_child[3]->to_string1()<<endl;
    cout<<"5th child is "<<nodes_list[0]->node_child[4]->to_string1()<<endl<<endl;
    cout<<"1st child of 1 is "<<nodes_list[0]->node_child[0]->node_child[0]->to_string1()<<endl;
    cout<<"2nd child of 1 is "<<nodes_list[0]->node_child[0]->node_child[1]->to_string1()<<endl<<endl;
    cout<<"child of 5 is "<<nodes_list[0]->node_child[4]->node_child[0]->to_string1()<<endl<<endl;
    cout<<"child of 8 is "<<nodes_list[0]->node_child[4]->node_child[0]->node_child[0]->to_string1()<<endl<<endl;
}

void check_mv()
{
    for(int i=0;i<ARR_SIZE;i++)
    {
        if(nodes_list[i]!=nullptr)                      //assuming all elements of the array are intially null     
                

        {
            cout<<"For "<<i<<"th pre order no. , MV= "<<nodes_mv_list[i]<<endl;

        }
        else
            break;
    }
}

void check_Tv1()
{

    int size=obj_vec.size();
    int tv11[size];
    for(int i=0;i<size;i++)
    {
        Node* n=nodes_list[i];
        int x= Tv1(n);
        tv11[i]=x;
    }
    for(int i=0;i<size;i++)
    {
            cout<<"for node i= "<<i<<" ,TV1= "<<tv11[i]<<endl;
        
    }
    // cout<<endl;
}

void check_Luvv0()
{
    int size=obj_vec.size();
    int luv0[size];
    for(int u_post=0;u_post<size;u_post++)
    {
        vector<int> v3;
        Node* u=obj_vec[u_post]->node;
        int mu1=obj_vec[u_post]->mv->post_order_number;
        for(int j=mu1;j<=u_post;j++)
        {
            // int mv1=(obj_vec[j-1]->mv)->post_order_number;
            
                Node* v=obj_vec[j-1]->node;
        
                int l=Luv0(u,v);
                v3.push_back(l);
        }
        cout<<"For node "<<u->To_string()<<endl;
        for(int k=0;k<v3.size();k++)
        {
            cout<<"L"<<(u_post+1)<<k+1<<" = "<<v3[k]<<endl;
        }
    }
}
void check_Tuvv0()
{
    int size=obj_vec.size();
    int tuv0[size];
    for(int u_post=0;u_post<size;u_post++)
    {
        vector<int> v3;
        Node* u=obj_vec[u_post]->node;
        int mu1=obj_vec[u_post]->mv->post_order_number;
        for(int j=mu1;j<=u_post;j++)
        {
            // int mv1=(obj_vec[j-1]->mv)->post_order_number;
            
                Node* v=obj_vec[j-1]->node;
        
                int l=T_uv_Zero(u,v);
                v3.push_back(l);
        }
        cout<<"For node "<<u->To_string()<<endl;
        for(int k=0;k<v3.size();k++)
        {
            cout<<"T"<<(u_post+1)<<k+1<<" = "<<v3[k]<<endl;
        }
    }
}

int main(int argc, char* argv[])                                // argc???????????????????????????????????

{
    initCu_And_Nu();                                            //what is this for?????????????????????
    init_TUt();                                                 //what is this for?????????????????????
    init_XUVt_CUVt();                                           //what is this for?????????????????????
    initialize_TV1_TUV0_RUV1_LUV0();                            //what is this for?????????????????????
    init_LUVt();                                                //what is this for?????????????????????

        int k =0;
        cout<<"Enter k: "<<endl;
        cin>>k;
        ifstream infile;        //taking input of all parent-child nodes    
        string filename = argv[1];                               //where is this argv[] coming from????????????????
        infile.open(filename.c_str());                          //use of .c_str()???????????????????????????
        string line;
            
        //for first line..
        getline(infile, line);
        istringstream check(line);  
        int parent;
        check >> parent;
        Node* parent_node = new Node(0, nullptr, parent);           //Root of the biggest tree created with pre order no.=0
        nodes_list[parent] = parent_node;
        nodes_count++;
        string arrow;
        check >> arrow;

        int child;
        while(check >> child){
            Node* child_node = new Node(0, parent_node, child);
            Edge* edge_obj = new Edge(1, child_node, parent_node);
            edge_vec.push_back(edge_obj);
            nodes_list[child] = child_node;
            nodes_count++;
            parent_node->node_child.push_back(child_node);
        }

        //second line onwards
        while(getline(infile, line))    
        {   
            istringstream check1(line); 
            check1 >> parent;   
            check1>>arrow;
            Node* par_node = nodes_list[parent];     //assuming node is already present in the tree           
            while(check1>>child)    
            {   
                Node* child_node = new Node(0, par_node, child);
                par_node->node_child.push_back(child_node);
                Edge* edge_obj = new Edge(1, child_node, par_node);
                edge_vec.push_back(edge_obj);
                nodes_list[child] = child_node;
            }   
        }   
                
        infile.close();

        ifstream infile2;       //taking input of the weight of the nodes   
        filename = argv[2];
        infile2.open(filename.c_str()); 
        while(getline(infile2, line))   
        {   
            istringstream check1(line); 
            int n;              //index of node in allnodes 
            int weight;         //weight of nth node in allnodes    
            string arrow;   
            check1>>n;  
            check1>>arrow;  
            check1>>weight; 
            (nodes_list[n]->weight) = weight;   
        }   
        infile2.close();
        // check_tree();

        /*_____________________________PHASE 1________________________________*/
        // display_tree(nodes_list[0]);
        // display_edges(edge_vec);
        init_mv_list();

        // check_mv();

// cout<<"asdf"<<endl;
        int node_num = 0;
        L1(nodes_list[0], node_num);
        init_mv_prime_list();
        
// cout<<"asdf"<<endl;
        store_mv_prime_in_Object();
        // display_MV_and_MV_prime();
        cout<<"obj_vec.size()= "<<obj_vec.size()<<endl;
// cout<<"asdf"<<endl;
// cout<<"asdf"<<endl;
        // display_obj_list();
//         if(k>=obj_vec.size()){

//          for(int i=0;i<obj_vec.size();i++)
//          {
//              if(i!=obj_vec.size()-1)
//              cout<<nodes_list[i]->pre_order_number<<" ";
//              else 
//                  cout<<nodes_list[i]->pre_order_number<<endl;
//          }
//          cout<<"Total cost: "<<0<<endl;
//          return 0;
//      }

// cout<<"asdf"<<endl;
        int n = obj_vec.size();
        for(int u_num = 1; u_num <=n; u_num++){
            INITIALIZATION(u_num);
            
            L4ForPhaseOne(u_num, k);
            initialize_TV1_TUV0_RUV1_LUV0();
            init_LUVt();
        }

        
//             // check_Tv1();
//         // check_Luvv0();
//          // check_Tuvv0();
        

//         // for(int i=1; i<= n; i++){
//         //     for(int j=1; j<=k; j++){
//         //         cout<<"||T u||t for u="<<i<<" and t= "<<j<<": "<<Tut[i][j]<<endl;
//         //     }
//         // }

//         // for(int i =0;i<obj_vec.size();i++)
//         // {
//         //   // if(Cu[i]!=0)
//         //   // cout<<obj_vec[i]->post_orde<<"]= "<<Cu[i]<<endl;
//         //   cout<<(obj_vec[i])->post_order_number<<endl;
//         // }
//         // for(int i =0;i<obj_vec.size();i++)
//         // {
//         //   if(Nu[i]!=0)
//         //   cout<<"Nu["<<i<<"]= "<<Nu[i]<<endl;
//         // }

        
//         /*PHASE 2*/
//         //init();
//         //display_Cu();
//         //display_Nu();.

//         // cout<<"here comes phase2\n";

//             //display();
//     // for(int i1 = obj_vec[n-1]->mv->post_order_number; i1 < obj_vec[n-1]->node->post_order_number; i1++){
//     //     for(int j1=1; j1 <= k; j1++){
//     //         if(LUVt[i1][j1] == -1)
//     //         int c = B_uvt(obj_vec[n-1]->node, obj_vec[i1-1]->node, j1);
//     //     }
//     // }
//         // cout<<"yaha pe\n";
//         // B_uvt(obj_vec[n-1]->node, obj_vec[7]->node, 1);
//         //     // for(int i= 1; i<=obj_vec.size(); i++){
//         //         // for(int t=1; t<=k; t++){
//         //             Proxies(obj_vec[n-1]->node, k);
//         //         // }
//         //     // }
//         proxyList.push_back(obj_vec.size());
//         proxyL.insert(obj_vec.size());
//         Proxies(obj_vec[obj_vec.size()-1]->node, k);
        
//         for(int i=0;i<NuList.size();i++)
//         {

//          Proxies(obj_vec[NuList[i]-1]->node, CuList[i]);

//         }
//         // for(int i=0; i<proxies.size(); i++){
//         //     cout<<"Proxy: "<<proxies[i]<<endl;
//         // }
//         // cout<<endl<<"NuList and CuList: "<<endl;
//         // int sie=NuList.size();

//         // cout<<NuList.size()<<" is size of NuList"<<endl;

//  // for(int i1=0;i1<NuList.size();i1++)
//  //    {
//  //      cout<<"NuList["<<i1<<"]= "<<NuList[i1]<<endl;
//  //    }
//  //        cout<<"proxyList size= "<<proxyList.size()<<endl;
//     //     for(int i1=0;i1<proxyList.size();i1++)
//     // {
//     //   cout<<"proxyList["<<i1<<"]= "<<proxyList[i1]<<endl;
//     // }

//     // cout<<"size of set= "<<proxyL.size()<<endl;

//     int size1=proxyL.size();
//     vector<int> beforeFinalProxies;
//     for(int i=0;i<size1;i++)
//     {
//      int x=*proxyL.begin();
//      beforeFinalProxies.push_back(x);
        
//      proxyL.erase(x);

//     }

//     // for(int i=0;i<beforeFinalProxies.size();i++)
//     // {
//     //   cout<<"beforeFinalProxies["<<i<<"]= "<<beforeFinalProxies[i]<<endl;
//     // }

//     set<int> s;
//     for(int i=0;i<beforeFinalProxies.size();i++)
//     {
//      s.insert((obj_vec[beforeFinalProxies[i]-1])->node->pre_order_number);
//     }



//  int size2=s.size();
//     vector<int> finalProxies;
//     for(int i=0;i<size2;i++)
//     {
//      int x=*s.begin();
//      finalProxies.push_back(x);
        
//      s.erase(x);

//     }
//     cout<<"Proxies: "<<endl;
//     for(int i=0;i<finalProxies.size();i++)
//     {
//      if(i!=finalProxies.size()-1)
//          cout<<finalProxies[i]<<" ";
//      else 
//          cout<<finalProxies[i]<<endl;
//     }

//     cout<<"Total cost: "<<Tut[obj_vec.size()][k]<<endl;
//     // cout<<"afadf"<<endl;
//         // int i1=0;
//         // while(NuList.size()>0)
//         // {
//         //   int n=NuList.front();
            

//         //   NuList.pop();
//         //   int t3=CuList[i1];
//         //   i1++;
//         //   cout<<"n= "<<n<<" popped from NuList T3="<<t3<<" n= "<<n<<" obj_vec.size()= "<<obj_vec.size()<<endl;
//         //   cout<<"k= "<<k<<endl;
//         //   if(n==obj_vec.size())
//         //   {

//         //       cout<<"root popped"<<endl;
//         //       break;
//         //   }
            
//         //   if(k-1==t3)
//         //   {
//         //       cout<<"t3=1 left"<<endl;
//         //       proxyList.push_back(n);
//         //       break;
//         //   }
//         //   else{
                
//         //       cout<<"proxies called for "<<obj_vec[n-1]->node->post_order_number<<endl;
//         //   proxyList.push_back(n);
//         //   Proxies(obj_vec[n-1]->node, t3);

//         //   cout<<"NuList size = "<<NuList.size()<<" with front = "<<NuList.front()<<endl;

//         //   break;
//         //   }
//         // }
         


        return 0;
        
}
