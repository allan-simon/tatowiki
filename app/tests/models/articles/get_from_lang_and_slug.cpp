#include <iostream>
#include "models/Articles.h"
#include <cppcms_skel/generics/test.h>

#define CPPCMSSKEL_TEST_NAME "models_get_from_lang_and_slug_test"
#define SQL_FILL_ARTICLES "../tests/models/articles/fill_articles.sql"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"


int main() {


    bool noTestFailed = true;
    models::Articles articlesModels(CPPCMSSKEL_TEST_NAME ".db");

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
 
    
    // now we check if we can retrieve them

    std::cout << "We now test get_from_lang_slug itself ... ";
    results::Article firstArticle = articlesModels.get_from_lang_and_slug(
        "fr",
        "page_principale"
    );
    if (!firstArticle.exists()) {

        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }

    //
    std::cout << "the article we get should be the same than the one we've inserted ... " << std::endl;
    std::cout << "the lang should be the same than the one we've inserted ... ";
    if (firstArticle.lang.compare("fr") != 0) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    } else {
        std::cout << " [ok]" << std::endl; 
    }

    // 
    std::cout << "the lang should be the same than the one we've inserted ... ";
    if (firstArticle.slug.compare("page_principale") != 0) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    } else {
        std::cout << " [ok]" << std::endl; 
    }

    //
    std::cout << "The title should be the same than the one we've inserted ... ";
    if(firstArticle.title.compare("Page Principale") != 0) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    } else {
        std::cout << " [ok]" << std::endl; 
    }

    //
    std::cout << "The content should be the same than the one we've inserted ... ";
    if(firstArticle.content.compare(u8"Juste pour voir si ça marche") != 0){
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
