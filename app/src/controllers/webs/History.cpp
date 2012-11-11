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
#include "History.h"

#include "generics/markdown.h"

#include "contents/History.h"

#include "models/History.h"
//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

History::History(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{

    dispatcher().assign("/revert-to-version", &History::revert_to_version, this);
    dispatcher().assign("/show-version/.*/(\\w+)", &History::show_version, this, 1);

    dispatcher().assign("/diff-between", &History::diff_between, this);
    dispatcher().assign("/diff-between_treat", &History::diff_between_treat, this);
    dispatcher().assign("/all-versions-of/(.*)", &History::all_versions_of, this, 1);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete


    historyModel = new models::History();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
History::~History() {
    delete historyModel;
    //%%%NEXT_DEL_MODEL_CTRL%%%
}

/**
 *
 */
void History::revert_to_version() {

    contents::history::RevertToVersion c;
    init_content(c);


    render("history_revert_to_version", c);
}

/**
 *
 */
void History::show_version(const std::string versionStr) {

    contents::history::ShowVersion c;
    init_content(c);

    const int version = std::stoi(versionStr); 
    
    c.markdown = mymarkdown;
    c.articleVersion = historyModel->get_version(version);


    render("history_show_version", c);
}

/**
 *
 */
void History::diff_between() {

    contents::history::DiffBetween c;
    init_content(c);

    render("history_diff_between", c);
}


/**
 *
 */
void History::diff_between_treat() {

    forms::history::DiffBetween form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

}


/**
 *
 */
void History::all_versions_of(const std::string slug) {

    contents::history::AllVersionsOf c;
    init_content(c);
    c.slug = slug;
    //TODO test if article exists
    c.changes = historyModel->all_versions_of(
        session()["interfaceLang"],
        slug
    );

    render("history_all_versions_of", c);
}

// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
