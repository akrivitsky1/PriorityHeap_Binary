#include "teamdata.h"
#include <fstream>
#include <vector>
#include "json.hpp"

TeamData::TeamData(std::string filename) {
	std::ifstream file(filename);
	nlohmann::json j;
	file >> j;
	numPlayers_ = j["metadata"]["numPlayers"];
	std::vector<std::vector<double>> winPercentages_(numPlayers_, std::vector<double>(numPlayers_, 0));
	for (const auto& teamStat : j["teamStats"]) {
		int playerOne = teamStat["playerOne"];
		int playerTwo = teamStat["playerTwo"];
		double winPercentage = teamStat["winPercentage"];
		winPercentages_[playerOne][playerTwo] = winPercentage;
		winPercentages_[playerTwo][playerOne] = 100 - winPercentage;
	}
}

int TeamData::numPlayers() const {
	return numPlayers_;
}
