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


#ifndef TATOWIKI_GENERICS_CONFIG_H
#define TATOWIKI_GENERICS_CONFIG_H

#include <map>
#include <cppcms/json.h>
#include <cppcms_skel/generics/Singleton.h>

/**
 * @namespace tatowiki
 */
namespace tatowiki {

    /**
     * @class Config Contains the configuration given by config.js 
     *               and that are specific to Tatowiki
     *
     * @since 14 January 2013
     */
    class Config: public Singleton<Config>{
        friend class Singleton<Config>;

        private:
            /**
             * @brief Constructor, do nothing special for the moment
             *
             * @since 14 January 2013
             */
            Config();

            /**
             * @brief Map  lang -> main page for that lang
             *
             * @since 14 January 2013
             */
            std::map<std::string, std::string> lang2MainPages;
        public:


            /**
             * @brief get the full main page URL of a given language
             *
             * @param lang The interface language
             *
             * @return An url in the form http://...
             *
             * @since 14 January 2013
             */
            static std::string main_url_from_lang(
                const std::string &lang
            );


            /**
             * @brief get the full page URL of an article in a given language
             *
             * @param lang The language of the article
             * @param slug The url name of that article
             *
             * @return An url in the form http://...
             *
             * @since 14 January 2013
             */
            static std::string articles_url_from_lang_and_slug(
                const std::string &lang,
                const std::string &slug
            );


            /**
             * @brief get the URL name of the main page given language
             *
             * @param lang The interface language
             *
             * @return A slug, like "main-page"
             *
             * @since 14 January 2013
             */
            static std::string get_slug_main_page_from_lang(
                const std::string &lang
            );


            /**
             * @brief Set the map containing the lang-> main_page using
             *        a JSON array
             *
             * @param lang2MainPagesJson The JSON array extracted from
             *                           the config.js
             *
             * @since 14 January 2013
             */
            static void set_lang_to_main_pages(
                cppcms::json::array lang2MainPagesJson
            );

            /**
             * @brief Get the map lang->main page's slug
             *
             * @return The map lang->main page's slug
             *
             * @since 17 January 2013
             *
             */
            static std::map<std::string, std::string> get_lang_to_main_pages();
    };


} // end of namespace tatowiki


#endif


