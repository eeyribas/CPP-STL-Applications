#ifndef CUSTOMQUEUE_H
#define CUSTOMQUEUE_H

#include <QByteArray>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

template <class T, int SIZE = 1024>
class CustomQueue
{
public:
    CustomQueue(int size = SIZE);
    void putQueue(const T &item);
    T getQueue();
    T peek();
    bool isEmpty() const { return m_queue.count() == 0; }
    int count() const { return m_queue.count(); }
    void clear() { m_queue.clear(); }

private:
    QQueue<T> m_queue;
    QSemaphore m_semProducer;
    QSemaphore m_semConsumer;
    QMutex m_mutex;
    int m_size;
};

template <class T, int SIZE>
CustomQueue<T, SIZE>::CustomQueue(int size)
    : m_semProducer(size), m_semConsumer(0), m_size(size)
{
}

template <class T, int SIZE>
void CustomQueue<T, SIZE>::putQueue(const T &item)
{
    m_semProducer.acquire();
    m_mutex.lock();
    m_queue.enqueue(item);
    m_mutex.unlock();
    m_semConsumer.release();
}

template <class T, int SIZE>
T CustomQueue<T, SIZE>::getQueue()
{
    T item;

    m_semConsumer.acquire();
    m_mutex.lock();
    item = m_queue.dequeue();
    m_mutex.unlock();
    m_semProducer.release();

    return item;
}

template <class T, int SIZE>
T CustomQueue<T, SIZE>::peek()
{
    T item;

    m_semConsumer.acquire();
    m_mutex.lock();
    item = m_queue.head();
    m_mutex.unlock();
    m_semProducer.release();

    return item;
}

#endif // CUSTOMQUEUE_H
