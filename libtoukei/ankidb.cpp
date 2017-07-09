#include <jansson.h>
#include "ankidb.hpp"

Ankidb::Ankidb(const std::string &filename){
	char *err = nullptr;
	int ret;

	ret = sqlite3_open(filename.c_str(), &db);

	if(ret){
		std::cerr << "Can't open db: "
			<< sqlite3_errmsg(db) << std::endl;
	} else {
		std::cout << "Db opened\n";
	}
}

Ankidb::~Ankidb(){
	std::cout << "Closing db...\n";
	sqlite3_close(db);
}

int Ankidb::get_card_count(const std::string &lmt){
	int count = -1;
	int ret;

	sqlite3_stmt *s;

	std::string query = "SELECT count(id) FROM cards WHERE " + lmt;

	ret = sqlite3_prepare_v2(db,
			query.c_str(),
			-1,
			&s,
			NULL);

	ret = sqlite3_step(s);
	count = sqlite3_column_int(s, 0);

	sqlite3_finalize(s);

	return count;
}

int Ankidb::get_deck_card_count(long long id){
	return get_card_count("did = " + std::to_string(id));
}

std::vector<Deck> Ankidb::getDecks(){
	int ret;
	sqlite3_stmt *s;

	const char *json;
	std::vector<Deck> decks;

	ret = sqlite3_prepare_v2(db,
			"SELECT decks FROM col",
			-1,
			&s,
			NULL);
	ret = sqlite3_step(s);
	json = (const char *) sqlite3_column_text(s, 0);

	json_t *root;
	json_error_t error;

	root = json_loads(json, 0, &error);
	if(!root){
		std::cerr << "Error: " << error.text << std::endl;
	}

	const char *key;
	json_t *value;

	json_object_foreach(root, key, value){
		json_t *j_name = json_object_get(value, "name");
		json_t *j_id = json_object_get(value, "id");

		std::string name = json_string_value(j_name);
		unsigned long long id = json_integer_value(j_id);
		decks.emplace_back(name, id);
	}

	sqlite3_finalize(s);
	return decks;
}
