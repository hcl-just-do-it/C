#include <iostream>
#include<math.h>
/*
192.168.1.0/24
192.168.0.0/16
10.0.0.0/8
答案2^24+2^16
*/
using namespace std;
struct Subnet {
    uint32_t ip_addr;
    uint8_t len;
};
bool cmp(Subnet net1,Subnet net2){
    return net1.len<net2.len;
}

uint32_t get_number_of_ips(const std::vector<Subnet>& subnets){
    sort(subnets.begin(),subnets.end(),cmp);
    uint32_t ans = 0;
    vector<Subnet> a;
    struct Subnet t;
    t.ip_addr = (subnets[0].ip_addr)>>(32-subnets[0].len);
    t.len = subnets[0].len;
    a.push_back(t);
    ans+=pow(2,32-subnets[0].len);
    for(int i=1;i<subnets.size();i++){
        int flag = 0;
        for(int j=0;j<a.size();j++){
            if(a[j].len==subnets[i].len&&a[j].ip_addr==((subnets[i].ip_addr)>>(32-subnets[i].len))){
                flag = 1;//完全一样不加入答案不加入数组
            }else if(a[j].len<subnets[i].len&&(subnets[i].ip_addr>>(32-a[j].len))==a[j].ip_addr){
                flag = 2;//已有答案包含当前数据
            }
        }
        if(flag == 0){
            t.ip_addr = (subnets[i].ip_addr)>>(32-subnets[i].len);
            t.len = subnets[i].len;
            a.push_back(t);
            ans+=pow(2,32-subnets[i].len);
        }
    }
    return ans;
}

int main() {
    //int a;
    //cin >> a;
    cout << "Hello World!" << endl;
}