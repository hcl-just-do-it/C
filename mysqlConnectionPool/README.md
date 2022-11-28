安装json库
sudo apt-get install libjsoncpp-dev
编译
cd ./build&&cmake ..&&make
运行
 cd ../bin&&./main

功能
连接池
保证可用连接数动态增大连接池
定时销毁空闲连接
超时连接

 待完善
 脚本sql

所有连接 = 队列里的可用连接+忙碌连接


测试
bug 加入maxSize判断应该用if，while会阻塞主线程。

