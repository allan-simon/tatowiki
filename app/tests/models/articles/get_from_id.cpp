#include <iostream>
#include "models/Articles.h"
#include <cppcms_skel/generics/test.h>

#define TEST_NAME "models_get_from_lang_and_slug_test"
#define SQL_FILL_ARTICLES "../tests/models/articles/fill_articles.sql"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"


int main() {


    bool noTestFailed = true;
    models::Articles articlesModels(TEST_NAME ".db");

    CPPCMSSKEL_TEST_RESULT_WORK(
        "Try load the database ... " ,
        articlesModels.import_sql_file(DB_SQL_FILE_PATH),
        noTestFailed
    );
    
    // we first load some raw articles on the database
    CPPCMSSKEL_TEST_RESULT_WORK(
        "Try to load the database with some data ... " ,
        articlesModels.import_sql_file(SQL_FILL_ARTICLES),
        noTestFailed
    );
    
    // load them again should not work as it will not met
    // the unique(lang,slug) constraint 
    CPPCMSSKEL_TEST_RESULT_NOT_WORK(
        "Load them again should not work ... " ,
        articlesModels.import_sql_file(SQL_FILL_ARTICLES),
        noTestFailed
    );
 
    
    // now we check if we can retrieve an article
    std::cout << "We try to get an article using get_from_lang_slug  ... ";
    results::Article firstArticle = articlesModels.get_from_lang_and_slug(
        "fr",
        "page_principale"
    );
    if ((!firstArticle.exists())) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    } else {
        std::cout << " [ok]" << std::endl; 
    }
    // now if we try to get an article with the id of the previous one
    // we should get (of course) the same one
    std::cout << "Using get_from_id to retrieve the same article ... ";
    results::Article secondArticle = articlesModels.get_from_id(
        firstArticle.id
    );
    if (
       !secondArticle.exists() ||
       secondArticle.id != firstArticle.id ||
       secondArticle.slug.compare(firstArticle.slug) != 0 ||
       secondArticle.lang.compare(firstArticle.lang) != 0
    ) {
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
