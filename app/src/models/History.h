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
 * @category Tatoeba wiki
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */

#ifndef TatoWiki_HISTORY
#define TatoWiki_HISTORY


#include "cppcms_skel/models/SqliteModel.h"

#include "results/History.h"
namespace models {


/**
 * @class History
 * 
 * @brief @TODO
 * @since 30 October 2012       
 *
 */
class History : public SqliteModel {
    public:
        /**
         * @brief Constructor
         * @since 30 October 2012
         */
        History();

        /**
         * @brief Save a new version of an article
         * 
         * @param lang    ISO code of the language in which the article
         *                is written
         * @param slug    Slug of the article (i.e URL version of the
         *                title)
         * @param title   The title of the article
         * @param content The main content of the article
         * @param summary A description of the change
         *
         * @return bool If the article historic version has been added
         *
         * @since 04 November 2012
         */
        bool add_version(
            const std::string &lang,
            const std::string &slug,
            const std::string &title,
            const std::string &content,
            const std::string &summary
        );

        /**
         * @brief Retrieve the list of changes made on an article
         * 
         * @param lang ISO code of the language in which the article
         *             is written
         * @param slug Slug of the article (i.e URL version of the
         *             title)
         *
         * @return Changes The list of changes made on the given
         *                 article
         *
         * @since 04 November 2012
         *
         */
        results::Changes all_versions_of(
            const std::string &lang,
            const std::string &slug
        );


        /**
         * @brief Retrieve a given version of an article
         * 
         * @param int Version The version number

         * @return ArticleVersion The article as it was at that time
         *                        And information related to the edit
         *
         * @since 11 November 2012
         *
         */
        results::ArticleVersion get_version(
            const int version
        );
};

} // end namespace models 

#endif
