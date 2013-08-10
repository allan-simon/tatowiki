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

#ifndef TatoWiki_REGISTER_NEW
#define TatoWiki_REGISTER_NEW

#include <cppcms/form.h>

namespace forms{
namespace users {

/**
 * @struct RegisterNew
 * @brief  @TODO
 * @since  30 October 2012
 *
 */
struct RegisterNew : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * name of the user
     */
    cppcms::widgets::text username;
    /**
     * @brief his password
     */
    cppcms::widgets::password password;
    /**
     * @brief his email address
     */
    cppcms::widgets::email email;
    /**
     * @brief The answer to a question to check he's not a bot
     */
    cppcms::widgets::text quiz;
    /**
     * @brief Checkbox to say you've read and agreed the terms of use
     */
    cppcms::widgets::checkbox termsOfUse;
    /**
     *  @brief html submit button
     */
    cppcms::widgets::submit submit;

    /**
     * @brief Default constructor add all the fields to the form
     * define their names etc.
     */
    RegisterNew() {
        //%%%NEXT_WIDGET_ADD_MARKER%%%
        username.name("username");
        username.message(_("Username:"));
        username.non_empty();
        add(username);

        password.name("password");
        password.message(_("Password:"));
        password.non_empty();
        add(password);

        email.name("email");
        email.message(_("Email:"));
        add(email);

        quiz.message(_("Quizz:"));
        quiz.message(_("What are the first five letters of your email?"));
        quiz.name("quiz");
        add(quiz);

        termsOfUse.name("termsofuse");
        termsOfUse.message(_("I accept the terms of use."));
        add(termsOfUse);

        submit.value(_("Register"));
        submit.id("registerButton");
        add(submit);;

    }

    /**
     * To be sure that everything is correct, nothing is missing etc.
     */
    virtual bool validate() {
        return form::validate() &&
            termsOfUse.value() && //should have check the terms of use
            // the "captcha" test is to input the first four letters of
            // the email so we test if it's correct
            email.value().substr(0,5).compare(quiz.value()) == 0;
    }
};

} // end of namespace users
}// end of namespace forms

#endif

