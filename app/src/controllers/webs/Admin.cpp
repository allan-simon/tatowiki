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
#include <cppcms_skel/models/Users.h>
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

    dispatcher().assign("/change-user-password", &Admin::change_user_password, this);
    dispatcher().assign("/change-user-password_treat", &Admin::change_user_password_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete


    usersModel = new cppcmsskel::models::Users();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Admin::~Admin() {
    delete usersModel;
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
void Admin::change_brand() {

    ADMIN_REQUIRED();

    contents::admin::ChangeBrand c;
    init_content(c);


    render("admin_change_brand", c);
}


/**
 *
 */
void Admin::change_brand_treat() {

    TREAT_PAGE();
    ADMIN_REQUIRED();

    forms::admin::ChangeBrand form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


/**
 *
 */
void Admin::change_user_password() {

    ADMIN_REQUIRED();

    contents::admin::ChangeUserPassword c;
    init_content(c);


    render("admin_change_user_password", c);
}


/**
 *
 */
void Admin::change_user_password_treat() {

    TREAT_PAGE();
    ADMIN_REQUIRED();

    forms::admin::ChangeUserPassword form;
    form.load(context());

    // we  check that there's no empty field
    if (!form.validate()) {
        add_error(_("Your form is not valid"));
        go_back_to_previous_page();
        return;
    }

    // we check that the username exists
    const std::string username = form.username.value();
    if (!usersModel->username_exists(username)) {
        add_error(_("The username you've entered does not exist"));
        go_back_to_previous_page();

    }
    // we check that the user has entered the same new password twice
    const std::string newPassword = form.newPassword.value();
    const std::string newPasswordTwice = form.newPasswordTwice.value();
    if (newPassword != newPasswordTwice) {
        add_error(_("You haven't entered twice the same new password."));
        go_back_to_previous_page();
        return;
    }

    const bool changed = usersModel->change_password(
       username,
       newPassword
    );
    if (!changed) {
        add_error(_("Error while trying to update your password."));
        go_back_to_previous_page();
        return;
    }
    add_success(_("Password updated successfully."));
    go_back_to_previous_page();

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
