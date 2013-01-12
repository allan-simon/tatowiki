#include <iostream>
#include "models/Articles.h"
#include "test.h"

#define TEST_NAME "models_create_from_lang_and_slug_test"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"


int main() {


    bool noTestFailed = true;
    models::Articles articlesModels(TEST_NAME ".db");

    TEST_RESULT_SHOULD_WORK(
        "Try load the database ... " ,
        articlesModels.import_sql_file(DB_SQL_FILE_PATH),
        noTestFailed
    );
    
    // we should be able to add an article ...
    TEST_RESULT_SHOULD_WORK(
        "Try to add an article ... " ,
        articlesModels.import_sql_file(DB_SQL_FILE_PATH),
        noTestFailed
    );
    





}
