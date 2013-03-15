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
#include "Users.h"


#include "contents/Users.h"

#include "models/Users.h"
//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

Users::Users(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{

    dispatcher().assign("/logout", &Users::logout, this);

    dispatcher().assign("/login", &Users::login, this);
    dispatcher().assign("/login_treat", &Users::login_treat, this);

    dispatcher().assign("/register-new", &Users::register_new, this);
    dispatcher().assign("/register-new_treat", &Users::register_new_treat, this);

    dispatcher().assign("/change-password", &Users::change_password, this);
    dispatcher().assign("/change-password_treat", &Users::change_password_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete




    usersModel = new models::Users();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Users::~Users() {
    delete usersModel;
    //%%%NEXT_DEL_MODEL_CTRL%%%
}

/**
 *
 */
void Users::logout() {
    current_user_logout();
    set_message(_("Logout"));
    go_back_to_previous_page();

}

/**
 *
 */
void Users::login() {

    contents::users::Login c;
    init_content(c);

    // we store in the hidden field of the login form
    // the page we wanted to access
    // in order to be able to redirect on it after login

    std::string wantedPage = request().get("from"); 
    if(wantedPage.empty()) {
        //TODO replace / by APPLICATION_ROOT
        wantedPage = "/";
    }

    c.loginForm.previousUrl.value(
        wantedPage
    );

    render("users_login", c);
}


/**
 *
 */
void Users::login_treat() {
    TREAT_PAGE();

    forms::users::Login form;
    form.load(context());
    
    const std::string username = form.username.value();

    // TODO maybe move that in the validate function of the form?
    if (!form.validate()) {
        set_message("Form didn't validate");
        go_back_to_previous_page();
        return;
    }

    if (
        usersModel->is_login_correct(
            username,
            form.password.value()
        )
    ) {
        set_current_username_and_id(
            username,
            usersModel->get_id_from_name<int>(username)
        );
        // we redirect to the page the user was before going
        // on the login page
        // TODO the message is not displayed try to see why
        // certainly due to successive redirection
        set_message("Login");
        redirect(
            form.previousUrl.value()
        );
    } else {
        set_message("Password incorrect");
        go_back_to_previous_page();
    } 

}


/**
 *
 */
void Users::register_new() {

    contents::users::RegisterNew c;
    init_content(c);


    render("users_register_new", c);
}


/**
 *
        // we redirect to the page the user was before going
        // on the login page
 */
void Users::register_new_treat() {
    TREAT_PAGE();

    forms::users::RegisterNew form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

    const std::string username = form.username.value();
    const std::string email = form.email.value();

    if (usersModel->username_exists(username)) {
        set_message(
            _("Username already taken")
        );
        go_back_to_previous_page();
        return;
    }

    if (usersModel->email_exists(email)) {
        set_message(
            _("Email already taken")
        );
        go_back_to_previous_page();
        return;
    }



    int userId = usersModel->add(
        username,
        form.password.value(),
        email 
    );
    if (userId >= 0) {
        //TODO add should return the id of the newly created user
        //     or -1 if not created
        set_current_username_and_id (
            username,
            userId
        );
        //TODO replace / by "ROOT_APPLICATION"
        redirect("/");
    } else {
        set_message(
            _("Unknown error")
        );
        go_back_to_previous_page();
    }
}


/**
 *
 */
void Users::change_password() {

    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    contents::users::ChangePassword c;
    init_content(c);


    render("users_change_password", c);
}


/**
 *
 */
void Users::change_password_treat() {

    TREAT_PAGE();
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    forms::users::ChangePassword form;
    form.load(context());

    // we  check that there's no empty field
    if (!form.validate()) {
        set_message(_("Your form is not valid")); 
        go_back_to_previous_page();
        return;
    }
    
    // we check that the old password is correct
    const std::string username = get_current_username();
    bool oldPasswordCorrect = usersModel->is_login_correct(
        username,
        form.oldPassword.value()
    );
    if (!oldPasswordCorrect) {
        set_message(_("Your previous password is not correct.")); 
        go_back_to_previous_page();
        return;
    }
    // we check that the user has entered the same new password twice
    const std::string newPassword = form.newPassword.value();
    const std::string newPasswordTwice = form.newPasswordTwice.value();
    if (newPassword != newPasswordTwice) {
        set_message(_("You haven't entered twice the same new password.")); 
        go_back_to_previous_page();
        return;
    }
    
    const bool changed = usersModel->change_password(
       username,
       newPassword
    );
    if (!changed) {
        set_message(_("Error while trying to update your password.")); 
        go_back_to_previous_page();
        return;
    } 
    set_message(_("Password updated successfully."));
    go_back_to_previous_page();

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
