#include<bits/stdc++.h>
using namespace std;
int a[1000050];
int ans[1000050];
int main(){
  	int n,p;cin>>n>>p;
  	for(int i=0;i<n;i++){
  		cin>>a[i];
    }
    sort(a,a+n);
	for(int i=0;i<n;i++){
		int l = 0,r = n-1,mx = 0;
		if(l!=i&&a[i]+a[l]>=p)
			ans[i] = (a[i]+a[r])%p;
		else if(r!=i&&a[i]+a[r]<p)
			ans[i] = (a[i]+a[r])%p;
		else
		while(l<r){
			int mid = l+(r-l)/2;
			if(mid!=i)
				mx = max(mx,(a[i]+a[mid])%p);
			if(mid-1!=i)
				mx = max(mx,(a[i]+a[mid-1])%p);
			if(mid+1!=i)
				mx = max(mx,(a[i]+a[mid+1])%p);
			if(a[i]+a[mid]>=p){
				r = mid-1;
			}else{
				l = mid+1;
			}
		}
		if(i!=r)
			ans[i] = max(mx,(a[i]+a[r])%p);
		else
			ans[i] = mx;
	}
	for(int i=0;i<n-1;i++)
		cout<<ans[i]<<" ";
	cout<<ans[n-1];
    return 0;
}