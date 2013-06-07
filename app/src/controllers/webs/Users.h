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
