#include <iostream>
#include "ankidb.hpp"

int main(){
	std::string filename = "collection.anki2";
	Ankidb db(filename);

	std::cout << "Card number: " << db.get_card_count() << std::endl;

	std::cout << "Decks: " << std::endl;

	for(Deck d: db.getDecks()){
		std::cout << d.getID() << ": " << d.getName() << ": ";
		std::cout << db.get_deck_card_count(d.getID()) << " cards" << std::endl;
	}

	return 0;
}
