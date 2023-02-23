#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

//20K0325 BCS6E

string city(int);

typedef struct Pair{
        string s;
        int cost;
    }Pair;

struct n {
   int p;
   vector<int> info;
   struct n *l;
};
class Priority_Queue {
   private:
      //Declare a front pointer f and initialize it to NULL.
      n *f;
   public:
      Priority_Queue() {
         f = NULL;
      }
      void insert(vector<int> i, int p) {
         n *t, *q;
         t = new n;
         t->info = i;
         t->p = p;
         if (f == NULL || p < f->p) {
            t->l= f;
            f = t;
         } else {
            q = f;
            while (q->l != NULL && q->l->p <= p)
               q = q->l;
               t->l = q->l;
               q->l = t;
         }
      }

      void Delete(int val,int p){
        n* temp=f,*prev=NULL;
        while(temp!=NULL){
            if(temp->info[temp->info.size()-1]==val && temp->p==p){
                if(temp==f){
                    temp=temp->l;
                    f=temp;
                    delete(temp);
                    break;
                }else{
                    prev->l=temp->l;
                    delete(temp);
                    break;
                }
            }
            prev=temp;
            temp=temp->l;
        }
      }

      int find(int val){
        n* temp=f;
        while(temp!=NULL){
            if(temp->info[temp->info.size()-1]==val){
                return 1;
            }
            temp=temp->l;
        }
        return 0;
      }

      vector<int> del() {
         n *t;
         if(f == NULL){ //if queue is null
            cout<<"Queue Underflow\n";
            vector<int> v;
            return v;
         }else {
            t = f;
            f = f->l;
            return t->info;
            free(t);
         }
      }

      int empty(){
        if(f==NULL) return 1;
        else return 0;
      }
      void show(){
         n *ptr;
         ptr = f;
         int i=0;
         if (f == NULL)
            cout<<"Queue is empty\n";
         else {
            cout<<"Current queue: \n";
            while(ptr != NULL) {
               cout<<"Element "<<i<<"("<<ptr->p<<"): "; 
               for(int j=0;j<ptr->info.size();j++){
                cout<<city(ptr->info[j])<<" ";
               }
               cout<<endl<<endl;
               ptr = ptr->l;
               i++;
         }
      }
    }
};

typedef struct edge{
    int u,v;
    int w;
    edge(int u,int v,int w):u(u),v(v),w(w){}
    int weight(){
        return w;
    }
}edge;

string city(int v){
    if(v==0){
        return "Oradea";
    }else if(v==1){
        return "Zerind";
    }else if(v==2){
        return "Arad";
    }else if(v==3){
        return "Timisoara";
    }else if(v==4){
        return "Lugoj";
    }else if(v==5){
        return "Mehadia";
    }else if(v==6){
        return "Drobeta";
    }else if(v==7){
        return "Craiova";
    }else if(v==8){
        return "Pitesti";       
    }else if(v==9){
        return "Bucharest";
    }else if(v==10){
        return "Giurgiu";
    }else if(v==11){
        return "Urzeceni";
    }else if(v==12){
        return "Hirsova";
    }else if(v==13){
        return "Eforie";
    }else if(v==14){
        return "Vaslui";
    }else if(v==15){
        return "Iasi";
    }else if(v==16){
        return "Neamt";
    }else if(v==17){
        return "Fagaras";
    }else if(v==18){
        return "Sibiu";
    }else{
        return "Rimnicu Vilcea";
    }
}

class Graph{
    private:
    int vertices;
    vector<vector<int>> list;
    vector<edge> edges;
    vector<int> underdfs,visited;
    unordered_map<int,int> heuristics;

    void reset(){
        underdfs.clear();
        underdfs.resize(vertices,0);
        visited.clear();
        visited.resize(vertices,0);
    }

    int pathCost(vector<int> v,char ch){
        int sum=0;
        cout<<"\nPath: ";
        if(ch=='b'){
            for(int i=0;i<v.size()-1;i++){
                cout<<city(v[i])<<"-> ";
                for(int j=0;j<edges.size();j++){
                    if((edges[j].u==v[i] && edges[j].v==v[i+1]) || (edges[j].v==v[i] && edges[j].u==v[i+1])){
                        sum+=edges[j].weight();
                    }
                }
            }
            cout<<city(v[v.size()-1])<<"\n";
        }else{
            for(int i=v.size()-1;i>0;i--){
            cout<<city(v[i])<<"-> ";
            for(int j=0;j<edges.size();j++){
                if((edges[j].u==v[i] && edges[j].v==v[i-1]) || (edges[j].v==v[i] && edges[j].u==v[i-1])){
                    sum+=edges[j].weight();
                }
            }
        }
        cout<<city(v[0])<<"\n";
        }
        cout<<"Cost: "<<sum<<endl;
        return sum;
    }

    int DFS(int u,int dest, int depth, int d,vector<int> &path){
        if(u==dest){
            //add u to path
            path.push_back(u);
            return 1;
        }
        if(d<depth){
            underdfs[u]=1;
            for(int i=0;i<list[u].size();i++){
                int v=list[u][i];
                if(!underdfs[v] && !visited[v]){
                    if(DFS(v,dest,depth,d+1,path)==1){
                        //add u to path
                        path.push_back(u);
                        return 1;
                    }
                }
            }
        }
        visited[u]=1;
        return 0;
    }

    int Cost(vector<int> v){
        int sum=0;
        for(int i=0;i<v.size()-1;i++){
            for(int j=0;j<edges.size();j++){
                if((edges[j].u==v[i] && edges[j].v==v[i+1]) || (edges[j].v==v[i] && edges[j].u==v[i+1])){
                    sum+=edges[j].weight();
                }
            }
        }
        return sum;
    }

public:
    Graph(int v){
        this->vertices=v;
        list.resize(v);
        underdfs.resize(v,0);
        visited.resize(v,0);
    }

    int getVertices(){
        return vertices;
    }

    void displayEdges(){
        for(int i=0;i<vertices;i++){
            cout<<city(i)<<": ";
            for(int j=0;j<list[i].size();j++){
                cout<<city(list[i][j])<<", ";
            }
            cout<<"\b\b \n";
        }
    }
    
    int bfs(int s,int t){
        queue<vector<int>> q;
        vector<int> v,visited;
        v.push_back(s);q.push(v);
        visited.resize(this->vertices,0);
        visited[s]=1;
        while(!q.empty()){
            v=q.front();q.pop();
            int node=v[v.size()-1];
            if(node==t) return pathCost(v,'b');
            for(int i=0;i<list[node].size();i++){
                if (!visited[list[node][i]]){
                    vector<int> v1(v);
                    v1.push_back(list[node][i]);q.push(v1);
                    visited[list[node][i]]=1;
                }
            }
        }
        cout<<"\nPath not found";
        return 0;
    }

    int bfs1(int s,int t){
        queue<vector<int>> q;
        vector<int> v,visited;
        v.push_back(s);q.push(v);
        visited.resize(this->vertices,0);
        visited[s]=1;
        while(!q.empty()){
            v=q.front();q.pop();
            int node=v[v.size()-1];
            for(int i=0;i<list[node].size();i++){
                if (!visited[list[node][i]]){
                    vector<int> v1(v);
                    v1.push_back(list[node][i]);
                    if(list[node][i]==t) return pathCost(v1,'b');
                    q.push(v1);
                    visited[list[node][i]]=1;
                }
            }
        }
        cout<<"\nPath not found";
        return 0;
    }


    int dfs(int s,int t){
        int depth=1;
        vector<int> path;
        while(!DFS(s,t,depth,0,path)){
            depth++;
            reset();
        }
        return pathCost(path,'d');
    }

    int ucs(int s,int t){
        Priority_Queue pq;
        vector<int> v,visited;
        v.push_back(s);pq.insert(v,0);
        visited.resize(this->vertices,0);
        visited[s]=1;
        while(!pq.empty()){
            v=pq.del();
            int node=v[v.size()-1];
            
            if(node==t) return pathCost(v,'b');
            visited[node]=1;
            for(int i=0;i<list[node].size();i++){
                vector<int> v1(v);
                v1.push_back(list[node][i]);
                int p=Cost(v1);
                if (!visited[list[node][i]] && !pq.find(list[node][i])){
                    pq.insert(v1,p);
                }else if(pq.find(list[node][i])){
                    pq.Delete(list[node][i],Cost(v));
                    pq.insert(v1,p);
                }
            }
        }
        cout<<"\nPath not found";
        return 0;
    }

    int bestfs(int s,int t){
        Priority_Queue pq;
        vector<int> v,visited;
        v.push_back(s);pq.insert(v,heuristics[s]);
        visited.resize(this->vertices,0);
        visited[s]=1;
        while(!pq.empty()){
            v=pq.del();
            int node=v[v.size()-1];
        
            visited[node]=1;
            for(int i=0;i<list[node].size();i++){
                vector<int> v1(v);
                v1.push_back(list[node][i]);
                if(list[node][i]==t) return pathCost(v1,'b');
                int p=heuristics[list[node][i]];    
                if (!visited[list[node][i]] && !pq.find(list[node][i])){
                    pq.insert(v1,p);
                }
            }
        }
        cout<<"\nPath not found";
        return 0;
    }

    void addEdge(int u,int v,int w){
        list[u].push_back(v);
        list[v].push_back(u);
        edge e(u,v,w);
        edges.push_back(e);
    }
    void setHeuristic(int v,int h){
        heuristics[v]=h;
    }
};

void searchGraph(Graph g){
    cout<<"Key:\tCity\n";
    for(int i=0;i<g.getVertices();i++){
            cout<<i<<":\t"<<city(i)<<endl;
    }
    while(1){
        int s,t;
        char ch;
        vector<Pair>results;
        int arr[4];
        cout<<"\n\nEnter source and destination: ";
        cin>>s>>t;
        Pair p;
        cout<<"\nBreadth First Search";
        arr[0]=g.bfs(s,t);
        p.cost=arr[0];
        p.s="Breadth First Search";
        results.push_back(p);

        cout<<"\nUniform Cost Search";
        arr[1]=g.ucs(s,t);
        p.cost=arr[1];
        p.s="Uniform Cost Search";
        results.push_back(p);

        cout<<"\nIterative Deepening";
        arr[2]=g.dfs(s,t);
        p.cost=arr[2];
        p.s="Iterative Deepening";
        results.push_back(p);

        cout<<"\nBest First Search";
        arr[3]=g.bestfs(s,t);
        p.cost=arr[3];
        p.s="Best First Search";
        results.push_back(p);

        sort(arr,arr+4);
        
        cout<<"\n\nResults:\n";
        for (int i = 0; i < 4; i++)
        {
            for(int j=0;j<results.size();j++){
                if(results[j].cost==arr[i]){
                    Pair p1;
                    cout<<results[j].s<<": "<<results[j].cost<<endl;
                    p1.cost=results[j].cost;
                    p1.s=results[j].s;
                    results.erase(results.begin()+j);
                }
            }
        }
        cout<<"\nDo you wish to continue?";
        cin>>ch;
        if(ch!='y')
        break;
    }
    
}

int main(){
    Graph g(20);
    g.addEdge(0,1,71);
    g.addEdge(1,2,75);
    g.addEdge(2,3,118);
    g.addEdge(3,4,111);
    g.addEdge(4,5,70);
    g.addEdge(5,6,75);
    g.addEdge(6,7,120);
    g.addEdge(7,8,138);
    g.addEdge(8,9,101);
    g.addEdge(9,10,90);
    g.addEdge(9,11,85);
    g.addEdge(11,12,98);
    g.addEdge(12,13,86);
    g.addEdge(11,14,142);
    g.addEdge(14,15,92);
    g.addEdge(15,16,87);
    g.addEdge(9,17,211);
    g.addEdge(17,18,99);
    g.addEdge(18,19,80);
    g.addEdge(0,18,151);
    g.addEdge(2,18,140);
    g.addEdge(7,19,146);
    g.addEdge(8,19,97);

    g.setHeuristic(0,380);
    g.setHeuristic(1,374);
    g.setHeuristic(2,366);
    g.setHeuristic(3,329);
    g.setHeuristic(4,244);
    g.setHeuristic(5,241);
    g.setHeuristic(6,242);
    g.setHeuristic(7,160);
    g.setHeuristic(8,100);
    g.setHeuristic(9,0);
    g.setHeuristic(10,77);
    g.setHeuristic(11,80);
    g.setHeuristic(12,151);
    g.setHeuristic(13,161);
    g.setHeuristic(14,199);
    g.setHeuristic(15,226);
    g.setHeuristic(16,234);
    g.setHeuristic(17,176);
    g.setHeuristic(18,253);
    g.setHeuristic(19,193);

    g.displayEdges();
    
    searchGraph(g);
    cout<<"\n*****************20K0325 BCS-6E AI Assignment 1*****************";
}