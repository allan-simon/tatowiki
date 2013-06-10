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


#ifndef TATOWIKI_TRANSLATE
#define TATOWIKI_TRANSLATE


#include <cppcms/form.h>
#include <cppcms_skel/generics/Languages.h>
#include "base_articles_form.h"

#define _(X) cppcms::locale::translate((X))

namespace forms{
namespace articles {

/**
 * @struct Translate Form that permit to translate an article by creating an other article
 *                   in an other language.
 * @since  18 November 2012
 *
 */
struct Translate : public BaseArticleForm {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * @brief use to select the lang in which we're translating
     *        the article
     * @since 8 December 2012
     */
    cppcms::widgets::select transLang;
    
    /**
     * @brief text field to choose what will be the slug
     *        of the translated article
     */
    cppcms::widgets::text translationSlug;

    /**
     * @brief Constructor
     */
    Translate(const std::string &slugStr = "") {
        init();
        Languages::get_instance()->fill_form_select(transLang);

        slug.value(slugStr);
        transLang.message(_("Language of the translation:"));

        translationSlug.name("translationSlug");
        translationSlug.id("translationSlug");
        translationSlug.message(_("URL name of this article's translation:"));
        translationSlug.non_empty();

        add(slug);
        add(title);
        add(transLang);
        add(translationSlug);
        add(content);
        add(summary);
        add(saveAndView);
        add(saveAndContinue);


    }


};


} // end of namespace articles
}// end of namespace forms


#endif


