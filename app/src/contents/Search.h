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


#ifndef TATOWIKI_CONTENTS_SEARCH_H
#define TATOWIKI_CONTENTS_SEARCH_H

#include "cppcms_skel/contents/content.h"

#include "contents/forms/simple.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace contents {
namespace search {

/**
 * @class Search Base content for every action of Search controller
 * @since 18 June 2013
 */
struct Search : public BaseContent {
};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace search
} //end of namespace contents

#endif
