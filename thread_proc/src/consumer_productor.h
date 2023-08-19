/**
 * 生产消费者基本定义
*/
#pragma once
//生产者，消费者线程个数
constexpr int PRODUCER_THREAD_NUM  = 3;
constexpr int CONSUMER_THREAD_NUM = 3;
void ProducerThread(int threadId);
void ConsumerThread(int threadId);