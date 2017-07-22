#include <iostream>
#include "ankidb.hpp"

int main(){
	std::string filename = "collection.anki2";
	Ankidb db(filename);

	std::cout << "Card number: " << db.get_card_count() << std::endl;

	std::cout << "Decks: " << std::endl;

	std::vector<Deck> decks = db.getDecks();

	for(Deck d: decks){
		std::cout << d.get_ID() << ": " << d.get_name() << ": ";
		std::cout << d.get_card_count() << " cards" << std::endl;
	}

	std::vector<StatPoint> stats = decks[1].get_review_stats(24*60*60);

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
