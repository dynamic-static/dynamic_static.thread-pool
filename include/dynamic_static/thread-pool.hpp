
/*
==========================================
  Copyright (c) 2015-2022 dynamic_static
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

namespace dst {

/**
Provides high level control over a collection of threads
*/
class ThreadPool final
{
public:
    /**
    Constructs an instance of ThreadPool
    @param [in] count (optional = std::thread::hardware_concurrency()) This ThreadPool object's number of threads
        @note If count is 0 std::thread::hardware_concurrency() will be used
    */
    inline ThreadPool(size_t count = std::thread::hardware_concurrency())
    {
        count = count ? count : std::thread::hardware_concurrency();
        mThreads.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            mThreads.emplace_back(
                [&]()
                {
                    while (mActive) {
                        std::unique_lock<std::mutex> lock(mMutex);
                        mTaskReceived.wait(lock, [&]() { return !mTasks.empty() || !mActive; });
                        lock.unlock();
                        ++mActiveThreadCount;
                        for (auto task = std::move(get_task()); task.valid(); task = std::move(get_task())) {
                            task();
                        }
                        if (!--mActiveThreadCount) {
                            mTasksComplete.notify_all();
                        }
                    }
                }
            );
        }
    }

    /**
    Destroys this instance of ThreadPool
    */
    inline ~ThreadPool()
    {
        mActive = false;
        mTaskReceived.notify_all();
        for (auto& thread : mThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    /**
    Gets this ThreadPool object's number of threads
    */
    inline size_t get_thread_count() const
    {
        return mThreads.size();
    }

    /**
    Gets this ThreadPool object's number of threads currently processing tasks
        @note The value retuned by this method may be stale by the time it's read
    */
    inline size_t get_active_thread_count() const
    {
        return mActiveThreadCount;
    }

    /**
    Gets this ThreadPool object's number of pending tasks
        @note The value retuned by this method may be stale by the time it's read
    */
    inline size_t get_task_count() const
    {
        return mTasks.size();
    }

    /**
    Queues a task for processing on one of this ThreadPool object's threads
    @param <TaskType> The type of task to queue for processing
    @param [in] task The task to queue for processing
    @return A std::future<void()> that can be used for notification of completion of the given task
        @note TaskType must have a signature compatible with std::packaged_task<void()>
    */
    template <typename TaskType>
    inline std::future<void> push(TaskType task)
    {
        std::packaged_task<void()> packagedTask(std::move(task));
        auto future = packagedTask.get_future();
        mMutex.lock();
        mTasks.push(std::move(packagedTask));
        mMutex.unlock();
        mTaskReceived.notify_one();
        return future;
    }

    /**
    Clears this ThreadPool object's pending tasks
    */
    inline void clear()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        while (!mTasks.empty()) {
            auto task = std::move(mTasks.front());
            mTasks.pop();
        }
    }

    /**
    Suspends the calling thread until this ThreadPool has completed all pending tasks
    */
    inline void wait()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mTasksComplete.wait(lock, [&]() { return !mActiveThreadCount && mTasks.empty(); });
    }

private:
    std::packaged_task<void()> get_task()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        if (!mTasks.empty()) {
            auto task = std::move(mTasks.front());
            mTasks.pop();
            return task;
        }
        return { };
    }

    std::atomic_bool mActive { true };
    std::vector<std::thread> mThreads;
    std::atomic_size_t mActiveThreadCount { 0 };
    std::queue<std::packaged_task<void()>> mTasks;
    std::mutex mMutex;
    std::condition_variable mTaskReceived;
    std::condition_variable mTasksComplete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
};

} // namespace dst
