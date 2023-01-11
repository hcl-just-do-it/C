#include<bits/stdc++.h>
using namespace std;
int main(){
  	int n;cin>>n;
  	vector<int>a(n,0);
  	for(int i=0;i<n;i++){
  		int x,y;cin>>x>>y;
  		a[i] = max(0,a[x]-a[y]);
	  }
	sort(a.begin(),a.end());
	int t = 0;
	for(int i=n-1;i>=0;i--){
		
		t++;
	}
    return 0;
}