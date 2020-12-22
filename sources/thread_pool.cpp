#include "thread_pool.h"
#include <QDebug>

ThreadPool* ThreadPool::instance = nullptr;

 ThreadPool::ThreadPool()
{
//    pool = new QThreadPool();
//    uint8_t count_threads = std::thread::hardware_concurrency();
//    pool->setMaxThreadCount(count_threads - 1);
    instance = this;
}

 ThreadPool *ThreadPool::getInstance()
{
    return instance;
}

// void ThreadPool::addToThread(std::function<void()> fun)
//{
//    instance->pool->start(fun);
//    qDebug() << instance->pool->activeThreadCount();
//}

ThreadPool::~ThreadPool()
{
    for (auto& thread : pool)
    {
        thread->quit();
        thread->wait();
    }
}

QThread *ThreadPool::addToThread(QObject* object)
{
    QThread* thread = new QThread();
    connect(thread, &QThread::finished, object, &QObject::deleteLater);
    pool.insert(thread);
    object->moveToThread(thread);
    thread->start();
    return thread;
}
