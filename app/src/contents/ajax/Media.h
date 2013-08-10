/**
 * Copyright (C) 2012-2013 Allan SIMON (Sysko) <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @package  Contents
 *
 */

#ifndef TATOWIKI_CONTENTS_AJAX_MEDIA_H
#define TATOWIKI_CONTENTS_AJAX_MEDIA_H

#include <cppcms_skel/contents/AjaxContent.h>
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace ajax {
namespace media {

/**
 * @class Media Base content for every ajax action of Media controller
 * @since 18 June 2013
 */
struct Media : public cppcmsskel::contents::AjaxContent {
};

/**
 * @struct UploadImage
 * @since  18 June 2013
 */
struct UploadImage : public Media {

    std::string url;
};


//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace media
} // end of namespace ajax
} // end of namespace contents

#endif
