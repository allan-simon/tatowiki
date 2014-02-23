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

#ifndef TATOWIKICONTROLLERS_WEBS_ADMIN_H
#define TATOWIKICONTROLLERS_WEBS_ADMIN_H

#include "cppcms_skel/controllers/webs/Controller.h"


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace models {
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%%
}

namespace controllers {
namespace webs {
/**
 * @class Admin @TODO add a description
 * @since 10 August 2013
 */
class Admin : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 10 August 2013
         */
        Admin(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 10 August 2013
         */
        ~Admin();

    private:
        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%

        /**
         * @brief @TODO add a description
         * @since 14 August 2013
         */
        void change_brand();

        /**
         * @brief @TODO add a description
         * @since 14 August 2013
         */
        void change_brand_treat();

        /**
         * @brief change the password of a given user
         * @since 23 February 2014
         */
        void change_user_password();

        /**
         * @brief change the password of a given user
         * @since 23 February 2014
         */
        void change_user_password_treat();

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers

#endif
