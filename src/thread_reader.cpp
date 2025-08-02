#include "thread_reader.h"

using namespace std;

ThreadReader::ThreadReader(ThreadSafeBuffer& buffer,mutex& cout_mutex) : buffer_(buffer) , cout_mutex_(cout_mutex){
	thread_reader_ = thread(&ThreadReader::ProccesReadning, this);
}

ThreadReader::~ThreadReader() {
	if (thread_reader_.joinable()) {
		thread_reader_.join();
	}
}

void ThreadReader::ProccesReadning() {
	while (true) {
		buffer_.WaitForChanges();
		if (buffer_.IsProcessStoped()) {
			break;
		}
		std::lock_guard<std::mutex> lock(cout_mutex_);
		ReadBufferStats();
	}
}

tuple<SymbolsStats, SymbolsStats> ThreadReader::CountElementsOnOddEvenPos(const std::string& buffer) const {
	std::unordered_map<char, int> even;
	std::unordered_map<char, int> odd;
	for (int i = 0; i < buffer.size(); i++) {
		if (i % 2 == 0) {
			even[buffer[i]]++;
		}
		else {
			odd[buffer[i]]++;
		}
	}
	return { even,odd };
}


void ThreadReader::ReadBufferStats() const{
	const string cur_buffer = buffer_.GetBuffer();
	cout << "Current buffer: " <<  cur_buffer << "\n";
	const auto [even,odd] = CountElementsOnOddEvenPos(cur_buffer);
	cout << "Even position count: \n";
	for (const auto [symbol, cnt] : even) {
		cout << symbol << " " << cnt << "\n";
	}
	if (even.empty()) {
		cout << "0\n";
	}
	cout << "Odd position count: \n";
	for (const auto [symbol, cnt] : odd) {
		cout << symbol << " " << cnt << "\n";
	}
	if (odd.empty()) {
		cout << "0\n";
	}
}