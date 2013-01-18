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

#ifndef TATOWIKICONTROLLERS_WEBS_IMG_H
#define TATOWIKICONTROLLERS_WEBS_IMG_H

#include "cppcms_skel/controllers/webs/Controller.h"


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the// controller every time we modify a model. even though it does// not affect the controller
namespace models {
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%% 
}

namespace controllers {
namespace webs { 
/**
 * @class Img
 * @brief @TODO add a description
 * @since 19 January 2013
 */
class Img : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 19 January 2013
         */
        Img(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 19 January 2013
         */
        ~Img();

        /**
         * @brief Serve an image file
         *
         * @param imgFile The relative path of the image file
         * @param mimeType Mime Type of the image (either jpeg, png or gif)
         *
         * @since 18 January 2013
         */
         void serve_file(
            std::string imgFIle,
            std::string mimeType
        );



    private:
        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers

#endif
