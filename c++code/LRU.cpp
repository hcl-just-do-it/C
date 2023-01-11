#include<bits/stdc++.h>
using namespace std;
struct node{
	int key;
	int value;
	struct node* next;
	struct node* pre;
	node():key(0),value(0),next(nullptr),pre(nullptr){};
	node(int _key,int _value):key(_key),value(_value),next(nullptr),pre(nullptr){};
};
unordered_map<int, node*>mapp;
node *head, *tail;
class Cache{
public:
	int capacity;int size;
	Cache(int n){
		capacity = n;
		head = new node();
		tail = new node();
		head->next = tail;
		tail->pre = head;
	};
	bool put(int key,int value){
		if(mapp.count(key) == 0){
			node *t = new node(key,value);
			addhead(t);
			size++;
			mapp[key] = t;
			if(size>capacity){
				mapp.erase(tail->pre->key);
				remove(tail->pre);
				size--;
			}
			return false;
		}else{
			node *t = mapp[key];
			node *newt = new node(t->key,t->value);
			remove(t);
			addhead(newt);
			mapp[key] = newt;
		}
		return true;
	}
	void remove(node *t){
		t->next->pre = t->pre;
		t->pre->next = t->next;
		delete t;
		t = nullptr;
	}
	void addhead(node *t){
		t->next = head->next;
		t->pre = head;
		head->next->pre = t;
		head->next = t;
	}
	int get (int key){
		if(mapp.count(key) == 0){
			return -1;
		}
		node *t = mapp[key];
		node *newt = new node(t->key,t->value);
		remove(t);
		addhead(newt);
		mapp[key] = newt;
		return newt->value;
	}
};
int main(){
	Cache cache(3);
	cout<<cache.get(0)<<endl;//缓存为空获取为-1
	cache.put(1,1);//依次加入1，2，3,访问1，再插入4，那么操作是1，2，3进入缓存，访问1之后，插入4可淘汰2
	cache.put(2,2);
	cache.put(3,3);
	cout<<cache.get(1)<<endl;
	cache.put(4,4);
	cout<<cache.get(2)<<endl;
	cout<<cache.get(4)<<endl;
	return 0;
}
/*
双向链表删除O（1）
mapp里的value设置成链表节点，方便直接得到对应节点，删除，更新和取值都很方便。
*/
