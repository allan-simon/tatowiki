/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2013 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_CONTENTS_ADMIN_H
#define TATOWIKI_CONTENTS_ADMIN_H

#include "cppcms_skel/contents/content.h"

//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace admin {

/**
 * @class Admin
 * @brief Base content for every action of Admin controller
 * @since 10 August 2013
 */
struct Admin : public BaseContent {
};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace admin
} //end of namespace contents

#endif
