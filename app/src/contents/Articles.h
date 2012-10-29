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


#ifndef TATOEBACPP_CONTENTS_ARTICLES_H
#define TATOEBACPP_CONTENTS_ARTICLES_H

#include "cppcms_skel/contents/content.h"

#include "contents/forms/edit.h"
//%%%NEXT_CONTENT_FORM_MARKER%%%

namespace contents {
namespace articles {

/**
 * @class Articles
 * @brief Base content for every action of Articles controller
 * @since 30 October 2012
 */
struct Articles : public BaseContent {
};

/**
 * @struct Delete
 * @since  30 October 2012
 * @brief 
 */
struct Delete : public Articles {

    Delete() {

    }

};

/**
 * @struct Show
 * @since  30 October 2012
 * @brief 
 */
struct Show : public Articles {

    Show() {

    }

};

/**
 * @struct Edit
 * @since  30 October 2012
 * @brief 
 */
struct Edit : public Articles {

    forms::articles::Edit editForm;

    /**
     * @brief Constructor
     */
    Edit() {
    }

};

/**
 * @struct Create
 * @since  30 October 2012
 * @brief 
 */
struct Create : public Articles {

    forms::articles::Create createForm;

    /**
     * @brief Constructor
     */
    Create() {
    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace articles
} //end of namespace contents

#endif
