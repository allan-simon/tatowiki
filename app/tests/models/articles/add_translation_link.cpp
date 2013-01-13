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

    // now we try to add a link between the german article
    // and the french one
    
    // first we retrieve the id of the articles
    int frId = articlesModels.get_id_from_lang_and_slug(
        TEST_ARTICLE_LANG_FRENCH,
        TEST_ARTICLE_SLUG_FRENCH
    );

    int deId = articlesModels.get_id_from_lang_and_slug(
        TEST_ARTICLE_LANG_GERMAN,
        TEST_ARTICLE_SLUG_GERMAN
    );

    int enId = articlesModels.get_id_from_lang_and_slug(
        TEST_ARTICLE_LANG_ENGLISH,
        TEST_ARTICLE_SLUG_ENGLISH
    );

    std::cout << "Try add a link between two articles with no links"
        << " to other articles, so it should add only one link ... ";

    int result = articlesModels.add_translation_link(
        frId,
        deId
    );
    if (result == ARTICLE_ADD_TRANSLATION_LINK_ERROR) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }

    
    if (noTestFailed) {
        return 0;
    } else {
        return 1;
    }
}
