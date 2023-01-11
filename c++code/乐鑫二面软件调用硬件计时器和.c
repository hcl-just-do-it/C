#include <stdio.h>//截止时间排序，只需要给最近截止时间的调用硬件接口就行
typedef struct node{
    int data;
    pfunc* callb;
    struct node *next;
}node;
node *head = （node *）malloc(sizeof(struct node);
head->data = -1;head->next = NULL;
tail = head;
int timer_start(uint32_t timeout, pfunc callback)
{
    node *t = (node *)malloc(sizeof(struct node));
    t->data = get_now()+timeout;
    t->callb = callback;
    t->next = NULL;
    node *pre = head;
    node *cur = head->next;
    if(cur== NULL){
        pre->next = t;
        set_timer(head->next->data);
    }else{
        
        while(cur){
            if(t->data<cur->data){
                t->next = cur;
                pre->next = t;
                if(head->next == t)
                    set_timer(head->next->data);
                break;
            }
            pre = cur;
            cur=cur->next;
        }
    }
    
}

void timer_fired(void) 
{
    node *t = head->next;
    head->next = head->next->next;
    free(t);
    t = NULL;
    if(head->next){
        set_timer(head->next->data);
    }
}


int main(){
    
    //int a;
    //scanf("%d", &a);
    //printf("%d\n", a);
    /*
    
APP1:

timer_start(5, callback1) ;

timer_start(10, callback2); 


APP2:

timer_start(5, callback3); 
    */
    printf("%s\n","Hello World!");
}