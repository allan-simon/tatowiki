#include <iostream>
#include "models/Articles.h"
#include "test.h"

#define TEST_NAME "models_create_from_lang_and_slug_test"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"

#define TEST_ARTICLE_ID  1
#define TEST_ARTICLE_LANG "fr"
#define TEST_ARTICLE_SLUG "page_principale"
#define TEST_ARTICLE_TITLE "Page Principale"
#define TEST_ARTICLE_CONTENT u8"Juste pour voir si ça marche"



int main() {


    bool noTestFailed = true;
    models::Articles articlesModels(TEST_NAME ".db");

    TEST_RESULT_SHOULD_WORK(
        "Try load the database ... " ,
        articlesModels.import_sql_file(DB_SQL_FILE_PATH),
        noTestFailed
    );
    
    // we should be able to add an article ...

    std::cout << "Try to add an article ... " ;

    int result = articlesModels.create_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG,
        TEST_ARTICLE_TITLE,
        TEST_ARTICLE_CONTENT
    );
    if (result == TEST_ARTICLE_ID) {
        std::cout << " [ok]" << std::endl;
    } else {
        std::cout << " [fail]" << std::endl;
        noTestFailed = false;
    }

    // try to add the same article should fail

    std::cout << "Adding the same article twice should be forbidden ... " ;

    result = articlesModels.create_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG,
        TEST_ARTICLE_TITLE,
        TEST_ARTICLE_CONTENT
    );
    if (result == ARTICLE_CREATION_ERROR) {
        std::cout << " [ok]" << std::endl;
    } else {
        std::cout << " [fail]" << std::endl;
        noTestFailed = false;
    }

    // try to retrieve the article we have added
    
    
    // now we check if we can retrieve them

    std::cout << "We now test if we can get it back ... ";
    results::Article firstArticle = articlesModels.get_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG
    );
    if ( 
        (firstArticle.id != TEST_ARTICLE_ID) ||
        (firstArticle.lang.compare(TEST_ARTICLE_LANG) != 0) ||
        (firstArticle.slug.compare(TEST_ARTICLE_SLUG) != 0) ||
        (firstArticle.title.compare(TEST_ARTICLE_TITLE) != 0) ||
        (firstArticle.content.compare(TEST_ARTICLE_CONTENT) != 0) ||
        (firstArticle.isLocked != false)
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
