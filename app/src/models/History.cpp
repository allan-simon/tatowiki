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

#include "models/History.h"


namespace models {

/**
 *
 */
History::History() :
    SqliteModel()
{
}


/**
 *
 */

bool History::add_version(
    const std::string &lang,
    const std::string &slug,
    const std::string &title,
    const std::string &content,
    const std::string &summary = ""
) {
    cppdb::statement addVersion = sqliteDb.prepare(
        "INSERT INTO history("
        "    title,"
        "    content,"
        "    lang,"
        "    slug,"
        "    summary,"
        "    version"
        ") VALUES ("
        "    ?,"
        "    ?,"
        "    ?,"
        "    ?,"
        "    ?,"
        // COALESCE = either we do version = version + 1 or
        // version = 1 (1+0) if no previous version
        "    1 + COALESCE("
        "       (SELECT version FROM history WHERE lang = ? and slug = ?),"
        "       0"
        "    )"
        ")"
    );
    // insert part
    addVersion.bind(title);
    addVersion.bind(content);
    addVersion.bind(lang);
    addVersion.bind(slug);
    addVersion.bind(summary);

    //coaelsce part
    addVersion.bind(lang);
    addVersion.bind(slug);
    
    try {
        addVersion.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        addVersion.reset();
        return false;
    }
    addVersion.reset();
    return true;
}


} // end namespace models


