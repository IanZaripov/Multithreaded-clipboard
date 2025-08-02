#pragma once
#include "buffer.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <string>
#include <mutex>

class ThreadWriter {
public:
	ThreadWriter(ThreadSafeBuffer& buffer, std::mutex& cout_mutex);
	~ThreadWriter();
	void SortInAscendingOrder();
	void SortInDescendingOrder();
	void Add(char ch);
	void Erase();
	void Reverse();
	void ProcessingCommand();
private:
	std::thread thread_writer_;
	std::mutex& cout_mutex_;
	ThreadSafeBuffer& buffer_;
	std::atomic<bool> changes;
};