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
 * @package  Results
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki
 */

#ifndef TATOWIKI_RESULTS_ARTICLES_H
#define TATOWIKI_RESULTS_ARTICLES_H


#include <vector>
#include "Articles.h"

namespace results {

    /**
     * @struct Change Represent a change made on an article
     *                Without going on "what has changed"
     *
     * @since 04 November 2012
     *
     */
    struct Change {
        /**
         * @brief version Version number of the modification
         *
         * @since 04 November 2012
         *
         */
        int version;

        /**
         * @brief editTime Timestamp when the change has beem made
         *
         * @since 04 November 2012
         *
         */
        unsigned int editTime;

        /**
         * @brief summary Short text for the user to explain the reason of
         *                this modification
         *
         * @since 04 November 2012
         *
         */
        std::string summary;


        /**
         * @brief Name of the user who has made this change
         *
         * @since 18 January 2013
         */
        std::string byUserName;

        /**
         * @brief Id of the user who has made this change
         *
         * @since 18 January 2013
         */
        int byUserId;

        /**
         * @brief Id of the changed made before (in the past) the current one
         *        -1 if the current change is the first one
         *
         * @since 20 March 2013
         */
        int previousVersion;
        
        /**
         * @brief Id of the changed made after (in the future) the current one
         *        -1 if the current change is the last one
         *
         * @since 20 March 2013
         */

        int nextVersion;


        public:
            Change(){};

            Change(
                int version,
                unsigned int editTime,
                const std::string &summary,
                const std::string &byUserName,
                const int byUserId,
                const int nextVersion = -1,
                const int previousVersion = -1
            ):
            version(version),
            editTime(editTime),
            summary(summary),
            byUserName(byUserName),
            byUserId(byUserId),
            nextVersion(nextVersion),
            previousVersion(previousVersion) {
                //Nothing yet except initialization of the struct fields
            }
    };

    /**
     * @struct ArticleVersion Structure used to represent the previous state
     *                        Of an article and information related to this
     *                        state
     *
     * @since 11 November 2012
     */
    struct ArticleVersion {
        results::Article article;
        results::Change change;

        /**
         * @brief test if article's version is an existing one or not
         *
         * @return bool True if it exists, false otherwise
         *
         * @since 11 November 2012
         *
         */
        bool exists() {
            return change.version > 0;
        };
    };

    /**
     * @class Changes Represent a list of change
     *
     * @since 04 November 2012
     *
     */
    struct Changes : public std::vector<results::Change> {
        public:
            /**
             * @brief Id of the first change made on this article
             *        (creation included)
             *
             * @since 20 March 2013
             */
            int oldestId;
            /**
             * @brief Id of the last change made on this article
             *        (deletion included)
             *
             * @since 20 March 2013
             */
            int newestId; 
    };

    /**
     * @class ArticlesVersions Represent of list of article versions
     * @since 18 January 2013
     */
    typedef std::vector<ArticleVersion> ArticlesVersions;
    

    /**
     * @class Represent a diff between two version of a same article
     *
     * @since 20 March 2013
     */
    struct Diff {
        std::string oldContent;
        int oldVersionTime;
        std::string newContent;
        int newVersionTime;
    };
} // end of namespace results


#endif
