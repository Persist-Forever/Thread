/**
 * 生产消费者测试代码
*/
#include "test_consumer_proc.h"
#include <thread>
#include "consumer_productor.h"
void TestConsumerProductor()
{
    std::thread arrRroducerThread[PRODUCER_THREAD_NUM];
    std::thread arrConsumerThread[CONSUMER_THREAD_NUM];

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++) {
        arrRroducerThread[i] = std::thread(ProducerThread, i);
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++) {
        arrConsumerThread[i] = std::thread(ConsumerThread, i);
    }

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++) {
        arrRroducerThread[i].join();
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++) {
        arrConsumerThread[i].join();
    }
}