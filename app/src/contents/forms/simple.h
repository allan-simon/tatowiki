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

#ifndef TATOWIKI_SIMPLE
#define TATOWIKI_SIMPLE

#include <cppcms/form.h>

#ifndef _
    #define _(X) cppcms::locale::translate((X))
#endif

namespace forms{
namespace search {

/**
 * @struct simple
 * @brief  @TODO
 * @since  18 June 2013
 *
 */
struct Simple : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * @brief Search query
     */
    cppcms::widgets::text query;

    /**
     * @brief button to submit the form
     */
    cppcms::widgets::submit submit;

    /**
     * @brief Constructor
     */
    Simple() {

        //%%%NEXT_WIDGET_ADD_MARKER%%%
        query.name("query");
        query.message(_("Query:"));
        query.non_empty();
        add(query);

        submit.name(_("Search"));
        submit.value("submit");
        add(submit);
    }


};


} // end of namespace search
}// end of namespace forms


#endif


