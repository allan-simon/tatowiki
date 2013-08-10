/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef CONTROLLERS_WEBS_USERS_H
#define CONTROLLERS_WEBS_USERS_H

#include <cppcms_skel/controllers/webs/Controller.h>

//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace cppcmsskel {
namespace models {
    class Users;
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%%
}
}

namespace controllers {
namespace webs {
/**
 * @class Users
 * @brief Module that manages user
 * @since 30 October 2012
 */
class Users : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 30 October 2012
         */
        Users(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 30 October 2012
         */
        ~Users();

    private:
        /**
         * @brief TODO
         * @since %%MODEL_CTRL_TODAY%%
         */
        cppcmsskel::models::Users *usersModel;

        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%


        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void logout();

        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void login();

        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void login_treat();

        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void register_new();

        /**
         * @brief @TODO
         * @since 30 October 2012
         */
        void register_new_treat();

        /**
         * @brief Display a page that permits the user to change
         *        his password
         *
         * @since 15 March 2013
         */
        void change_password();

        /**
         * @brief Treat the form that permits the user to change
         *        his pasword
         *
         * @since 15 March 2013
         */
        void change_password_treat();

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace generics

#endif
