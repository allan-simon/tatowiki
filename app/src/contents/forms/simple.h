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
 * @package  Form
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
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


