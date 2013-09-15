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

#ifndef TATOWIKI_CONTENTS_ARTICLES_H
#define TATOWIKI_CONTENTS_ARTICLES_H

#include <booster/function.h>
#include <cppcms_skel/contents/content.h>

#include "contents/forms/edit.h"
#include "contents/forms/create.h"
#include "contents/forms/translate.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

#include "results/Articles.h"
namespace contents {
namespace articles {

/**
 * @class Articles
 * @brief Base content for every action of Articles controller
 * @since 30 October 2012
 */
struct Articles : public BaseContent {
};


/**
 * @struct Show
 * @since  30 October 2012
 */
struct Show : public Articles {

    /**
     * @brief placeholder for the function that will be called
     *        when using  <%= variable | ext markdown %> in the
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
     * @brief key used for caching the article section of the web
     *        page
     *
     * @since 20 January 2013
     *
     */
    std::string cacheKey;

    /**
     * @brief the article to display
     *
     * @since  30 October 2012
     */
    results::Article article;

    /**
     * @brief The languages in which the article is available
     * @since 27 December 2012
     */
    results::TranslatedIn translatedIn;

    /**
     * @brief Constructor
     *
     * @since  30 October 2012
     */
    Show(): article() {
    }

};

/**
 * @struct Edit Contains the information send to the view in order
 *              to present an edit form of an article
 * @since  30 October 2012
 */
struct Edit : public Articles {

    forms::articles::Edit editForm;

    /**
     * @brief Constructor
     *
     * @param article The article that we will use to fill the
     *                edit form.
     *
     * @since  30 October 2012
     *
     */
    Edit(
        const results::Article &article,
        const int lastVersionId

    ): editForm(article,lastVersionId) {
    }

};


/**
 * @struct Create
 * @since  30 October 2012
 */
struct Create : public Articles {

    forms::articles::Create createForm;

    /**
     * @brief Constructor
     */
    Create(const std::string &slug = "") : createForm(slug) {
    }

};

/**
 * @struct ShowAll
 * @since  17 November 2012
 */
struct ShowAll : public Articles {

    /**
     * @brief contains all the articles titles and url to access to it
     *
     * @since 17 November 2012
     */
    results::Articles articles;

    ShowAll() {

    }

};

/**
 * @struct Translate Content used for the rendering the "articles/translate"
 *         pages.
 * @since  18 November 2012
 *
 */
struct Translate : public Articles {

    forms::articles::Translate translateForm;

    /**
     * @brief Constructor
     */
    Translate(const std::string &slug) : translateForm(slug) {
    }

};

/**
 * @struct ShowConflict
 * @since  14 March 2013
 */
struct ShowConflict : public Show {

    ShowConflict() {

    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace articles
} //end of namespace contents

#endif
