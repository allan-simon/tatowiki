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
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */

#include <cppcms/session_interface.h>
#include <cppcms_skel/contents/forms/change_interface_langs.h>
#include "Pages.h"

#include "contents/Pages.h"
#include "generics/Config.h"




namespace controllers {
namespace webs {

Pages::Pages(cppcms::service& serv) : controllers::webs::Controller(serv) {
    dispatcher().assign("", &Pages::homepage, this);
}

/**
 *
 */
void Pages::change_interface_lang_treat() {
    forms::InterfaceLang form;
    form.set_langs();
    form.load(context());
    if(!form.validate()) {
        go_back_to_previous_page();
    }

    session()["interfaceLang"] =  form.interfaceLang.selected_id();

    go_back_to_previous_page();



}

/**
 *
 */
void Pages::homepage() {

    // the homepage actually redirect to the
    // main wiki page

    redirect(
        tatowiki::Config::main_url_from_lang(
            get_interface_lang()
        )
    );
}


} // End namespace webs
} // End namespace controllers
