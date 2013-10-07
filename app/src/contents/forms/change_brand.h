/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2013 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Form
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_CHANGE_BRAND
#define TATOWIKI_CHANGE_BRAND

#define _(X) cppcms::locale::translate((X))

#include <cppcms/form.h>

namespace forms{
namespace admin {

/**
 * @struct change_brand TODO description
 * @since  14 August 2013
 *
 */
struct ChangeBrand : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * @brief button to submit the form
     */
    cppcms::widgets::submit submit;

    /**
     * @brief Will contain the brand image
     */
    cppcms::widgets::file image;

    /**
     * checkbox to chose if we want the brand to be an image
     * if checked we use the uploaded image, and the text for the
     * alt attribute
     *
     * @since 21 September 2013
     */
    cppcms::widgets::checkbox useImage;

    /**
     * The name of the brand, either displayed directly or used as an alt
     * text if we use an image
     *
     * @since 21 September 2013
     */
    cppcms::widgets::text brandText;


    /**
     * @brief Constructor
     */
    ChangeBrand() {

        //%%%NEXT_WIDGET_ADD_MARKER%%%

        //TODO duplicate with upload_image.h
        image.filename(
            booster::regex(".*\\.(jpg|jpeg|png|JPG|PNG)")
        );
        // magic for JPEG
        image.add_valid_magic("\xFF\xD8");
        // magic for PNG
        image.add_valid_magic("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A");

        image.limits(0, 1024*1024);
        image.message(_("Brand's image"));
        image.non_empty();


        brandText.name("brandText");
        brandText.message(_("Brand:"));
        brandText.attributes_string("class=\"input text\"");
        brandText.non_empty();
        add(brandText);

        useImage.name("useImage");
        useImage.message("Use an image: ");
        add(useImage);



        add(submit);
        submit.name(_("submit"));
        submit.value("submit");
    }


};


} // end of namespace admin
}// end of namespace forms


#endif


