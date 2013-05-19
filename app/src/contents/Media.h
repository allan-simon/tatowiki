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
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */


#ifndef TATOWIKI_CONTENTS_MEDIA_H
#define TATOWIKI_CONTENTS_MEDIA_H

#include "cppcms_skel/contents/content.h"

#include "contents/forms/upload_image.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace media {

/**
 * @class Media
 * @brief Base content for every action of Media controller
 * @since 19 May 2013
 */
struct Media : public BaseContent {
};

/**
 * @struct UploadImage
 * @since  19 May 2013
 * @brief 
 */
struct UploadImage : public Media {

    forms::media::UploadImage uploadImageForm;

    /**
     * @brief Constructor
     */
    UploadImage() {
    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace media
} //end of namespace contents

#endif
