#include "thread_writer.h"
#include "thread_reader.h"
#include "buffer.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


int main(){
	ThreadSafeBuffer buffer;
	mutex cout_mutex;
	ThreadWriter writer(buffer,cout_mutex);
	ThreadReader reader(buffer,cout_mutex);
	while (!buffer.IsProcessStoped()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
    return 0;
}
