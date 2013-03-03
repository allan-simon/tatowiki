#include <iostream>
#include "models/Articles.h"
#include "test.h"

#define TEST_NAME "models_articles_add_to_group_test"


#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"
#define SQL_FILL_ARTICLES "../tests/models/articles/fill_articles.sql"




#define TEST_ARTICLE_LANG_FRENCH "fr"
#define TEST_ARTICLE_LANG_GERMAN "de"
#define TEST_ARTICLE_LANG_CHINESE "zh"
#define TEST_ARTICLE_LANG_POLISH "pl"
#define TEST_ARTICLE_LANG_ENGLISH "en"

#define TEST_ARTICLE_SLUG_FRENCH "page_principale"
#define TEST_ARTICLE_SLUG_GERMAN "main_page_de"
#define TEST_ARTICLE_SLUG_CHINESE "main_page_zh"
#define TEST_ARTICLE_SLUG_POLISH "main_page_pl"
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
    
    int zhId = articlesModels.get_id_from_lang_and_slug(
        TEST_ARTICLE_LANG_CHINESE,
        TEST_ARTICLE_SLUG_CHINESE
    );
        
    int plId = articlesModels.get_id_from_lang_and_slug(
        TEST_ARTICLE_LANG_POLISH,
        TEST_ARTICLE_SLUG_POLISH
    );



    std::cout << "Try add a link between two articles with no links"
        << " to other articles, so it should add only one link ... ";

    int result = articlesModels.add_to_group(
        frId,
        deId
    );
    if (result == ARTICLE_ADD_TRANSLATION_LINK_ERROR) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }

    // we try to add a link between A and B 
    // with A already linked to C 
    std::cout << "Try add a link between two articles that already have some links ... ";

    result = articlesModels.add_to_group (
        frId,
        enId
    );

    if (result == ARTICLE_ADD_TRANSLATION_LINK_ERROR) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }
    //  
    result = articlesModels.add_to_group(
        frId,
        plId
    );

    if (result == ARTICLE_ADD_TRANSLATION_LINK_ERROR) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }
    //  
    result = articlesModels.add_to_group(
        frId,
        zhId
    );

    if (result == ARTICLE_ADD_TRANSLATION_LINK_ERROR) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }





    // We want that if A and B are linked, that if we link B and C, that
    // automatically A is linked to C
    std::cout << "Test if all articles at the end are interlinked ... ";
    if (
        
        articlesModels.group_contains_lang(frId, TEST_ARTICLE_LANG_FRENCH) &&
        articlesModels.group_contains_lang(frId, TEST_ARTICLE_LANG_ENGLISH) &&
        articlesModels.group_contains_lang(frId, TEST_ARTICLE_LANG_GERMAN) &&
        articlesModels.group_contains_lang(frId, TEST_ARTICLE_LANG_CHINESE) &&
        articlesModels.group_contains_lang(frId, TEST_ARTICLE_LANG_POLISH) 
    ) {
    
        std::cout << " [ok]" << std::endl; 

    } else {

        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    }



    
    if (noTestFailed) {
        return 0;
    } else {
        return 1;
    }
}
