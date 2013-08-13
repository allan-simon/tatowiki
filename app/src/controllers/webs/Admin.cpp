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
#include "Admin.h"


#include "contents/Admin.h"

//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

Admin::Admin(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{


    dispatcher().assign("/change-brand", &Admin::change_brand, this);
    dispatcher().assign("/change-brand_treat", &Admin::change_brand_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete


    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Admin::~Admin() {
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
void Admin::change_brand() {

    contents::admin::ChangeBrand c;
    init_content(c);


    render("admin_change_brand", c);
}


/**
 *
 */
void Admin::change_brand_treat() {

    forms::admin::ChangeBrand form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
