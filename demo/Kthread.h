#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>

void thread_task(int nCount)
{
    for(int nIndex = 0; nIndex < nCount; ++nIndex)
    {
        std::cout<<"the index is "<<nIndex<<"     hello world"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

}

void thread_task1(int nCount)
{
    std::this_thread::sleep_for(std::chrono::seconds(nCount));
    std::cout << "hello thread "
              << std::this_thread::get_id()
              << " paused " << nCount << " seconds" << std::endl;

}

void thread_taskref(int& nCount)
{
    for(int nIndex = 0; nIndex < 5; ++nIndex)
    {
        std::cout<<"the index ref is "<<nIndex<<"     hello world"<<std::endl;
        ++nCount;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

}

int thread_test()
{
    int nCount = 2;
    std::thread thread1;
    std::thread thread2(thread_task,nCount + 1);
    std::thread thread3(thread_taskref,std::ref(nCount));
    std::thread thread4(std::move(thread3));
    thread2.join();
    thread4.join();
    std::cout<< "Final Value nCount is "<<nCount<<std::endl;
    return EXIT_SUCCESS;
}

int thread_test1()
{
    std::thread threads[5];
    std::cout<<"Spawning 5 threads....\n";
    for(int nIndex = 0; nIndex < 5;nIndex++)
    {
        threads[nIndex] = std::thread(thread_task1,nIndex+1);
    }
    std::cout<<"Done spawning threads! Now wait for them to join \n";
    for(auto& t:threads)
    {
        t.join();
    }

    std::cout<<"All threads joined.\n";
    return EXIT_SUCCESS;
}

volatile  int counter(0);
std::mutex mtx;

void attempt_10K_increases()
{
    for(int nIndex = 0; nIndex < 10000; ++nIndex)
    {
        if(mtx.try_lock())
        {
            ++counter;
            mtx.unlock();
        }
    }
}


int mutex_test()
{
    std::thread threads[10];
    for(int nIndex = 0; nIndex < 10;++nIndex)
    {
        threads[nIndex] = std::thread(attempt_10K_increases);
    }

    for(auto& th:threads)
        th.join();

    std::cout<<counter<<"  successful increases of the counter.\n";
    return 0;
}

std::timed_mutex time_mtx;
void fireworks()
{
    while (!time_mtx.try_lock_for(std::chrono::milliseconds(200)))
    {
        std::cout<<"-";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"*\n";
    time_mtx.unlock();
}

int time_mutex_test()
{
    std::thread threads[10];
    for(int nIndex = 0; nIndex < 10;++nIndex)
    {
        threads[nIndex] = std::thread(fireworks);

    }

    for(auto& th:threads) th.join();
    return 0;
}

std::mutex mutex_test_value;
void print_block(int n, char c)
{
    std::unique_lock<std::mutex> lck(mutex_test_value);
    for(int nIndex = 0; nIndex < n; ++nIndex)
    {
        std::cout<<c;
    }
    std::cout<<'\n';
}

int unique_lock_test()
{
    std::thread thread1(print_block,50,'*');
    std::thread thread2(print_block,50,'#');

    thread1.join();
    thread2.join();

    return 0;
}