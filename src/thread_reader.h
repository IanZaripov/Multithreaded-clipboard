#pragma once
#include <iostream>
#include "buffer.h"
#include <string>
#include <mutex>
#include <thread>
#include <atomic>
#include <tuple>
#include <unordered_map>

using SymbolsStats = std::unordered_map<char, int>;

class ThreadReader {
public:
	ThreadReader(ThreadSafeBuffer& buffer,std::mutex& cout_mutex);
	~ThreadReader();
	void ProccesReadning();
	std::tuple<SymbolsStats, SymbolsStats> CountElementsOnOddEvenPos(const std::string& buffer) const;
	void ReadBufferStats() const;
private:
	ThreadSafeBuffer& buffer_;
	std::thread thread_reader_;
	std::mutex& cout_mutex_;
};