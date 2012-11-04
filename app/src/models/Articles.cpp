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
bool Articles::create_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug,
    const std::string &title,
    const std::string &content
) {
    cppdb::statement create = sqliteDb.prepare(
        "INSERT INTO articles(title,content,lang,slug,locked) "
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
        return false;
    }
    create.reset();
    return true;

}



} // end namespace models


