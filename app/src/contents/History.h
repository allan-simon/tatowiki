/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */


#ifndef TATOEBACPP_CONTENTS_HISTORY_H
#define TATOEBACPP_CONTENTS_HISTORY_H

#include <cppcms_skel/contents/content.h>

#include "contents/forms/diff_between.h"
#include "results/History.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace history {

/**
 * @class History
 * @brief Base content for every action of History controller
 * @since 30 October 2012
 */
struct History : public BaseContent {
};

/**
 * @struct RevertToVersion
 * @since  30 October 2012
 */
struct RevertToVersion : public History {

    RevertToVersion() {

    }

};

/**
 * @struct ShowVersion Content that will be used by History::show_version
 * @since  30 October 2012
 */
struct ShowVersion : public History {

    //TODO factorize with Show from Articles.h
    /**
     * @brief placeholder for the function that will be called
     *        when using  <%= varible | ext markdown %> in the
     *        template
     *
     * @since  30 October 2012
     */
    booster::function<
        std::string(
            const std::string &
        )
    > markdown;


    /**
     * @brief Represent a given version of a wiki Article
     * @since 11 November 2012
     */
    results::ArticleVersion articleVersion;

    ShowVersion() {

    }

};

/**
 * @struct DiffBetween
 * @since  30 October 2012
 */
struct DiffBetween : public History {

    forms::history::DiffBetween diffBetweenForm;

    /**
     * @brief Constructor
     */
    DiffBetween() {
    }

};

/**
 * @struct AllVersionsOf
 * @since  04 November 2012
 */
struct AllVersionsOf : public History {

    /**
     * @brief changes List of modification that has been made on the article
     *
     * @since 04 November 2012
     */
    results::Changes changes;

    /**
     * @brief slug Url name of the article
     *
     * @since 04 November 2012
     */

    std::string slug;

    /**
     * @brief Id of the article
     *
     * @since 20 March 2013
     */
    int articleId;

    AllVersionsOf() {
    }

};

/**
 * @struct RecentChanges Content used by the page history/recent-changes
 * @since  18 January 2013
 */
struct RecentChanges : public History {

    /**
     * @brief changes List of modifications made on the wiki
     *
     * @since 18 January 2013
     */
    results::ArticlesVersions articlesVersions;



    RecentChanges() {

    }

};

/**
 * @struct ShowDiffBetween Content used by history/show-diff-between
 * @since  20 March 2013
 */
struct ShowDiffBetween : public History {

    results::Diff diff;
    int oldVersion;
    int newVersion;
    std::string slug;

    ShowDiffBetween() {

    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace history
} //end of namespace contents

#endif
