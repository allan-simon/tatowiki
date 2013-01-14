/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 * Copyright (C) 2013 Allan SIMON <allan.simon@supinfo.com> 
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
 * @package  Generics
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/allan-simon/tatowiki
 */

#include <cppcms_skel/generics/Config.h>
#include "Config.h"

namespace tatowiki {

/**
 *
 */
Config::Config() {

}


/**
 *
 */
void Config::set_lang_to_main_pages(
    cppcms::json::array lang2MainPagesJson
) {
    cppcms::json::array::const_iterator end = lang2MainPagesJson.end();
    for (
        cppcms::json::array::const_iterator p=lang2MainPagesJson.begin();
        p!= end;
        ++p
    ) {
        cppcms::json::array lang2MainPage = p->array();
        std::string lang = lang2MainPage[0].str();
        std::string mainPage = lang2MainPage[1].str();
        Config::get_instance()->lang2MainPages[lang] = mainPage;
    }
}

/**
 *
 */
std::string Config::get_slug_main_page_from_lang(
    const std::string &lang
) {
    return Config::get_instance()->lang2MainPages[lang];

}

/**
 *
 */
std::string Config::articles_url_from_lang_and_slug(
    const std::string &lang,
    const std::string &slug
) {
    return "http://" +
        lang + "." +
        ::Config::get_base_host() +
        "/articles/show/" + slug ;

}


/**
 *
 */
std::string Config::main_url_from_lang(
    const std::string &lang
) {
    return articles_url_from_lang_and_slug(
        lang,
        Config::get_slug_main_page_from_lang(lang)
    );
}




} // end of namespace tatowiki
