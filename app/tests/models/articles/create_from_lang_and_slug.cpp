#include <iostream>
#include "models/Articles.h"

#define TEST_NAME "models_create_from_lang_and_slug_test"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"


int main() {

    models::Articles articlesModels(TEST_NAME ".db");
    int result = articlesModels.import_sql_file(DB_SQL_FILE_PATH);

}
