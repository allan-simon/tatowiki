/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
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
