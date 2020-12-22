#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#pragma once
#include <set>
#include <thread>
#include <QThreadPool>
class ThreadPool : public QObject
{
    Q_OBJECT
public:
    ThreadPool();
    ~ThreadPool();
    void addToThread(std::function<void()> fun);
    static ThreadPool *instance;
    static ThreadPool *getInstance();
    QThread* addToThread(QObject *object);

private:
    //    QThreadPool *pool = nullptr;
    std::set<QThread *> pool;
};

#endif // THREAD_POOL_H
