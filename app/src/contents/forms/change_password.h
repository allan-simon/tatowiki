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
 * @package  Form
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
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


