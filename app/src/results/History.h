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

        public:
            Change(
                int version,
                unsigned int editTime,
                const std::string &summary
            ):
            version(version),
            editTime(editTime),
            summary(summary) {
                //Nothing yet except initialization of the struct fields
            }
    };

    /**
     * @class Changes Represent a list of change
     *
     * @since 04 November 2012
     *
     */
    typedef std::vector<Change> Changes;

} // end of namespace results


#endif
