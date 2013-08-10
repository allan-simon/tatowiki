/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Forms
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_CREATE
#define TATOWIKI_CREATE

#include <cppcms/form.h>
#include "base_articles_form.h"

namespace forms{
namespace articles {

/**
 * @struct Create Structure representing a form to create a new article
 * @since  30 October 2012
 *
 */
struct Create : public BaseArticleForm {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * @brief Constructor
     */
    Create(const std::string &slugStr = "") {
        init_and_add();
        slug.value(slugStr);
    }



};


} // end of namespace articles
}// end of namespace forms


#endif


