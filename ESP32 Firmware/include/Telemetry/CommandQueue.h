#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include <stdexcept>
#include "Command.h"

class CommandQueue {
public:
	// Construct a new Command Queue object
	CommandQueue(size_t max_size = 100);

	// Adds a new command to the queue. If the queue is full, removes the oldest command.
	void addCommand(const Command& cmd);

	// Attempts to get the next command. If the queue is empty, returns false.
	bool tryGetCommand(Command& cmd);

	// Gets the next command. If the queue is empty, blocks until a command is available.
	// Command getCommand(); - Consequences of careless use can cause serious consequences

	// Returns the number of commands in the queue.
	size_t length();

	// Returns true if there is at least one command in the queue, false otherwise.
	bool isAvailableCommand();

	// Clears all commands from the queue.
	void clear();

private:
	std::deque<Command> commandQueue;
	std::mutex mtx;
	std::condition_variable cv;
	size_t maxSize;
};

#endif // COMMANDQUEUE_H
