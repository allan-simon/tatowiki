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

#include <cppcms/session_interface.h>
#include "Media.h"


#include "contents/Media.h"

//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

Media::Media(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{


    dispatcher().assign("/upload-image", &Media::upload_image, this);
    dispatcher().assign("/upload-image_treat", &Media::upload_image_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete


    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Media::~Media() {
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
void Media::upload_image() {

    contents::media::UploadImage c;
    init_content(c);


    render("media_upload_image", c);
}


/**
 *
 */
void Media::upload_image_treat() {

    forms::media::UploadImage form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
