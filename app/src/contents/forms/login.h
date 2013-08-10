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
        username.message(_("Username :"));
        username.attributes_string("class=\"input text\"");
        username.non_empty();
        add(username);

        password.name("password");
        password.message(_("Password :"));
        add(password);

        rememberMe.name("rememberMe");
        rememberMe.message(_("Remember me"));
        add(rememberMe);


        submit.name("submit");
        submit.value(_("Log in"));
        add(submit);


        password.non_empty();
    }




};


} // end of namespace users
}// end of namespace forms


#endif


