/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com> 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @category Tatoeba wiki
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */


#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <cppdb/frontend.h>

#include "models/Articles.h"


namespace models {

/**
 *
 */
Articles::Articles() :
    SqliteModel()
{
}

/**
 *
 */
Articles::Articles(const std::string &dbPath) :
    SqliteModel(dbPath)
{
}

results::Article Articles::get_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug
) {
    cppdb::statement getFromLangAndSlug = sqliteDb.prepare(
        "SELECT * FROM articles "
        "WHERE lang = ? AND slug = ? LIMIT 1"
    );
    getFromLangAndSlug.bind(lang);
    getFromLangAndSlug.bind(slug);

    cppdb::result res = getFromLangAndSlug.row();
    results::Article article;

    if (!res.empty()) {
        article.id = res.get<int>("id");
        article.lang = res.get<std::string>("lang");
        article.content = res.get<std::string>("content");
        article.slug = res.get<std::string>("slug");
        article.title = res.get<std::string>("title");
        article.isLocked = res.get<int>("locked") == true;
    } else {
        article.id = 0;
    }
    getFromLangAndSlug.reset();
    return article;
}

/**
 *
 */
bool Articles::edit_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug,
    const std::string &title,
    const std::string &content
) {
    cppdb::statement edit = sqliteDb.prepare(
        "UPDATE articles "
        "SET "
        "   title = ? , "
        "   content = ? "
        "WHERE lang = ? AND slug = ?"
    );
    
    edit.bind(title);
    edit.bind(content);
    edit.bind(lang);
    edit.bind(slug);

    try {
        edit.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        edit.reset();
        return false;
    }
    edit.reset();
    return true;

}

/**
 *
 */
int Articles::create_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug,
    const std::string &title,
    const std::string &content
) {
    cppdb::statement create = sqliteDb.prepare(
        "INSERT INTO articles("
        "    title,"
        "    content,"
        "    lang,"
        "    slug"
        ") "
        "VALUES ( "
        "   ? ,"
        "   ? ,"
        "   ? ,"
        "   ? "
        ")"
    );
    
    create.bind(title);
    create.bind(content);
    create.bind(lang);
    create.bind(slug);

    try {
        create.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        create.reset();
        return ARTICLE_CREATION_ERROR;
    }

    //TODO sqlite provide something better to get
    // the last inserted ID
    const int id = get_id_from_lang_and_slug(
        lang,
        slug
    );

    create.reset();
    return id;

}

/**
 *
 */
bool Articles::remove(
    const std::string &lang,
    const std::string &slug
) {

    
    // first we copy the articles to the list of deleted articles
    cppdb::statement moveToDeleted = sqliteDb.prepare(
        "INSERT OR REPLACE INTO deleted_articles "
        "SELECT * FROM articles  "
        "WHERE "
        "    lang = ? AND "
        "    slug = ?; "
    );

    moveToDeleted.bind(lang);
    moveToDeleted.bind(slug);

    try {
        moveToDeleted.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        moveToDeleted.reset();
        return false;
    }
    moveToDeleted.reset();

    // then we remove it from the list of actual articles
    cppdb::statement remove = sqliteDb.prepare(
        "DELETE FROM articles "
        "WHERE "
        "    lang = ? AND "
        "    slug = ?; "
    );

    remove.bind(lang);
    remove.bind(slug);

    try {
        remove.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        remove.reset();
        return false;
    }
    remove.reset();
    return true;

}

/**
 *
 */
results::Articles Articles::get_all() {
    cppdb::statement allArticles = sqliteDb.prepare(
        "SELECT "
        "   lang, "
        "   slug, "
        "   title "
        "FROM articles "
        "ORDER BY title"
    );

    cppdb::result res = allArticles .query();
    results::Articles articles;
    while (res.next()) {
        results::Article tmpArticle(
            res.get<std::string>("lang"),
            res.get<std::string>("slug"),
            res.get<std::string>("title")
        );
        articles.push_back(tmpArticle);
    }
    allArticles.reset();
    return articles;

}

int Articles::get_id_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug
) {
    std::cout << "search for " << lang << ":" << slug << std::endl;
    cppdb::statement getIdFromLangAndSlug = sqliteDb.prepare(
        "SELECT id "
        "FROM articles "
        "WHERE "
        "   lang = ? AND"
        "   slug = ? "
        "LIMIT 1"
    );
    getIdFromLangAndSlug.bind(lang);
    getIdFromLangAndSlug.bind(slug);

    cppdb::result res = getIdFromLangAndSlug.row();

    int id = ARTICLE_DOESNT_EXIST_ERROR;
    if (!res.empty()) {
        id = res.get<int>("id");
    }
    getIdFromLangAndSlug.reset();

    return id;
}

/**
 *
 */
int Articles::translate_from_lang_and_slug(
    const std::string &origLang,
    const std::string &origSlug,
    const std::string &lang,
    const std::string &slug,
    const std::string &title,
    const std::string &content
) {
    //cppdb::transaction guard(sqliteDb);

    // GET id of the article 
    const int articleId = get_id_from_lang_and_slug(
        origLang,
        origSlug
    );
    if(articleId <= 0) { // TODO test if article exists
        return ARTICLE_DOESNT_EXIST_ERROR;
    }
    // test if articles already has a translation in that lang
    if (is_translated_in(articleId,lang)) {
        return ARTICLE_ALREADY_TRANSLATED_ERROR;
    }

    // save translation 
    // TODO need to change create_from_lang to return an ID
    // if ID < 0 => error 
    const int translationId = create_from_lang_and_slug(
        lang,
        slug,
        title,
        content
    );
    if (translationId <= 0) {
        return ARTICLE_CREATE_TRANSLATION_ERROR;
    }
    const int linksAdded = add_translation_link(
        articleId,
        translationId
    );
    // add translation link
    if (linksAdded < 0) {
        return ARTICLE_ADD_TRANSLATION_LINK_ERROR;
    }
    
    //guard.commit();
    return translationId;

}

/**
 *
 */
bool Articles::is_translated_in(
    const int articleId,
    const std::string &lang
) {
    
    cppdb::statement checkTransExists = sqliteDb.prepare(
        "SELECT 1 "
        "FROM articles_translations at "
        "JOIN articles t ON"
        "   (at.translation_id = t.id) "
        "WHERE "
        "   at.article_id = ? AND "
        "   t.lang = ? "
        "LIMIT 1"
    );
    checkTransExists.bind(articleId);
    checkTransExists.bind(lang);
    cppdb::result res = checkTransExists.row();
    int checkresult = 0;
    res.fetch(0,checkresult);

    // Don't forget to reset statement
    checkTransExists.reset();

    if (checkresult == 1 ) {
        return true;
    }
    return false;
}

/**
 *
 */
int Articles::add_translation_link(
    const int articleId,
    const int translationId
) {
    
    // if we want to translate a  by  b ...
    cppdb::statement insertTransLink = sqliteDb.prepare(
        "INSERT INTO articles_translations "
        // ... we insert the link  a -> b 
        "SELECT "
        "   ?,"
        "   ? "

        "UNION "
        // ... then the link  b -> a 
        "SELECT "
        "   ?,"
        "   ?"

        "UNION "
        // ... then the linkS b -> all the things linked to  a
        "SELECT "
        "    ?, "
        "    (SELECT "
        "       translation_id "
        "    FROM "
        "       articles_translations "
        "    WHERE "
        "       article_id = ? "
        "    ) "

        "UNION "

        // ..  and the linkS  all the things linked to  a -> b
        "SELECT "
        "   (SELECT "
        "       article_id "
        "   FROM "
        "       articles_translations "
        "   WHERE "
        "       translation_id = ? "
        "   ),"
        "   ?"

        ";"
    );

    // ... we insert the link  a -> b 
    insertTransLink.bind(articleId);
    insertTransLink.bind(translationId);

    // ... then the link  b -> a 
    insertTransLink.bind(translationId);
    insertTransLink.bind(articleId);

    // ... then the linkS b -> all the things linked to  a
    insertTransLink.bind(translationId);
    insertTransLink.bind(articleId);

    // ..  and the linkS  all the things linked to  a -> b
    insertTransLink.bind(articleId);
    insertTransLink.bind(translationId);



    try {
        insertTransLink.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        insertTransLink.reset();
        return ARTICLE_ADD_TRANSLATION_LINK_ERROR;
    }
    insertTransLink.reset();
    return 1;


}

/**
 *
 */
results::TranslatedIn Articles::get_translated_in(
    const int id
) {
    
    cppdb::statement request = sqliteDb.prepare(
        "SELECT "
        "    t.lang as tlang, t.slug as tslug "
        "FROM articles_translations at "
        "JOIN articles t ON"
        "   (at.translation_id = t.id) "
        "WHERE "
        "   at.article_id = ? "
    );
    request.bind(id);

    cppdb::result res = request.query();

    results::TranslatedIn translatedIn;
    while (res.next()) {
        std::string translationLang = res.get<std::string>("tlang");
        std::string translationSlug = res.get<std::string>("tslug");

        translatedIn[translationLang] = translationSlug;
    }
    request.reset();
    return translatedIn;

}

} // end namespace models


