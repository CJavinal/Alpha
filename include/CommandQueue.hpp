#ifndef CommandQueue_HPP_INCLUDED
#define CommandQueue_HPP_INCLUDED
#include "Command.hpp"
#include <queue>

class CommandQueue {
	public:
		void					push(const Command& command);
		Command					pop();
		bool					isEmpty() const;

	private:
		std::queue<Command>		mQueue;
};

#endif // CommandQueue_HPP_INCLUDED
