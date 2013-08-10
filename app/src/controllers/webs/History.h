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

        /**
         * @brief Show the diff between two versions of an article
         *        It will redirect you to the previous page if the
         *        article or the versions you're requesting does not
         *        exists
         *
         * @param articleIdStr  The id of the article as a string
         * @param oldVersionStr The id of the old version as a string
         * @param newVersionStr The id of the new version as a string
         *
         * @since 20 March 2013
         */
        void show_diff_between(
            const std::string articleIdStr,
            const std::string oldVersionStr,
            const std::string newVersionStr
        );

        /**
         * @brief Will redirector to the page 
         *        showing the difference between this version of an article
         *        and the version just before 
         *
         * @since 20 March 2013
         */
        void diff_with_previous_version_of(
            const std::string articleIdStr,
            const std::string versionStr
        );

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace generics

#endif
