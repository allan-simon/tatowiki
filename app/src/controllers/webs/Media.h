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

#ifndef TATOWIKICONTROLLERS_WEBS_MEDIA_H
#define TATOWIKICONTROLLERS_WEBS_MEDIA_H

#include "cppcms_skel/controllers/webs/Controller.h"


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace cppcmsskel {
namespace models {
    class Uploads;
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%% 
}
}

namespace controllers {
namespace webs { 
/**
 * @class Media Class that contains all the pages to deal with
 *              uploading/managing uploaded files
 * @since 19 May 2013
 */
class Media : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 19 May 2013
         */
        Media(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 19 May 2013
         */
        ~Media();

    private:
        /**
         * @brief Pointer to the medial model to save file
         * @since 7 June 2013
         */
        cppcmsskel::models::Uploads* uploadsModel;

        /**
         * @brief Display a page containing a form to upload an image
         * @since 19 May 2013
         */
        void upload_image();

        /**
         * @brief Display nothing, only to treat a form that upload an image
         * @since 19 May 2013
         */
        void upload_image_treat();

        /**
         * @brief Paginated page that display in list the uploaded files
         * @TODO  it's not yet paginated
         * @since 13 June 2013
         */
        void list_all();

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers

#endif
