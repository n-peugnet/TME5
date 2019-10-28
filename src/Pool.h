#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) :
			queue((size_t) qsize) {
	}
	void start(int nbthread) {
		queue.setBlocking(true);
		threads.reserve(nbthread);
		for (int i = 0; i < nbthread; ++i) {
//			std::thread t(poolWorker, std::ref(queue));
//			t.join();
			threads.emplace_back(poolWorker, std::ref(queue));
		}
	}
	void submit(Job *job) {
		queue.push(job);

	}
	void stop() {
		queue.setBlocking(false);
		for (std::thread & t : threads) {
			t.join();
		}
	}
	void static poolWorker(Queue<Job> &queue) {
		while (true) {
			Job *job = queue.pop();
			if (job == nullptr) {
				break;
			}
			job->run();
			delete job;
		}
	}
	~Pool() {
		stop();
		threads.clear();
	}
};

}
