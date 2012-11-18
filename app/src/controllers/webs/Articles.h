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

#ifndef CONTROLLERS_WEBS_ARTICLES_H
#define CONTROLLERS_WEBS_ARTICLES_H

#include <cppcms_skel/controllers/webs/Controller.h>


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace models {
    class Articles;
    class History;
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%% 
}

namespace controllers {
namespace webs { 
/**
 * @class Articles
 * @brief Module dealing with wiki pages that can be edited/added
 * @since 30 October 2012
 */
class Articles : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 30 October 2012
         */
        Articles(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 30 October 2012
         */
        ~Articles();

    private:
        /**
         * @brief TODO
         * @since %%MODEL_CTRL_TODAY%%
         */
        models::Articles *articlesModel;
        
        /**
         * @brief Use to access to the history features 
         * @since 04 November 2012
         */
        models::History *historyModel;
        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%
    

        /**
         * @brief Display an article
         *
         * @param string slug URL name of the article
         *
         * @since 30 October 2012

         */
        void show(std::string slug);

        /**
         * @brief Edit a given article
         *
         * @param string slug URL name of the article
         *
         * @since 30 October 2012
         */
        void edit(const std::string slug);

        /**
         * @brief Treat the form sent after editing an article
         * @since 30 October 2012
         */
        void edit_treat();

        /**
         * @brief Show a form to create a new page with a given slug
         *
         * @param string slug URL name that will be associated to the page
         *
         * @since 30 October 2012
         */
        void create(std::string slug);

        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void create_treat();

        /**
         * @brief Remove a given article from the list of viewable articles
         *
         * @param string slug URL name of the article we want to remove
         *
         * @since 16 November 2012
         */
        void remove(const std::string slug);

        /**
         * @brief Page that will display all the articles
         * @since 17 November 2012
         */
        void show_all();

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace generics

#endif
