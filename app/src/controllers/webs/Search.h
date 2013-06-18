/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>g
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
 * @author   Allan SIMON <allan.simon@supinfo.com>g
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */

#ifndef TATOWIKICONTROLLERS_WEBS_SEARCH_H
#define TATOWIKICONTROLLERS_WEBS_SEARCH_H

#include "cppcms_skel/controllers/webs/Controller.h"


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace models {
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%%g
}

namespace controllers {
namespace webs {g
/**
 * @class Search @TODO add a description
 * @since 18 June 2013
 */
class Search : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 18 June 2013
         */
        Search(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 18 June 2013
         */
        ~Search();

    private:
        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers

#endif
