/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Form
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_CHANGE_USER_PASSWORD
#define TATOWIKI_CHANGE_USER_PASSWORD


#include <cppcms/form.h>

namespace forms{
namespace admin {

/**
 * Form that permits an admin to reset a user password
 * @struct change_user_password
 * @since  23 February 2014
 *
 */
struct ChangeUserPassword : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * name of user we're going to reset the password of
     */
    cppcms::widgets::text username;
    /**
     * @brief The new password a first time
     */
    cppcms::widgets::password newPassword;

    /**
     * @brief The new password a second time
     */
    cppcms::widgets::password newPasswordTwice;

    /**
     * @brief button to submit the form
     */
    cppcms::widgets::submit submit;

    /**
     * @brief Constructor
     */
    ChangeUserPassword() {

        //%%%NEXT_WIDGET_ADD_MARKER%%%

        username.name("username");
        username.message(_("Username"));
        username.non_empty();
        add(username);

        newPassword.name("newPassword");
        newPassword.message(_("New password"));
        newPassword.non_empty();
        add(newPassword);

        newPasswordTwice.name("newPasswordTwice");
        newPasswordTwice.message(_("New password again"));
        newPasswordTwice.non_empty();
        add(newPasswordTwice);

        add(submit);
        submit.name(_("Change password"));
        submit.value("submit");

    }


};


} // end of namespace admin
}// end of namespace forms


#endif


