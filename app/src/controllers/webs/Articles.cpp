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
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */

#include <cppcms/session_interface.h>
#include "Articles.h"


#include "contents/Articles.h"

#include "models/Articles.h"
//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

Articles::Articles(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{

    dispatcher().assign("/delete", &Articles::delete, this);
    dispatcher().assign("/show", &Articles::show, this);

    dispatcher().assign("/edit", &Articles::edit, this);
    dispatcher().assign("/edit_treat", &Articles::edit_treat, this);

    dispatcher().assign("/create", &Articles::create, this);
    dispatcher().assign("/create_treat", &Articles::create_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete



    articlesModel = new models::Articles();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Articles::~Articles() {
    //%%%NEXT_DEL_MODEL_CTRL%%%
}

/**
 *
 */
void Articles::delete() {

    contents::articles::Delete c;
    init_content(c);


    render("articles_delete", c);
}

/**
 *
 */
void Articles::show() {

    contents::articles::Show c;
    init_content(c);


    render("articles_show", c);
}

/**
 *
 */
void Articles::edit() {

    contents::articles::Edit c;
    init_content(c);


    render("articles_edit", c);
}


/**
 *
 */
void Articles::edit_treat() {

    forms::articles::Edit form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


/**
 *
 */
void Articles::create() {

    contents::articles::Create c;
    init_content(c);


    render("articles_create", c);
}


/**
 *
 */
void Articles::create_treat() {

    forms::articles::Create form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
