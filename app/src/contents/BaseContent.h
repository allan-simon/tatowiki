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


#ifndef TATOWIKI_CONTENTS_BASECONTENT_H
#define TATOWIKI_CONTENTS_BASECONTENT_H

#include <cppcms_skel/contents/content.h>

#include "results/Wiki.h"


namespace tatowiki {
namespace contents {

struct BaseContent : public :: contents::BaseContent {

    results::Wiki wiki;

};


} // end namespace contents
} // end namespace tatowiki

#endif
