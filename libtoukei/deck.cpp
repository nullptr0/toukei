#include "deck.hpp"
#include "ankidb.hpp"


int Deck::get_card_count() { return db.get_deck_card_count(id); }

std::vector<StatPoint> Deck::get_review_stats(unsigned chunk,
		const std::string &lmt,
		bool fill)
{
	std::string limit = lmt + " and revlog.cid IN (SELECT id FROM cards WHERE did = ";
	limit += std::to_string(id) + ")";
	return db.get_review_stats(chunk, limit, fill);
}
