#include "buffer.h"

using namespace std;

void ThreadSafeBuffer::WaitForChanges() {
	std::unique_lock<mutex> ulock(mx_);
	cv_.wait(ulock, [this]() {
		return changes.load() || stop; 
		});
	if (stop) {
		return;
	}
	changes = false;
}

void ThreadSafeBuffer::StopProcess() {
	lock_guard<mutex>lg(mx_);
	stop = true;
	cv_.notify_one();
}

bool ThreadSafeBuffer::IsProcessStoped() const{
	lock_guard<mutex> lg(mx_);
	return stop;
}

void ThreadSafeBuffer::SetBuffer(string& buffer) {
	lock_guard<mutex> lg(mx_);
	buffer_ = move(buffer);
}

void ThreadSafeBuffer::Notify() {
	changes = true;
	cv_.notify_one();
}

string ThreadSafeBuffer::GetBuffer() const{
	lock_guard<mutex> lg(mx_);
	return buffer_;
}
