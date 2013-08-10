/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Generics
 * @author   Allan SIMON <allan.simon@supinfo.com>
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
bool Config::isPrivate() {
    return Config::get_instance()->privateWiki;
}

/**
 *
 */
void Config::isPrivate(bool privateWiki) {
    Config::get_instance()->privateWiki = privateWiki;
}

/**
 *
 */
std::map<std::string, std::string> Config::get_lang_to_main_pages() {
    return Config::get_instance()->lang2MainPages;
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
