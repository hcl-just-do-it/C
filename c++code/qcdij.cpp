class Solution {//前向星，空间时间好，vector数组开链，时间同前向星，空间多于前向星。二维数组空间同vector数组，时间多于vector数组，因为二维数组要遍历所有顶点，vector只要遍历有边相连的点。
public://dij有两步，先找这个点所有边里最小的，然后更新这个点相连的所有边。优先队列优化第一步，前向星或者vector数组开链优化的是第二步。
    int n,m;
    vector<pair<int,int>>mp[100005];
    int dis[100005],vis[100005];
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int getid(int x,int y){
        return x*m+y;//一行有m个
    }
    void dij(vector<vector<int>>& grid){
        memset(dis,0x3f,sizeof(dis));dis[0] = 0;//用INT_MAX有加法会炸int
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>que;
        que.push({0,0});
        while(que.size()){
            auto u = que.top();que.pop();//u.first是排序依据，是0,0的id到u.first这个id的距离
            if(vis[u.second])continue;
            vis[u.second] = 1;
            for(auto v : mp[u.second]){
                if(dis[v.second]>dis[u.second]+v.first){
                    dis[v.second] = dis[u.second]+v.first;
                    que.push({dis[v.second],v.second});
                }
            }
        }
    }
    int minimumObstacles(vector<vector<int>>& grid) {//角落不允许输入障碍物
        n = grid.size(); m = grid[0].size();
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                for(auto [dx,dy] : dirs){
                    if(i+dx<0||i+dx>=n||j+dy<0||j+dy>=m)continue;
                    mp[getid(i,j)].push_back({grid[i][j],getid(i+dx,j+dy)});
                } 
            }
        }
        dij(grid);
        return dis[getid(n-1,m-1)];
    }
};
/*
三种建图的一点总结//前向星，空间时间好，vector数组开链，时间同前向星，空间多于前向星。二维数组空间多余vector数组，时间多于vector数组，因为二维数组要遍历所有顶点，vector只要遍历有边相连的点，存储也是。
//dij有两步，先找这个点所有边里最小的，然后更新这个点相连的所有边。优先队列优化第一步，前向星或者vector数组开链优化的是第二步。
*/