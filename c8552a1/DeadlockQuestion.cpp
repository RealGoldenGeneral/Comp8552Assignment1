//
//  Created by Borna Noureddin
//  Copyright (c) 2015 BCIT. All rights reserved.
//  COMP 8551 - Deadlocks
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <mutex>
#include <condition_variable>


class CAccount
{
public:
    CAccount() { balance = 100; };
    ~CAccount() {};
    void Transfer(CAccount& from, double amount)
    {
        std::lock_guard<std::mutex> lock_from(from.m);
        std::chrono::milliseconds timespan(100);
        std::this_thread::sleep_for(timespan);
        std::lock_guard<std::mutex> lock_to(this->m);
        from.balance -= amount;
        this->balance += amount;
    }
    double GetBalance() { return balance; };

private:
    std::mutex m;
    double balance;
};

void TransferToChequing(CAccount* chequing, CAccount* savings)
{
    chequing->Transfer(*savings, 10);
}

void TransferToSavings(CAccount* chequing, CAccount* savings)
{
    savings->Transfer(*chequing, 20);
}


int main(int argc, char* argv[])
{
    CAccount chequing, savings;
    std::cout << "Start potential deadlock actions:\n";
    std::thread* thread1 = new std::thread(TransferToChequing, &chequing, &savings);
    std::thread* thread2 = new std::thread(TransferToSavings, &chequing, &savings);
    thread1->join();
    thread2->join();
    std::cout << "\tChq = " << chequing.GetBalance();
    std::cout << "; Sav = " << savings.GetBalance() << std::endl;

    return 0;
}
