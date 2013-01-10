#include <iostream>
#include "models/Articles.h"
#include "test.h"

#define TEST_NAME "models_articles_articles"

#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"

int main () {


    models::Articles articlesModels(TEST_NAME ".db");

    std::cout << "Try load the database ... " ;
    int result = articlesModels.import_sql_file(DB_SQL_FILE_PATH);
    TEST_RESULT_SHOULD_WORK();

    return 0;
}
