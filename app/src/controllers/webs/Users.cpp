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

    dispatcher().assign("/register", &Users::register, this);
    dispatcher().assign("/register_treat", &Users::register_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete



    usersModel = new models::Users();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Users::~Users() {
    //%%%NEXT_DEL_MODEL_CTRL%%%
}

/**
 *
 */
void Users::logout() {

    contents::users::Logout c;
    init_content(c);


    render("users_logout", c);
}

/**
 *
 */
void Users::login() {

    contents::users::Login c;
    init_content(c);


    render("users_login", c);
}


/**
 *
 */
void Users::login_treat() {

    forms::users::Login form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


/**
 *
 */
void Users::register() {

    contents::users::Register c;
    init_content(c);


    render("users_register", c);
}


/**
 *
 */
void Users::register_treat() {

    forms::users::Register form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
