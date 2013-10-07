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

#ifndef TatoWiki_HISTORY
#define TatoWiki_HISTORY


#include <cppcms_skel/models/SqliteModel.h>

#include "results/History.h"

#define NO_HISTORY_FOR_ARTICLE_ERROR -2
#define HISTORY_UNKOWN_ERROR -3
namespace models {


/**
 * @class History
 *
 * @since 30 October 2012
 *
 */
class History : public cppcmsskel::models::SqliteModel {
    public:
        /**
         * @brief Constructor
         * @since 30 October 2012
         */
        History();

        /**
         * @brief Save a new version of an article
         *
         * @param article The article's version to save
         * @param userId  Id of the user who has added this version
         * @param summary A description of the change
         *
         * @return bool If the article historic version has been added
         *
         * @since 06 March 2013
         */
        bool add_version(
            const results::Article &article,
            const int userId,
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
         * @param version int The version number

         * @return ArticleVersion The article as it was at that time
         *                        And information related to the edit
         *
         * @since 11 November 2012
         *
         */
        results::ArticleVersion get_version(
            const int version
        );


        /**
         * @brief Get a summary of the last modifications made
         *        on the wiki
         *
         * @param number Will return the numberTh last modifications
         *
         * @return A list of modification
         *
         * @since 18 January 2013
         */

        results::ArticlesVersions recent_changes(
            const int number = 100
        );

        /**
         * @brief Get the last revision number of an article
         *
         * @param articleId The id of the article
         *
         * @return The most recent revision number of that article
         *
         * @since 15 March 2013
         */
        int get_last_version_id_of(
            const int articleId
        );

        /**
         * @brief Return the diff between two versions of an article
         *
         * @param articleId The article we want to compare two versions of
         * @param oldVersion Id of the old revision we will use as a base
         * @param newVersion Id of the new revision we will use to compare
         *
         * @return The two contents and their differences
         *
         * @since 20 March 2013
         */
        results::Diff diff(
            const int articleId,
            const int oldVersion,
            const int newVersion
        );

        /**
         * @brief Return the id of the change change that happened just
         *               before the one given on parameter on a given article
         *
         * @param articleId The id of the article we're interested in
         * @param version Id of the version we want to get the previous change
         *
         * @return The id of the change preceding the one given in parameter
         *
         * @since 20 March 2013
         */
        int get_version_of_before(
            const int articleId,
            const int version
        );

};

} // end namespace models

#endif
