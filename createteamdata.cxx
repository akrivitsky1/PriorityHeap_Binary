#include <cstdio>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "json.hpp"

int main(int argc, char** argv) { // if argc is not two, wrong command line inputs
	if (argc != 2) {
		printf("Usage: %s numPlayers\n", argv[0]);
		return EXIT_FAILURE; //end code
	}
	unsigned int numPlayers = 0;
	if (sscanf(argv[1], "%u", &numPlayers) != 1) { //reading command line arg 1 to numplayers
		printf("numPlayers must be a positive integer\n");
		return EXIT_FAILURE; //not positive integer, cancel the code
	}

	std::random_device rd; //random generator 
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<int> winDist(0, 100000); //generates number between 0 and 100

	nlohmann::json players; //nlohmann  object
	players["metadata"]["numPlayers"] = numPlayers; //setting players from json file to numplayers
	std::set<double> seenWinPercentages; //a new set of double objects
	for (unsigned int player = 0; player < numPlayers; player++) { //for loop going through players
		for (unsigned int partner = player + 1; partner < numPlayers; partner++) { //going through partners
			nlohmann::json playerObj; // new json object
			double winPercentage = (double) winDist(rng) / 1000; //randomly generated win percentage
			while (seenWinPercentages.count(fabs(winPercentage - 50)) > 0) { //counting it
				winPercentage = (double) winDist(rng) / 10;
			}
			seenWinPercentages.insert(fabs(winPercentage - 50)); //insert it into the object
			playerObj["winPercentage"] = winPercentage; //insert into the object
			playerObj["playerOne"] = player; //insert player 1 into object
			playerObj["playerTwo"] = partner; //insert partner into object
			players["teamStats"].push_back(playerObj); //push back the stats for playerObj
		}
	}
	std::cout << players.dump(2); //dump players object
}