#ifndef DECK_HPP
#define DECK_HPP

#include <string>

class Deck{
public:
	Deck(std::string name, long long id): name(name), id(id) {  }
	std::string getName() { return name; };
	long long getID() { return id; };

private:
	std::string name;
	long long id;
};

#endif
