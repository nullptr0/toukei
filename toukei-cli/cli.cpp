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

	std::vector<StatPoint> stats = db.get_review_stats(24*60*60);

	for(const StatPoint &p: stats){
		std::cout << p.time << " ";
		std::cout << p.learn << " ";
		std::cout << p.young << " ";
		std::cout << p.mature << " ";
		std::cout << p.lapse << " ";
		std::cout << p.cram << " ";
		std::cout << std::endl;
	}

	return 0;
}
