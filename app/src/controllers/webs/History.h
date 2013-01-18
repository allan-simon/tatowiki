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
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */

#ifndef CONTROLLERS_WEBS_HISTORY_H
#define CONTROLLERS_WEBS_HISTORY_H

#include <cppcms_skel/controllers/webs/Controller.h>


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
//controller every time we modify a model. even though it does
// not affect the controller
namespace models {
    class History;
    class Articles;
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%% 
}

namespace controllers {
namespace webs { 
/**
 * @class History
 * @brief @TODO
 * @since 30 October 2012
 */
class History : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 30 October 2012
         */
        History(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 30 October 2012
         */
        ~History();

    private:
        /**
         * @brief TODO
         * @since %%MODEL_CTRL_TODAY%%
         */
        models::History *historyModel;

        /**
         * @brief Link to the Articles Model
         *
         * @since 11 November 2012
         */
        models::Articles *articlesModel;

        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%
    

        /**
         * @brief Not a page, directly revert an article to a given
         *        version and redirect to the page that display it
         *
         * @param string slug    URL name of the article to revert
         * @param string version Version number to which revert the
         *                       article (number as a string)
         *
         * @since 30 October 2012
         */
        void revert_to_version(
            const std::string slug,
            const std::string versionStr 
        );

        /**
         * @brief Display the given version of an article
         * @param string versionStr The version number as a string
         * @since 30 October 2012
         */
        void show_version(
            const std::string versionStr
        );

        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void diff_between();

        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void diff_between_treat();

        /**
         * @brief Show all the version of a given article
         * 
         * @param string slug The url name of the article, will be used in
         *                    combination with the lang to identify the article
         *
         * @since 04 November 2012
         */
        void all_versions_of(const std::string slug);

        /**
         * @brief Show the last modifications made on the wiki
         * @since 18 January 2013
         */
        void recent_changes();

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace generics

#endif
