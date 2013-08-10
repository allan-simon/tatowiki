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
             * @brief Permit to know if the wiki is set as
             *        private or not
             * @TODO replace this by something better to manage
             *       global permission
             *
             * @since 28 March 2013
             */
            bool privateWiki;
            /**
             * @brief Map  lang -> main page for that lang
             *
             * @since 14 January 2013
             */
            std::map<std::string, std::string> lang2MainPages;
        public:
            /**
             * @brief Permit to know if the wiki is set as
             *        private or not
             *
             * @return bool True if it is private, false otherwise
             *
             * @since 28 March 2013
             */
            static bool isPrivate(void);

            /**
             * @brief Set if the wiki is private or not
             *
             * @param privateWiki True if it is now private,
             *                    false if we want it to be public
             *
             * @since 28 March 2013
             */
            static void isPrivate(bool privateWiki);


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


