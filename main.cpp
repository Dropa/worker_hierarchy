#include <iostream>
#include <vector>
#include "json.hpp" // see https://github.com/nlohmann/json
#include <fstream>
#include <map>
#include "composite.h"
#include "leaf.h"
#include <string>

#define RETRY_MAX 10
#define READ_JSON_FILE "workers.json"
#define MAXIMUM_EMPLOYEES 100

using std::cout;
using std::endl;
using std::vector;
using nlohmann::json;
using std::string;
using std::map;
using std::pair;
using std::ifstream;

int main() {
	// Get the list of workers.
	json people;
	map <string, int> peoplemap;
	ifstream people_file(READ_JSON_FILE, ifstream::binary);
	people_file >> people;

	bool rerun;
	auto retry = 0;

	composite workers[MAXIMUM_EMPLOYEES];
	auto i = 0;
	do {
		rerun = false;
		for (auto it = people.begin(); it != people.end();) {
			// Parse worker.
			const auto supervisor = it.value()["supervisor"];
			const auto first = it.value()["first"];
			const auto last = it.value()["last"];
			const auto role = it.value()["role"];

			// There should be only one worker who has no supervisor.
			if (supervisor == nullptr) {
				workers[i].add(new leaf(first, last, role));
			}
			else {
				// Not superboss, processing needed.
				const auto supervisor_exists = peoplemap.find(supervisor);
				// Check whether supervisor of current worker has been found yet.
				if (supervisor_exists != peoplemap.end()) {
					const auto pos = supervisor_exists->second;
					workers[i].add(new leaf(first, last, role));
					workers[pos].add(&(workers[i]));
				}
				else {
					// Supervisor has not been found yet, might be found after rerun.
					rerun = true;
					if (retry++ >= RETRY_MAX) {
						cout << "Did not found supervisor for all employees. Exiting." << endl;
						getchar();
						return 1;
					}
					// Manual iterator increasing as we are not deleting current user.
					++it;
					continue;
				}
			}
			// This person has been fully processed, remove from people vector
			// to make possible rerun faster.
			peoplemap.insert(pair<string, int>(it.key(), i++));
			it = people.erase(it);
		}
	} while (rerun);

	// First row in workers contains full hierarchy starting from the superboss.
	// The array contains all workers, so it is possible to check hiearchy
	// starting from any worker.
	workers[0].traverse(0);

	// Remove the getchar() if you do not want to pause before exit.
	getchar();
	return 0;
}