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


#ifndef TATOWIKI_CONTENTS_%%CONTROLLER_INCLUDE%%_H
#define TATOWIKI_CONTENTS_%%CONTROLLER_INCLUDE%%_H

#include "cppcms_skel/contents/content.h"

//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace %%CONTROLLER_NS%% {

/**
 * @class %%CONTROLLER_NAME%%
 * @brief Base content for every action of %%CONTROLLER_NAME%% controller
 * @since %%CONTROLLER_TODAY%%
 */
struct %%CONTROLLER_NAME%% : public BaseContent {
};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace %%CONTROLLER_NS%%
} //end of namespace contents

#endif
