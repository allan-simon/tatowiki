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
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */


#ifndef TATOEBACPP_CONTENTS_USERS_H
#define TATOEBACPP_CONTENTS_USERS_H

#include <cppcms_skel/contents/content.h>

#include "contents/forms/login.h"
#include "contents/forms/register_new.h"
//%%%NEXT_CONTENT_FORM_MARKER%%%

namespace contents {
namespace users {

/**
 * @class Users
 * @brief Base content for every action of Users controller
 * @since 30 October 2012
 */
struct Users : public BaseContent {
};

/**
 * @struct Logout
 * @since  30 October 2012
 * @brief 
 */
struct Logout : public Users {

    Logout() {

    }

};

/**
 * @struct Login
 * @since  30 October 2012
 * @brief 
 */
struct Login : public Users {

    forms::users::Login loginForm;

    /**
     * @brief Constructor
     */
    Login() {
    }

};

/**
 * @struct RegisterNew
 * @since  30 October 2012
 * @brief 
 */
struct RegisterNew : public Users {

    forms::users::RegisterNew registerNewForm;

    /**
     * @brief Constructor
     */
    RegisterNew() {
    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace users
} //end of namespace contents

#endif
