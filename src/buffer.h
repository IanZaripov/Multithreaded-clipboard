#pragma once
#include <mutex>
#include <condition_variable>
#include <string>
#include <atomic>

class ThreadSafeBuffer {
public:
	void SetBuffer(std::string& buffer);
	std::string GetBuffer() const;
	void WaitForChanges();
	void Notify();
	void StopProcess();
	bool IsProcessStoped() const;
private:
	mutable std::mutex mx_;
	std::string buffer_;
	std::condition_variable cv_;
	std::atomic<bool>changes;
	bool stop{ false };
};