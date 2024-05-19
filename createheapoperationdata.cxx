#include <cstdio>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "json.hpp"

typedef unsigned int 	Key;

Key createKey(std::mt19937_64& rng, std::set<Key>& pqueueContents);

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Usage: %s numOperations maxHeapSize\n", argv[0]);
		return EXIT_FAILURE;
	}
	unsigned int numOperations = 0, maxHeapSize = 0;
	if (sscanf(argv[1], "%u", &numOperations) != 1 || sscanf(argv[2], "%u", &maxHeapSize) != 1) {
		printf("numOperations and maxHeapSize must be positive integers\n");
		return EXIT_FAILURE;
	}

	nlohmann::json samples;
	std::set<Key> pqueueContents;
	size_t initialInserts = std::min(maxHeapSize, numOperations) / 2;
	size_t minHeapSize = 1 + maxHeapSize / 4;
	samples["metadata"]["numOperations"] = numOperations;
	samples["metadata"]["maxHeapSize"] = maxHeapSize;

	std::random_device rd;
	std::mt19937_64 rng(rd());

	// Create distributions
	enum class HeapOperation { insert, removeMin };
	std::uniform_int_distribution<int> opDist(0, 1);

	unsigned int totalZeros = (int) floor(log10((double) numOperations)) + 1;
	for (unsigned int op = 1; op <= numOperations; op++) {
		int opZeros =  (int) floor(log10((double) op)) + 1;
		std::string opNum = std::string(totalZeros - opZeros, '0').append(std::to_string(op));
		nlohmann::json newOp;
		// Add random integer to array
		HeapOperation operation =
			((op < initialInserts) ? HeapOperation::insert : (HeapOperation) opDist(rng));
		switch (operation) {
			case HeapOperation::insert:
				if (pqueueContents.size() < maxHeapSize) {
					newOp["operation"] = "insert";
					Key key = createKey(rng, pqueueContents);
					newOp["key"] = key;
					pqueueContents.insert(key);
					break;
				}
			case HeapOperation::removeMin:
				if (pqueueContents.size() > minHeapSize) {
					newOp["operation"] = "removeMin";
					pqueueContents.erase(pqueueContents.begin());
					break;
				}
			default:
				op--;
				continue;
		}
		samples["Op" + opNum] = newOp;
	}
	std::cout << samples.dump(2) << std::endl;
	return EXIT_SUCCESS;
}

Key createKey(std::mt19937_64& rng, std::set<Key>& pqueueContents) {
	std::uniform_int_distribution<Key> keyDist(0, 5000);
	while (true) {
		Key key = keyDist(rng);
		if (pqueueContents.count(key) == 0) {
			return key;
		}
	}
}