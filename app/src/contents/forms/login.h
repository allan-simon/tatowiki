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


#ifndef TatoWiki_LOGIN
#define TatoWiki_LOGIN

#define _(X) cppcms::locale::translate((X))

#include <cppcms/form.h>

namespace forms{
namespace users {

/**
 * @struct login
 * @brief  @TODO
 * @since  30 October 2012
 *
 */
struct Login : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%
    /**
     * @brief To keep trace of the url we were in before
     *        landing on the login page
     *
     * @since 13 November 2012
     */
    cppcms::widgets::hidden previousUrl;
    
    /**
     * @brief The username with which we want to log in
     * @since 13 November 2012
     */
    cppcms::widgets::text username;
    
    /**
     * TODO write the doc
     * @since 13 November 2012
     */
    cppcms::widgets::password password;
    
    /**
     * TODO write the doc
     * @since 13 November 2012
     */
    cppcms::widgets::checkbox rememberMe;
    
    /**
     * TODO write the doc
     * @since 13 November 2012
     */
    cppcms::widgets::submit submit;
    

    /**
     * @brief Default constructor add all the fields to the form
     * define their names etc.
     */
    Login() {
        //%%%NEXT_WIDGET_ADD_MARKER%%%
        previousUrl.name("previousurl");
        previousUrl.value("");
        add(previousUrl);

        username.name("username");
        username.message(_("Username : "));
        username.attributes_string("class=\"input text\"");
        username.non_empty();
        add(username);

        password.name("password");
        password.message(_("Password : "));
        add(password);

        rememberMe.name("rememberMe");
        rememberMe.message(_("Remember Me"));
        add(rememberMe);
        

        submit.name("submit");
        submit.value(_("submit"));
        add(submit);


        password.non_empty();
    }
    



};


} // end of namespace users
}// end of namespace forms


#endif


