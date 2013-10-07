/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Forms
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
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

        //TODO duplicate with change_brand.h
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


