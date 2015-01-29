// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <thread>
#include <shand/concurrent/queue.hpp>
 
void producer(shand::concurrent_queue<int>& que)
{
    for (int i = 0; i < 100; ++i) {
        que.push(i);
    }
}
 
void consumer(shand::concurrent_queue<int>& que)
{
    int i = 0;
    for (;;) {
        if (boost::optional<int> x = que.pop()) {
            std::cout << x.get() << std::endl;
            ++i;
        }
 
        if (i > 30)
            return;
    }
}
 
int main()
{
    shand::concurrent_queue<int> que;
 
    std::thread t1(producer, std::ref(que));
    std::thread t2(consumer, std::ref(que));
 
    t1.join();
    t2.join();
}

/*
output:
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
*/

