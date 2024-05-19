#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_
#include <vector>
#include <string>

class TeamData {
 public:
 	TeamData(std::string filename);
 	int numPlayers() const;
 	double winPercentages(int i, int j) const { return winPercentages_[i][j]; }

 private:
	std::vector<std::vector<double>> winPercentages_;

	int numPlayers_;

};  // class TeamData

#endif  // _TEAMDATA_H_