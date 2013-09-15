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


#ifndef TATOWIKI_CONTENTS_SEARCH_H
#define TATOWIKI_CONTENTS_SEARCH_H

#include <booster/function.h>

#include "contents/BaseContent.h"
#include "contents/forms/simple.h"
#include "results/Articles.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace search {

/**
 * @class Search Base content for every action of Search controller
 * @since 18 June 2013
 */
struct Search : public ::tatowiki::contents::BaseContent {
};

/**
 * @struct Simple
 * @since  18 June 2013
 * @brief
 */
struct Simple : public Search {

    forms::search::Simple simpleForm;

    /**
     * @brief Constructor
     */
    Simple() {
    }

};

/**
 * @struct Result Content used by the page "search/result"
 * @since  21 June 2013
 *
 */
struct Result : public Search {

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
     * @brief contains all the articles that match the request
     *        and the first part of their contents
     *
     * @since 4 July 2013
     */
    results::Articles articles;

    //TODO
    std::string query;

    Result() {

    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace search
} //end of namespace contents

#endif
