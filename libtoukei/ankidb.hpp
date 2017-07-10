#ifndef ANKIDB_HPP_
#define ANKIDB_HPP_

#include <iostream>
#include <sqlite3.h>

#include <vector>

#include "deck.hpp"

struct StatPoint{
	int time;

	int learn;
	int young;
	int mature;
	int lapse;
	int cram;

	int learn_time;
	int young_time;
	int mature_time;
	int lapse_time;
	int cram_time;

	int new_learned;
};

class Ankidb{
public:
	Ankidb(const std::string &filename);
	~Ankidb();

	int get_card_count(const std::string &lmt = "1=1");
	int get_deck_card_count(long long id);
	std::vector<Deck> getDecks();

	std::vector<StatPoint> get_review_stats(unsigned chunk,
			const std::string &lmt = "1=1",
			bool fill = "true");

private:
	sqlite3 *db;
};

#endif
