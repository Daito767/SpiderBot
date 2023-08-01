#include "Telemetry/CommandQueue.h"

CommandQueue::CommandQueue(size_t max_size) : maxSize(max_size) {}

void CommandQueue::addCommand(const Command& cmd) {
	std::lock_guard<std::mutex> lock(mtx);

	if(commandQueue.size() >= maxSize) {
		commandQueue.pop_front();
	}

	commandQueue.push_back(cmd);
	// cv.notify_one();
}

bool CommandQueue::tryGetCommand(Command& cmd) {
	std::lock_guard<std::mutex> lock(mtx);

	if(!commandQueue.empty()) {
		cmd = commandQueue.front();
		commandQueue.pop_front();
		return true;
	}

	return false;
}

// Command CommandQueue::getCommand() {
// 	std::unique_lock<std::mutex> lock(mtx);
// 	cv.wait(lock, [this] { return !commandQueue.empty(); });

// 	Command cmd = commandQueue.front();
// 	commandQueue.pop_front();
// 	return cmd;
// }

size_t CommandQueue::length() {
	std::lock_guard<std::mutex> lock(mtx);
	return commandQueue.size();
}

bool CommandQueue::isAvailableCommand() {
	std::lock_guard<std::mutex> lock(mtx);
	return !commandQueue.empty();
}

void CommandQueue::clear() {
	std::lock_guard<std::mutex> lock(mtx);
	commandQueue.clear();
}
