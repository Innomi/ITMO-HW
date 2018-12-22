#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <iterator>
#include <atomic>


class ThreadPool
{
public:
    explicit ThreadPool(std::size_t);
    ~ThreadPool();
    void execute(std::function<void()> const &);
    void execute(std::function<void()> &&);

    template <class Iter, class F>
    void parallel(Iter begin, Iter end, F const & function)
    {
        std::atomic_int_fast64_t counter(0);
        unsigned int step = (end - begin) / (threads_.size() + 1);
        for (size_t i = 0; i < threads_.size(); ++i)
        {
            execute([begin, step, &function, &counter]
            {
                for (auto i = begin; i != begin + step; ++i)
                {
                    function(*i);
                }
                counter.fetch_add(1);
            });
            begin += step;
        }
        for (auto i = begin; i != end; ++i)
        {
            function(*i);
        }
        while (counter.load() < threads_.size()) {}
    };

public:
    static thread_local ThreadPool* thisThreadPool;
    
private:
    void thrFunc();

private:
    std::mutex locker_;
    std::condition_variable queueEmpty_;
    std::vector<std::thread> threads_;
    std::queue< std::function<void()> > queueOfTasks_;
    bool isEnd_;
};


#endif //THREADPOOL_H