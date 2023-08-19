/**
 *  生产者：不停的生产数据，直到最大缓冲区
 *  消费者：不断消费数据，直到数据为空
*/
#include "consumer_productor.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

std::mutex g_cvMutex;
std::condition_variable g_cv;

//缓存区
std::deque<int> g_data_deque;
//缓存区最大数目
constexpr int  MAX_NUM = 30;
//数据
int g_next_index = 0;

void  ProducerThread(int threadId)
{
	 while (true)
	 {
	     std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	     //加锁
	     std::unique_lock <std::mutex> lk(g_cvMutex);
	     //当队列未满时，继续添加数据
	     g_cv.wait(lk, [](){ return g_data_deque.size() <= MAX_NUM; });
	     g_next_index++;
         g_next_index = g_next_index > 100000 ? 0 : g_next_index;
	     g_data_deque.push_back(g_next_index);
	     std::cout << "producer_thread: " << threadId << "  " << std::this_thread::get_id() << " producer data: " << g_next_index;
	     std::cout << " queue size: " << g_data_deque.size() << std::endl;
	     //唤醒其他线程 
	     g_cv.notify_all();
	     //自动释放锁
	 }
}

void  ConsumerThread(int threadId)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(550));
        //加锁
        std::unique_lock <std::mutex> lk(g_cvMutex);
        //检测条件是否达成
        g_cv.wait( lk,   []{ return !g_data_deque.empty(); });
        //互斥操作，消息数据
        int data = g_data_deque.front();
        g_data_deque.pop_front();
        std::cout << "\tconsumer_thread: " << threadId << "  " << std::this_thread::get_id() << " consumer data: ";
        std::cout << data << " deque size: " << g_data_deque.size() << std::endl;
        //唤醒其他线程
        g_cv.notify_all();
        //自动释放锁
    }
}
