#include<iostream>//prim算法
#include<algorithm>
#include<vector>

using namespace std;

int prime(vector<vector<int>>& edge){
    int n = edge.size();
    vector<bool> visit(n, false);
    vector<int> dis(n, INT_MAX);

    dis[1] = 0;
    int ans = 0;
    for(int i=1; i<n; ++i){
        int u=-1, mins=INT_MAX;
        // 在dis中找到路径最近的一个节点
        for(int j=1; j<n; ++j){
            if(visit[j]==false && dis[j]<mins){
                u = j;
                mins = dis[j];
            }
        }
        if(u==-1) return -1;
        // 将节点加入最短路径
        visit[u] = true;
        ans += dis[u];

        // 更新dis中的到当前最短路径的距离
        for(int v=1; v<n; ++v){
            if(visit[v]==false && edge[u][v] < dis[v])
                dis[v] = edge[u][v];
        }
    }
    return ans;
}


int main(){
    int a, b, w;
    int n, m;
    cin>>n>>m;
    vector<vector<int>> edge(n+1, vector<int>(n+1, INT_MAX));
    for(int i=0; i<m; ++i){
        cin>>a>>b>>w;
        edge[a][b] = w;
        edge[b][a] = w;
    }
    cout<<prime(edge);
}
/*
4 5
1 2 2
1 3 3
1 4 5
2 4 4
3 4 1
*/
/*
4 5
1 2 2
1 3 3
1 4 5
2 4 4
3 4 1
*/
