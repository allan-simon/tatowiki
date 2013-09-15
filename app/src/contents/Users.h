/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOEBACPP_CONTENTS_USERS_H
#define TATOEBACPP_CONTENTS_USERS_H


#include "contents/BaseContent.h"
#include "contents/forms/login.h"
#include "contents/forms/register_new.h"
#include "contents/forms/change_password.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace users {

/**
 * @class Users
 * @brief Base content for every action of Users controller
 * @since 30 October 2012
 */
struct Users : public ::tatowiki::contents::BaseContent {
};

/**
 * @struct Logout
 * @since  30 October 2012
 */
struct Logout : public Users {

    Logout() {

    }

};

/**
 * @struct Login Form to log in
 * @since  30 October 2012
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
 */
struct RegisterNew : public Users {

    forms::users::RegisterNew registerNewForm;

    /**
     * @brief Constructor
     */
    RegisterNew() {
    }

};

/**
 * @struct ChangePassword
 * @since  15 March 2013
 */
struct ChangePassword : public Users {

    forms::users::ChangePassword changePasswordForm;

    /**
     * @brief Constructor
     */
    ChangePassword() {
    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace users
} //end of namespace contents

#endif
