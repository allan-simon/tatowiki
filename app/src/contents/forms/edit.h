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
};


} // end of namespace articles
}// end of namespace forms


#endif


