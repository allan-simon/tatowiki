#include <iostream>
#include <cppcms_skel/generics/test.h>
#include "models/Articles.h"

#define CPPCMSSKEL_TEST_NAME "models_group_id_from_lang_and_slug_test"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"
#define SQL_FILL_ARTICLES "../tests/models/articles/fill_articles.sql"

#define TEST_ARTICLE_LANG "fr"
#define TEST_ARTICLE_SLUG "page_principale"



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


    
    // we should be able to get an article ...

    std::cout << "Try to get an article ... " ;

    results::Article article = articlesModels.get_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG
    );

    if (article.id > 0 ) {
        std::cout << " [ok]" << std::endl;
    } else {
        std::cout << " [fail]" << std::endl;
        noTestFailed = false;
    }

    // if we request directly the group id of that article, that should be the same
    // value as when we request the entire articel
    std::cout << "We should get the same group id when requesting it directly ... " ;

    int groupId = articlesModels.get_group_id_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG
    );
    if (article.groupId == groupId) {
        std::cout << " [ok]" << std::endl;
    } else {
        std::cout << " [fail]" << std::endl;
        noTestFailed = false;
    }

    if (noTestFailed) {
        return 0;
    } else {
        return 1;
    }

}
