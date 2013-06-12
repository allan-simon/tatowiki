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

#include <fstream>

#include <cppcms/session_interface.h>
#include <cppcms/http_file.h>

#include <cppcms_skel/models/Uploads.h>
#include <cppcms_skel/generics/Config.h>

#include "Media.h"
#include "contents/Media.h"

//%%%NEXT_INC_MODEL_CTRL_MARKER%%%

#ifndef _
#define _(X) cppcms::locale::translate(X)
#endif

#define MEDIA_FILES_BY_PAGE 50

namespace controllers {
namespace webs {

Media::Media(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{


    dispatcher().assign("/get/(.+\\.(png|PNG|jpeg|jpg|JPG|JPEG))", &Media::get, this, 1, 2);
    dispatcher().assign("/upload-image", &Media::upload_image, this);
    dispatcher().assign("/upload-image_treat", &Media::upload_image_treat, this);
    dispatcher().assign("/list-all", &Media::list_all, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete

    uploadsModel = new cppcmsskel::models::Uploads();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Media::~Media() {
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
    delete uploadsModel;
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

    std::string fileURL = uploadsModel->save(
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

/**
 *
 */
void Media::list_all() {

    contents::media::ListAll c(
        uploadsModel->list(MEDIA_FILES_BY_PAGE)
    );
    init_content(c);

    render("media_list_all", c);
}

/**
 *
 */
void Media::get(
    const std::string filename,
    const std::string extension
) {
    std::string absolutePath = Config::get_upload_folder() + filename;
    std::ifstream file(
        absolutePath.c_str()
    );
    if(!file.good()) {
       response().status(404);
       response().out() << "404";
    }
    else {
        response().content_type(
            mime_from_extension(extension)
        );
        response().out() << file.rdbuf();
    }

    file.close();

}

/**
 *
 */
const std::string Media::mime_from_extension(
    const std::string &extension
) {

    //TODO it can certainly be improved

    // if it's a jpeg image
    if (
        extension == "jpeg" ||
        extension == "jpg" ||
        extension == "JPEG" ||
        extension == "JPG"
    ) {
        return "image/jpeg";
    }

    // if it's a png image
    if (
        extension == "png" ||
        extension == "PNG"
    ) {
        return "image/png";
    }

    // when we don't know what is, RFC 2046 says it's for arbitrary binary
    // data
    return "application/octet-stream";
}



// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
