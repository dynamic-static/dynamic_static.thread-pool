
/*
==========================================
  Copyright (c) 2016-2022 dynamic_static
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/thread-pool.hpp"
#include "dynamic_static/time.hpp"

#include "catch2/catch.hpp"

#include <future>
#include <string>
#include <vector>

namespace dst {
namespace tests {

static constexpr int TestCount { 256 };

static std::string make_word(size_t index)
{
    static const std::vector<std::string> sWords {
        "the",
        "quick",
        "brown",
        "fox",
    };
    return sWords[index % sWords.size()] + "[" + std::to_string(index) + "]";
}

/**
Validates that wait() doesn't dead lock when there are no tasks
*/
TEST_CASE("ThreadPool::wait()", "[ThreadPool]")
{
    ThreadPool threadPool;
    threadPool.wait();
}

/**
Validates that a single task can be pushed and executed
*/
TEST_CASE("ThreadPool::push() (single task)", "[ThreadPool]")
{
    ThreadPool threadPool;
    bool taskComplete = false;
    auto future = threadPool.push(
        [&]()
        {
            std::this_thread::sleep_for(Seconds<> { 0.25 });
            taskComplete = true;
        }
    );
    SECTION("future.wait()")
    {
        future.wait();
        CHECK(taskComplete);
    }
    SECTION("threadPool.wait()")
    {
        threadPool.wait();
        CHECK(taskComplete);
    }
}

/**
Validates that multiple tasks can be pushed and executed
*/
TEST_CASE("ThreadPool::push() (multiple tasks)", "[ThreadPool]")
{
    ThreadPool threadPool;
    std::vector<std::string> taskResults(TestCount);
    std::vector<std::future<void>> futures(TestCount);
    threadPool.push([]() { std::this_thread::sleep_for(Seconds<> { 0.25 }); });
    for (size_t i = 0; i < TestCount; ++i) {
        auto future = threadPool.push(
            [i, &taskResults]()
            {
                taskResults[i] = make_word(i);
            }
        );
        futures[i] = std::move(future);
    }
    SECTION("future.wait()")
    {
        for (size_t i = 0; i < TestCount; ++i) {
            futures[i].wait();
            if (taskResults[i] != make_word(i)) {
                FAIL();
            }
        }
    }
    SECTION("threadPool.wait()")
    {
        threadPool.wait();
        for (size_t i = 0; i < TestCount; ++i) {
            if (taskResults[i] != make_word(i)) {
                FAIL();
            }
        }
    }
}

/**
Validates that ThreadPool completes pending tasks on destruction
*/
TEST_CASE("ThreadPool::~ThreadPool()", "[ThreadPool]")
{
    std::vector<std::string> taskResults(TestCount);
    std::vector<std::future<void>> futures(TestCount);
    {
        ThreadPool threadPool;
        threadPool.push([]() { std::this_thread::sleep_for(Seconds<> { 0.25 }); });
        for (size_t i = 0; i < TestCount; ++i) {
            auto future = threadPool.push(
                [i, &taskResults]()
                {
                    taskResults[i] = make_word(i);
                }
            );
            futures[i] = std::move(future);
        }
    }
    SECTION("future.wait()")
    {
        for (size_t i = 0; i < TestCount; ++i) {
            futures[i].wait();
            if (taskResults[i] != make_word(i)) {
                FAIL();
            }
        }
    }
    SECTION("ThreadPool::~ThreadPool()")
    {
        for (size_t i = 0; i < TestCount; ++i) {
            if (taskResults[i] != make_word(i)) {
                FAIL();
            }
        }
    }
}

} // namespace tests
} // namespace dst
