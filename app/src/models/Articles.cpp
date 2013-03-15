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
#include <vector>
#include <cppdb/frontend.h>
#include <cppcms/localization.h>

#include "models/Articles.h"


#define _(X) cppcms::locale::translate((X))

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
        article.groupId = res.get<int>("group_id");
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
    add_to_group(
        id,
        id
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

int Articles::get_group_id_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug
) {
    cppdb::statement getGroupIdFromLangAndSlug = sqliteDb.prepare(
        "SELECT group_id "
        "FROM articles "
        "WHERE "
        "   lang = ? AND"
        "   slug = ? "
        "LIMIT 1"
    );
    getGroupIdFromLangAndSlug.bind(lang);
    getGroupIdFromLangAndSlug.bind(slug);

    cppdb::result res = getGroupIdFromLangAndSlug.row();

    int groupId = ARTICLE_DOESNT_EXIST_ERROR;
    if (!res.empty()) {
        groupId = res.get<int>("group_id");
    }
    getGroupIdFromLangAndSlug.reset();

    return groupId;
}



int Articles::get_id_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug
) {
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
    if (origLang == lang) {
        return ARTICLE_SAME_TRANSLATION_LANGUAGE_ERROR;
    }
    //cppdb::transaction guard(sqliteDb);

    // GET group id of the article 
    const int groupId = get_group_id_from_lang_and_slug(
        origLang,
        origSlug
    );
    if(groupId <= 0) { // TODO test if article exists
        return ARTICLE_DOESNT_EXIST_ERROR;
    }
    // test if articles already has a translation in that lang
    if (group_contains_lang(groupId,lang)) {
        return ARTICLE_ALREADY_TRANSLATED_ERROR;
    }

    // save translation 
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
    const int linksAdded = add_to_group(
        groupId,
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
bool Articles::group_contains_lang(
    const int groupId,
    const std::string &lang
) {
    
    cppdb::statement checkTransExists = sqliteDb.prepare(
        "SELECT 1 "
        "FROM articles "
        "WHERE "
        "   group_id = ? AND "
        "   lang = ? "
        "LIMIT 1"
    );
    checkTransExists.bind(groupId);
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
int Articles::add_to_group(
    const int groupId,
    const int translationId
) {
    
    // if we want to translate a  by  b ...
    cppdb::statement addToGroup = sqliteDb.prepare(
        "UPDATE articles "
        "SET  "
        "   group_id = ? "
        "WHERE id = ?"
    );

    addToGroup.bind(groupId);
    addToGroup.bind(translationId);


    try {
        addToGroup.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        addToGroup.reset();
        return ARTICLE_ADD_TRANSLATION_LINK_ERROR;
    }
    addToGroup.reset();
    return 1;


}

/**
 *
 */
results::TranslatedIn Articles::get_group_of(
    const int articleId,
    const int groupId
) {
    
    cppdb::statement request = sqliteDb.prepare(
        "SELECT "
        "    lang, "
        "    slug  "
        "FROM articles "
        "WHERE "
        "   group_id = ? AND "
        "   id != ?"
    );
    request.bind(groupId);
    request.bind(articleId);

    cppdb::result res = request.query();

    results::TranslatedIn translatedIn;
    while (res.next()) {
        std::string translationLang = res.get<std::string>("lang");
        std::string translationSlug = res.get<std::string>("slug");

        translatedIn[translationLang] = translationSlug;
    }
    request.reset();
    return translatedIn;

}

/**
 *
 */
int Articles::save_conflict(
    const results::Article &article
) {
    cppdb::statement create = sqliteDb.prepare(
        "INSERT INTO conflicts("
        "    article_id,"
        "    title,"
        "    content,"
        "    lang,"
        "    slug"
        ") "
        "VALUES ( "
        "   ? ,"
        "   ? ,"
        "   ? ,"
        "   ? ,"
        "   ? "
        ")"
    );
    
    create.bind(article.id);
    create.bind(article.title);
    create.bind(article.content);
    create.bind(article.lang);
    create.bind(article.slug);

    try {
        create.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        create.reset();
        return CONFLICT_CREATION_ERROR;
    }

    // the last inserted ID
    const int conflictId = create.last_insert_id();
    create.reset();
    return conflictId;

}

/**
 *
 */
results::Article Articles::get_article_from_conflict(
    const int conflictId
) {
    cppdb::statement getFromLangAndSlug = sqliteDb.prepare(
        "SELECT * FROM conflicts "
        "WHERE id = ? LIMIT 1"
    );
    getFromLangAndSlug.bind(conflictId);

    cppdb::result res = getFromLangAndSlug.row();
    results::Article article;

    if (!res.empty()) {
        article.id = res.get<int>("article_id");
        article.lang = res.get<std::string>("lang");
        article.content = res.get<std::string>("content");
        article.slug = res.get<std::string>("slug");
        article.title = res.get<std::string>("title");
    } else {
        article.id = 0;
    }
    getFromLangAndSlug.reset();
    return article;
}



} // end namespace models


