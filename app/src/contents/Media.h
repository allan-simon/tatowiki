/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */


#ifndef TATOWIKI_CONTENTS_MEDIA_H
#define TATOWIKI_CONTENTS_MEDIA_H

#include <cppcms_skel/results/Uploads.h>

#include "contents/BaseContent.h"
#include "contents/forms/upload_image.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace media {

/**
 * @class Media
 * @brief Base content for every action of Media controller
 * @since 19 May 2013
 */
struct Media : public ::tatowiki::contents::BaseContent {
};

/**
 * @struct UploadImage
 * @since  19 May 2013
 */
struct UploadImage : public Media {

    forms::media::UploadImage uploadImageForm;

    /**
     * @brief Constructor
     */
    UploadImage() {
    }

};

/**
 * @struct ListAll Contents used by Media::list_all()
 * @since  13 June 2013
 */
struct ListAll : public Media {

    cppcmsskel::results::Files files;

    ListAll() {
    }

    /**
     *
     */
     ListAll(cppcmsskel::results::Files filesParam) : files(filesParam) {

     }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace media
} //end of namespace contents

#endif
