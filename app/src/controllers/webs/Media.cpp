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
#include <cppcms/http_file.h>

#include <cppcms_skel/models/Media.h>
#include "Media.h"


#include "contents/Media.h"

//%%%NEXT_INC_MODEL_CTRL_MARKER%%%

#ifndef _
#define _(X) cppcms::locale::translate(X)
#endif

namespace controllers {
namespace webs {

Media::Media(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{


    dispatcher().assign("/upload-image", &Media::upload_image, this);
    dispatcher().assign("/upload-image_treat", &Media::upload_image_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete

    mediaModel = new cppcmsskel::models::Media();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Media::~Media() {
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
    delete mediaModel;
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
    form.image.load(context());
    if (!form.validate()) {
        if (!form.image.validate()) {
            add_error(_(
                "Please check your image type (we only accept "
                "jpeg/png images) or size ( < 1MB)"
            )); 
        }
        go_back_to_previous_page();
        return;
    }
    
    std::string fileURL = mediaModel->save_media(
        form.image.value()
    );
    if (fileURL.empty()) {
        add_error(_(
            "Internal error while trying to upload the file."
            "If you see this message again, try to contact an"
            " administrator"
        ));
        go_back_to_previous_page();
        return;
    }
    const std::string fileUploaded = (cppcms::locale::format(
        _("File uploaded successfully. at this address: {1} ")
    ) % fileURL).str();

    add_success(fileUploaded);
    go_back_to_previous_page();

}

// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
