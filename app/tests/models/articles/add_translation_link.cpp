#include <iostream>
#include "models/Articles.h"
#include "test.h"

#define TEST_NAME "models_articles_add_translation_link_test"


#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"
#define SQL_FILL_ARTICLES "../tests/models/articles/fill_articles.sql"

#define TEST_ARTICLE_LANG_FRENCH "fr"
#define TEST_ARTICLE_LANG_GERMAN "de"
#define TEST_ARTICLE_LANG_ENGLISH "en"

#define TEST_ARTICLE_SLUG_FRENCH "page_principale"
#define TEST_ARTICLE_SLUG_GERMAN "main_page_de"
#define TEST_ARTICLE_SLUG_ENGLISH "main_page"

int main () {

    bool noTestFailed = true;

    models::Articles articlesModels(TEST_NAME ".db");

    TEST_RESULT_SHOULD_WORK(
        "Try load the database ... " ,
        articlesModels.import_sql_file(DB_SQL_FILE_PATH),
        noTestFailed
    );
    
    // we first load some raw articles on the database
    TEST_RESULT_SHOULD_WORK(
        "Try to load the database with some data ... " ,
        articlesModels.import_sql_file(SQL_FILL_ARTICLES),
        noTestFailed
    );
    
    
    if (noTestFailed) {
        return 0;
    } else {
        return 1;
    }
}
