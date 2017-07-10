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

	json_decref(root);

	sqlite3_finalize(s);
	return decks;
}

std::vector<StatPoint> Ankidb::get_review_stats(unsigned chunk,
		const std::string &lmt,
		bool fill)
{
	std::vector<StatPoint> result;

	int ret;

	sqlite3_stmt *s;

	std::string query = "SELECT (id / 1000 - 7200) / "
		+ std::to_string(chunk) + " AS day, "
		"SUM(case when type = 0 then 1 else 0 end) AS lrn, "
		"SUM(case when type = 1 and lastIvl < 21 then 1 else 0 end) AS yng, "
		"SUM(case when type = 1 and lastIvl >= 21 then 1 else 0 end) AS mtr, "
		"SUM(case when type = 2 then 1 else 0 end) AS lapse, "
		"SUM(case when type = 3 then 1 else 0 end) AS cram "
		"FROM revlog "
		"WHERE " + lmt + " "
		"GROUP by day "
		"ORDER by day ";


	ret = sqlite3_prepare_v2(db,
			query.c_str(),
			-1,
			&s,
			NULL);

	int last_time = 0;

	while((ret = sqlite3_step(s)) == SQLITE_ROW){
		int time = sqlite3_column_int(s, 0);

		if(fill && last_time != 0 && time - last_time > 1){
			StatPoint p = {};
			p.time = last_time + 1;
			for(int i = 0; i < time - last_time - 1; i++){
				result.push_back(p);
				p.time++;
			}
		}

		StatPoint p = {};
		p.time = time;
		p.learn = sqlite3_column_int(s, 1);
		p.young = sqlite3_column_int(s, 2);
		p.mature = sqlite3_column_int(s, 3);
		p.lapse = sqlite3_column_int(s, 4);
		p.cram = sqlite3_column_int(s, 5);
		result.push_back(p);
		last_time = time;
	}

	sqlite3_finalize(s);
		
	return result;
}
