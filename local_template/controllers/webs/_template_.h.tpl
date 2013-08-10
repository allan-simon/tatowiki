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

#ifndef TATOWIKICONTROLLERS_WEBS_%%CONTROLLER_INCLUDE%%_H
#define TATOWIKICONTROLLERS_WEBS_%%CONTROLLER_INCLUDE%%_H

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
 * @class %%CONTROLLER_NAME%% %%CONTROLLER_DESCRIPTION%%
 * @since %%CONTROLLER_TODAY%%
 */
class %%CONTROLLER_NAME%% : public Controller {
    public:
        /**
         * @brief Constructor
         * @since %%CONTROLLER_TODAY%%
         */
        %%CONTROLLER_NAME%%(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since %%CONTROLLER_TODAY%%
         */
        ~%%CONTROLLER_NAME%%();

    private:
        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers

#endif
