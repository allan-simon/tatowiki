#include <iostream>
#include "models/Articles.h"
#include "test.h"

#define TEST_NAME "models_articles_articles"

#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"
#define SQL_TABLE_STRUCTURE_CHECK "../tests/models/articles/table_structure_check.sql"

int main () {

    bool noTestFailed = true;
    models::SqliteModel articlesModels(TEST_NAME ".db");

    TEST_RESULT_SHOULD_WORK(
        "Try load the database ... " ,
        articlesModels.import_sql_file(DB_SQL_FILE_PATH),
        noTestFailed
    );
    /*
    TEST_RESULT_SHOULD_WORK(
        "Check articles table fields all there ... " ,
        articlesModels.import_sql_file(SQL_TABLE_STRUCTURE_CHECK),
        noTestFailed
    );
    */

    if (noTestFailed) {
        return 0;
    } else {
        return 1;
    } 
    

}
