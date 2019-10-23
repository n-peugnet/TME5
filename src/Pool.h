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
	Pool::Pool(int qsize) :
			queue((size_t) qsize) {
	}
	void Pool::start(int nbthread) {
		queue.setBlocking(true);
		threads.reserve(nbthread);
		for (int i = 0; i < nbthread; ++i) {
			threads.emplace_back(poolWorker, std::ref(queue));
		}
	}
	void Pool::submit(Job *job) {
		queue.push(job);

	}
	void Pool::stop() {
		queue.setBlocking(false);
		for (std::thread t : threads) {
			t.join();
		}
	}
	void Pool::poolWorker(Queue<Job> &queue) {
		while (true) {
			Job *job = queue.pop();
			if (job == nullptr) {
				break;
			}
			job->run();
			delete job;
		}
	}
	Pool::~Pool() {
		stop();
		threads.clear();
	}
};

}
