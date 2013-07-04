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

#include "models/Search.h"


namespace models {

/**
 *
 */
Search::Search() :
    SqliteModel()
{
}


/**
 *
 */
std::string Search::exact_title(
    const std::string &query,
    const std::string &lang
) {
    cppdb::statement searchTitle = sqliteDb.prepare(
        "SELECT slug  FROM search "
        "WHERE lower(title) = lower(?) AND lang = ? LIMIT 1"
    );
    searchTitle.bind(query);
    searchTitle.bind(lang);

    cppdb::result res = searchTitle.row();
    if (res.empty()) {
        return "";
    } else {
        return res.get<std::string>("slug");
    }
}




/**
 *
 */
std::string Search::match_title(
    const std::string &query,
    const std::string &lang
) {
    cppdb::statement searchTitle = sqliteDb.prepare(
        "SELECT slug  FROM search "
        "WHERE title MATCH ? AND lang = ? LIMIT 1"
    );
    searchTitle.bind(query);
    searchTitle.bind(lang);

    cppdb::result res = searchTitle.row();
    if (res.empty()) {
        return "";
    } else {
        return res.get<std::string>("slug");
    }
}

/**
 *
 */
results::Articles Search::content(
    const std::string &query,
    const std::string &lang
) {
    cppdb::statement searchContent = sqliteDb.prepare(
        "SELECT "
        "   docid,  "
        "   lang,  "
        "   slug,  "
        "   title,  "
        "   content  "
        "FROM search "
        "WHERE "
        "   content MATCH ? AND "
        "   lang = ? "
    );
    searchContent.bind(query);
    searchContent.bind(lang);

    cppdb::result res = searchContent.query();
    results::Articles articles;
    while (res.next()) {
        results::Article tmpArticle(
            res.get<int>("docid"),
            res.get<std::string>("lang"),
            res.get<std::string>("slug"),
            res.get<std::string>("title"),
            content_summary(res.get<std::string>("content"))
        );
        articles.push_back(tmpArticle);
    }
    return articles;
}


std::string Search::content_summary(const std::string &content) {
    size_t endTitle=  content.find_first_of('\n',0);
    size_t endFirstSentence = content.find_first_of(
        "\n",
        endTitle+1
    );
    // for people who put several new lines before the title
    // and the actual content
    while (endFirstSentence - endTitle <= 2 ) {
        endTitle = endFirstSentence;
        endFirstSentence = content.find_first_of(
            "\n",
            endTitle+1
        );
    }

    std::string contentSummary = content.substr(
        endTitle,
        endFirstSentence - endTitle
    );

    return contentSummary;
}


} // end namespace models


