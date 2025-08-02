#include "thread_writer.h"

using namespace std;

ThreadWriter::ThreadWriter(ThreadSafeBuffer& buffer, mutex& cout_mutex) : buffer_(buffer), cout_mutex_(cout_mutex){
	thread_writer_ = thread(&ThreadWriter::ProcessingCommand, this);
}

ThreadWriter::~ThreadWriter() {
	if (thread_writer_.joinable()) {
		thread_writer_.join();
	}
}

void ThreadWriter::ProcessingCommand() {
    while (!buffer_.IsProcessStoped()) {
        {
            lock_guard<mutex> lg(cout_mutex_);
            cout << "Write command (add/erase/sort_asc/sort_desc/reverse/exit):";
        }
        string command;
        cin >> command;
        if (command == "exit") {
            buffer_.StopProcess();
            break;
        }
        else if (command == "add") {
            char ch;
            if (cin >> ch) {
                Add(ch);
            }
        }
        else if (command == "erase") {
            Erase();
        }
        else if (command == "sort_asc") {
            SortInAscendingOrder();
        }
        else if (command == "sort_desc") {
            SortInDescendingOrder();
        }
        else if (command == "reverse") {
            Reverse();
        }
        else {
            cout << "Unknown command!\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очистка буфера
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void ThreadWriter::SortInAscendingOrder() {
	auto buffer = buffer_.GetBuffer();
	sort(buffer.begin(), buffer.end());
	buffer_.SetBuffer(buffer);
	buffer_.Notify();
}
void ThreadWriter::SortInDescendingOrder() {
	auto buffer = buffer_.GetBuffer();
	sort(buffer.rbegin(), buffer.rend());
	buffer_.SetBuffer(buffer);
	buffer_.Notify();
}

void ThreadWriter::Add(char ch) {
	auto buffer = buffer_.GetBuffer();
	buffer.push_back(ch);
	buffer_.SetBuffer(buffer);
	buffer_.Notify();
}

void ThreadWriter::Erase() {
	auto buffer = buffer_.GetBuffer();
	if (!buffer.empty()) {
		buffer.pop_back();
		buffer_.SetBuffer(buffer);
		buffer_.Notify();
	}
}

void ThreadWriter::Reverse() {
	auto buffer = buffer_.GetBuffer();
	reverse(buffer.begin(), buffer.end());
	buffer_.SetBuffer(buffer);
	buffer_.Notify();
}
