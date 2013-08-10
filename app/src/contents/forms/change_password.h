/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Forms
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_CHANGE_PASSWORD
#define TATOWIKI_CHANGE_PASSWORD


#include <cppcms/form.h>

namespace forms{
namespace users {

/**
 * @struct change_password
 * @brief  @TODO
 * @since  15 March 2013
 *
 */
struct ChangePassword : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%
    /**
     * @brief The old password to change
     */
    cppcms::widgets::password oldPassword;

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
    ChangePassword() {

        //%%%NEXT_WIDGET_ADD_MARKER%%%

        oldPassword.name("oldPassword");
        oldPassword.message(_("Old password"));
        oldPassword.non_empty();
        add(oldPassword);

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


} // end of namespace users
}// end of namespace forms


#endif


