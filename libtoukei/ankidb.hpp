#ifndef ANKIDB_HPP_
#define ANKIDB_HPP_

#include <iostream>
#include <sqlite3.h>

#include <vector>

#include "deck.hpp"

class Ankidb{
public:
	Ankidb(const std::string &filename);
	~Ankidb();

	int get_card_count(const std::string &lmt = "1=1");
	int get_deck_card_count(long long id);
	std::vector<Deck> getDecks();

private:
	sqlite3 *db;
};

#endif
