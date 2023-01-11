#include <bits/stdc++.h>
using namespace std;
const int macn=1e5+50;//节点数
const int macm=2e5+50;//边数
int head[macn],vis[macn],dis[macn];
int num;
struct edge{
    int v,w,next;
}a[macm];
struct node{
    int index,distance;
    bool operator <(node n)const{
        return distance>n.distance ;
    }
};
void inline add(int u,int v,int w){
    a[++num].v =v;
    a[num].w =w;
    a[num].next =head[u];
    head[u]=num;
}
void dij(){
    memset(dis,INT_MAX,sizeof(dis));
    priority_queue<node>q;
    dis[0]=0;//勿漏
    q.push({0,0});
    while(!q.empty()){
        node t=q.top();
        q.pop();
        int x=t.index;
        if(vis[x])
            continue;
        vis[x]=1;
        for(j=head[x];j!=0;j=a[j].next){
            int v=a[j].v ;
            if(dis[v]>dis[x]+a[j].w ){
                dis[v]=dis[x]+a[j].w;
                if(!vis[v])//可以不加
                    q.push((node){v,dis[v]});
            }
        }
    }
}
int main(){
    num=0;
    int x,y,z;
    cin>>n>>m>>s;
    for(i=1;i<=m;i++){
        cin>>x>>y>>z;
        add(x,y,z);
    }
    dij();
}