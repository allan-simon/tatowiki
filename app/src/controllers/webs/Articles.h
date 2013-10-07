/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
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

        /**
         * @brief Generate and interlink the main pages of each language
         *
         * @param lang2MainPages A map containing the languages supported
         *                       and the slug of their main page
         *
         * @since 15 March 2013
         */
        static void generate_main_pages(
            std::map<std::string,std::string> lang2MainPages
        );



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
         * @param slug string URL name of the article
         *
         * @since 30 October 2012

         */
        void show(std::string slug);

        /**
         * @brief Edit a given article
         *
         * @param slug string URL name of the article
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
         * @param slug string URL name that will be associated to the page
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
         * @param slug string URL name of the article we want to remove
         *
         * @since 16 November 2012
         */
        void remove(const std::string slug);

        /**
         * @brief Page that will display all the articles
         * @since 17 November 2012
         */
        void show_all();

        /**
         * @brief @TODO add a description
         * 
         * @param slug URL name of the article to translate
         * 
         * @since 18 November 2012
         */
        void translate(const std::string slug);

        /**
         * @brief @TODO add a description
         * @since 18 November 2012
         */
        void translate_treat();

        /**
         * @brief Page to display the non-applied edition of an article
         *        when an a conflict between two editions appears
         *
         * @param conflictIdStr The conflict id as a string
         *
         * @since 14 March 2013
         */
        void show_conflict(std::string conflictIdStr);

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace generics

#endif
