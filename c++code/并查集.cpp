#include<iostream>
using namespace std;
int find(int x){//用递归的实现  
    if (father[x] != x)
        return find(father[x]);  
    return x;   
}
void unionn(int r1,int r2){
　  father[r2] = r1;
　}
int main(){
　　    cin >> n >> m;
　　    for (i = 1; i <= n; i++)
　　        father[i] = i;           //建立新的集合，每个集合只有自己，自己是自己的祖先
　　    for (i = 1; i <= m; i++) {
　　        scanf("%d%d",&x,&y);
　　        int r1 = find(x);
　　        int r2 = find(y);
　　        if (r1 != r2){
            unionn(r1,r2);
        }   
　　    }    
　　    cin >> q;
　　    for (i = 1; i <= q; i++)  {
　　        scanf("%d%d",&x,&y);
　　        if (find(x) == find(y)){
            printf("Yes\n");
        } else {
            printf("No\n");
        }
　　    }
　　    return 0;
　　}
