#ifndef DECK_HPP
#define DECK_HPP

#include <string>
#include <vector>

class Ankidb;
class StatPoint;

class Deck{
public:
	Deck(Ankidb &db, std::string name, long long id): db(db), name(name), id(id) {  }
	std::string get_name() { return name; };
	long long get_ID() { return id; };

	int get_card_count();
	std::vector<StatPoint> get_review_stats(unsigned chunk,
			const std::string &lmt = "1=1",
			bool fill = "true");

private:
	Ankidb &db;
	std::string name;
	long long id;
};

#endif
