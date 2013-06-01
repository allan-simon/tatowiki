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
 * @package  Form
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */


#ifndef TATOWIKI_UPLOAD_IMAGE
#define TATOWIKI_UPLOAD_IMAGE


#include <cppcms/form.h>

namespace forms{
namespace media {

/**
 * @struct upload_image
 * @brief  @TODO
 * @since  19 May 2013
 *
 */
struct UploadImage : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    
    /**
     * @brief Will contain the uploaded file
     */
    cppcms::widgets::file image;

    /**
     * @brief button to submit the form
     */
    cppcms::widgets::submit submit;

    /**
     * @brief Constructor
     */
    UploadImage() {

        //%%%NEXT_WIDGET_ADD_MARKER%%%
    
        image.filename(
            booster::regex(".*\\.(jpg|jpeg|png|JPG|PNG)")
        );
        // magic for JPEG
        image.add_valid_magic("\xFF\xD8");
        // magic for PNG
        image.add_valid_magic("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A");

        image.limits(0, 1024*1024);
        image.non_empty();
        add(image);

        add(submit);
        submit.name(
            cppcms::locale::translate("submit")
        );
        submit.value("submit");
    }


};


} // end of namespace media
}// end of namespace forms


#endif


