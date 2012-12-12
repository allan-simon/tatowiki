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
        article.isLocked = res.get<int>("locked");
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
        "    slug,"
        "    locked"
        ") "
        "VALUES ( "
        "   ? ,"
        "   ? ,"
        "   ? ,"
        "   ? ,"
        "   0  "
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
} // end namespace models


