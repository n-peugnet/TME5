/*
 * Barrier.h
 *
 *  Created on: 23 oct. 2019
 *      Author: 3872867
 */

#pragma once

#include <mutex>
#include <condition_variable>

namespace pr {

class Barrier {
	int counter;
	const int MAX;
	std::mutex m;
	std::condition_variable cv;
public:
	Barrier(int max): counter(0), MAX(max) {
	}
	void done() {
		std::unique_lock<std::mutex> l(m);
		counter++;
		if (counter == MAX) {
			cv.notify_all();
		}
	}
	void waitFor()
	{
		std::unique_lock<std::mutex> l(m);
		while(counter != MAX) {
			cv.wait(l);
		}
	}

private:
};

}  // namespace pr



