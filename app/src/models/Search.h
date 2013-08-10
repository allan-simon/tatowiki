/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_SEARCH
#define TATOWIKI_SEARCH

#include <cppcms_skel/models/SqliteModel.h>
#include "results/Articles.h"
namespace models {


/**
 * @class Search @TODO add a description
 * @since 18 June 2013
 *
 */
class Search : public cppcmsskel::models::SqliteModel {

    private:
        /**
         * @brief Shorten the content of an article
         *
         * @param content The content to shorten
         *
         * @return A string containing only an "interesting" part
         *         of the initial content
         *
         * @since 5 July 2013
         */
        std::string content_summary(const std::string &content);

    public:
        /**
         * @brief Constructor
         * @since 18 June 2013
         */
        Search();

        /**
         * @brief Perform an exact search in the articles' title
         *
         * @param query The query to perform
         * @param lang  The query will be performed only on articles
         *              int that language
         *
         * @return The slug of this article if an exact match (delta collation)
         *         empty string otherwise
         *
         * @since 4 July 2013
         */
        std::string exact_title(
            const std::string &query,
            const std::string &lang
        );


        /**
         * @brief Perform a search in the articles' title
         *
         * @param query The query to perform
         * @param lang  The query will be performed only on articles
         *              int that language
         *
         * @return The slug of this article if any match
         *         empty string otherwise
         *
         * @since 4 July 2013
         */
        std::string match_title(
            const std::string &query,
            const std::string &lang
        );

        /**
         * @brief Perform a search in the articles' content
         *
         * @param query The query to perform
         * @param lang  The query will be performed only on articles
         *              int that language
         *
         * @since 4 July 2013
         */
        results::Articles content(
            const std::string &query,
            const std::string &lang
        );


};

} // end namespace models

#endif
