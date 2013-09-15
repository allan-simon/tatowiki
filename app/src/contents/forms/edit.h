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

#ifndef TATOWIKI_EDIT
#define TATOWIKI_EDIT


#include <cppcms/form.h>

#include "results/Articles.h"
#include "base_articles_form.h"

namespace forms{
namespace articles {

/**
 * @struct Edit Form to edit an article
 * @since  30 October 2012
 *
 */
struct Edit : public BaseArticleForm {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    cppcms::widgets::hidden lastVersion;
    /**
     * @brief Constructor
     *
     * @since  30 October 2012
     */
    Edit() {
        init_and_add();
        add(lastVersion);
    }

    /**
     * @brief Constructor using an article structure to pre-fill
     *        the fields
     *
     * @since  30 October 2012
     */
    Edit(
        const results::Article &article,
        const int lastVersionId
    ) {
        init_and_add();
        slug.value(article.slug);
        title.value(article.title);
        content.value(article.content);
        lastVersion.value(std::to_string(lastVersionId));
        add(lastVersion);

    }
};


} // end of namespace articles
}// end of namespace forms


#endif


