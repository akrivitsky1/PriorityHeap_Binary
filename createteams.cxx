#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "priorityqueue.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json; //using json nlohmann

typedef std::pair<int, int> Pair; //create a pair

int main(int argc, char* argv[]) { //input file
 if (argc < 2) {
    std::cerr << "Please provide an input file." << std::endl; //error if argc less than 2
    return 1;
  }
  // Load the input JSON data from the input file
json data; // json object
std::ifstream inputFile(argv[1]);//new input file
inputFile >> data; //object has json file
inputFile.close();
// Extract the number of players and team statistics
int num_players = data["metadata"]["numPlayers"];
std::vector<json> team_stats = data["teamStats"];

// Create the priority queue
int num_teams = num_players*(num_players-1)/2;
PriorityQueue pq(num_teams); //creates priority queue
for (const auto& team : team_stats) {
    int player1 = team["playerOne"]; //player one is set to player1
    int player2 = team["playerTwo"]; //player two is set to player2
    double win_percentage = team["winPercentage"]; 
    // Store the team statistics as a key-value pair in the priority queue,
    // where the key is the difference between the win percentage and 50%
    // and the value is the pair of players
    pq.insert(std::make_pair(std::abs(win_percentage - 50.0), Pair(player1, player2)));
}

// The final teams
std::vector<Pair> teams;

// The players who have already been assigned to a team
std::vector<int> assigned_players;

// Repeat the greedy algorithm until all players have been assigned to a team
while (static_cast<int>(teams.size()) < num_players / 2) {
    // Select the team with the win percentage closest to 50%
    auto min = pq.removeMin();
    Pair team = min.second;
    // Check if either player in the team has already been assigned to a team
    int player1 = team.first; //int player 1 is team 1
    int player2 = team.second; //int player 2 is team 3
    if (std::find(assigned_players.begin(), assigned_players.end(), player1) == assigned_players.end() &&
        std::find(assigned_players.begin(), assigned_players.end(), player2) == assigned_players.end()) {
        // Add the team to the final teams
        teams.push_back(team);
        // Add both players to the assigned players
        assigned_players.push_back(player1);
        assigned_players.push_back(player2);
    }
}
// Convert the final teams to a JSON object and print it
json output;
output["teams"] = json::array(); // putting it into an array
for (const auto& team : teams) {
    output["teams"].push_back({team.first, team.second}); //adds it to an array
}
std::cout << (output.dump(2)) << std::endl;
// Output the result to the terminal as well

return 0;
}