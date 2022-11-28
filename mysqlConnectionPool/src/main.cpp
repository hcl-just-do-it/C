#include <iostream>
#include <memory>
#include "MysqlConn.h"
#include "ConnectionPool.h"
#include <thread>
using namespace std;

// 1. 单线程: 使用/不使用连接池
// 2. 多线程: 使用/不使用连接池

void op1(int begin, int end)
{
    for (int i = begin; i < end; ++i)
    {
        MysqlConn conn;
        conn.connect("root", "root", "mydb", "localhost");
        char sql[1024] = { 0 };
        sprintf(sql, "insert into user1(id, name, sex) values(%d, '%s', '%s')", 21,  "op1", "male");
        conn.update(sql);
    }
}

void op2(ConnectionPool* pool, int begin, int end)
{
    for (int i = begin; i < end; ++i)
    {
        shared_ptr<MysqlConn> conn = pool->getConnection();
        if(conn == nullptr){
            cout<<"超时了哦"<<endl;
            continue;
        }
        char sql[1024] = { 0 };
        //sprintf(sql, "insert into person values(%d, 25, 'man', 'tom')", i);
        sprintf(sql, "insert into user1(id, name, sex) values(%d, '%s', '%s')", i,  "op2", "female");
        conn->update(sql);
    }
}

void test1()
{
#if 0
    // 非连接池, 单线程, 用时: 16536193225 纳秒, 16536 毫秒
    steady_clock::time_point begin = steady_clock::now();
    op1(0, 5000);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "非连接池, 单线程, 用时: " << length.count() << " 纳秒, "
        << length.count() / 1000000 << " 毫秒" << endl;
#else
    // 连接池, 单线程, 用时: 13862254582 纳秒, 13862 毫秒
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    steady_clock::time_point begin = steady_clock::now();
    op2(pool, 0, 5000);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "连接池, 单线程, 用时: " << length.count() << " 纳秒, "
        << length.count() / 1000000 << " 毫秒" << endl;
    cout<<"最大conn = "<<pool->m_connMax<<endl;

#endif
}

void test2()
{
#if 0
    // 非连接池, 多单线程, 用时: 7335618992 纳秒, 7102 毫秒
    MysqlConn conn;
    conn.connect("root", "root", "mydb", "localhost");
    steady_clock::time_point begin = steady_clock::now();
    thread t1(op1, 0, 1000);
    thread t2(op1, 1000, 2000);
    thread t3(op1, 2000, 3000);
    thread t4(op1, 3000, 4000);
    thread t5(op1, 4000, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "非连接池, 多单线程, 用时: " << length.count() << " 纳秒, "
        << length.count() / 1000000 << " 毫秒" << endl;

#else
    // 连接池, 多单线程, 用时: 5380805397 纳秒, 5380 毫秒
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    steady_clock::time_point begin = steady_clock::now();
    thread t1(op2, pool, 0, 1000);
    thread t2(op2, pool, 1000, 2000);
    thread t3(op2, pool, 2000, 3000);
    thread t4(op2, pool, 3000, 4000);
    thread t5(op2, pool, 4000, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "连接池, 多单线程, 用时: " << length.count() << " 纳秒, "
        << length.count() / 1000000 << " 毫秒" << endl;
    cout<<"最大conn = "<<pool->m_connMax<<endl;

#endif
}

int query()
{
    MysqlConn conn;
    conn.connect("root", "root", "mydb", "localhost");
    char sql[1024] = { 0 };
    sprintf(sql, "insert into user1(id, name, sex) values(%d, '%s', '%s')", 21,  "zhangsan", "query");
    conn.update(sql);
    string ssql = "select * from user1";
    conn.query(ssql);
    while (conn.next())
    {
        cout << conn.value(0) << ", "
            << conn.value(1) << ", "
            << conn.value(2) << ", "
            << conn.value(3) << endl;
    }
    return 0;
}
int main()
{
    //query();
    //test1();
    test2();
    return 0;
}