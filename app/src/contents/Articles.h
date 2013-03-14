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
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
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
 * @brief 
 */
struct Show : public Articles {

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
 * @struct Edit
 * @since  30 October 2012
 * @brief 
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
 * @brief 
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
 * @brief 
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

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace articles
} //end of namespace contents

#endif
