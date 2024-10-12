#pragma once
//
//  Semaphore.h
//  MultiThread
//
//  Created by Borna Noureddin
//  Copyright (c) BCIT. All rights reserved.
//

#ifndef Semaphore_h
#define Semaphore_h

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count_ = 0) : count(count_) {}

    // Notifies a thread, locks a resource, and increments the count by 1.
    inline void notify()
    {
        //### Use unique_lock to lock a resource
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }

    // Locks a resource, waits for a return of count above 0, and decrements the count by 1.
    inline void wait()
    {
        //### Use unique_lock to lock a resource
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] {return count > 0; });
        --count;
    }

    // Sets the count.
    void setCount(int newCount)
    {
        count.store(newCount);
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<int> count;
};

#endif
