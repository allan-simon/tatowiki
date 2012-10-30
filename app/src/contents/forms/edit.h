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


#ifndef TatoWiki_EDIT
#define TatoWiki_EDIT


#include <cppcms/form.h>

#include "results/Articles.h"

namespace forms{
namespace articles {

/**
 * @struct Edit Form to edit an article
 * @since  30 October 2012
 *
 */
struct Edit : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * @brief Hidden field to store the slug of the article
     *        (i.e it's URL representation)
     *
     * @since  30 October 2012
     */
    cppcms::widgets::hidden slug;

    cppcms::widgets::text title;
    cppcms::widgets::textarea content;
    /**
     * @brief button to save the article and view it
     *
     * @since  30 October 2012
     */
    cppcms::widgets::submit saveAndView;

    /**
     * @brief button to save the article and continue to edit it
     *
     * @since  30 October 2012
     */
    cppcms::widgets::submit saveAndContinue;

    /**
     * @brief Constructor
     *
     * @since  30 October 2012
     */
    Edit() {
        init();
    };

    /**
     * @brief Constructor using an article structure to pre-fill
     *        the fields
     *
     * @since  30 October 2012
     */
    Edit(const results::Article &article) {
        
        init();
        slug.value(article.slug);
        title.value(article.title);
        content.value(article.content);
       
    };
    
    /**
     * @brief Centralize the common instruction between the
     *        constructors of this form
     *
     */
    void init() {
        //%%%NEXT_WIDGET_ADD_MARKER%%%
        add(slug);

        title.message(
            cppcms::locale::translate("Title")
        );
        title.non_empty();
        add(title);

        content.message(
            cppcms::locale::translate("Content")
        );
        content.non_empty();
        add(content);

        saveAndView.value(
            cppcms::locale::translate("Save")
        );
        saveAndView.name("save_and_view");
        add(saveAndView);

        add(saveAndContinue);
        saveAndContinue.value(
            cppcms::locale::translate("save and continue")
        );
        saveAndContinue.name("save_and_continue");

    };


};


} // end of namespace articles
}// end of namespace forms


#endif


