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

#include "History.h"

#include "generics/markdown.h"

#include "contents/History.h"

#include "models/History.h"
#include "models/Articles.h"

#define _(X) cppcms::locale::translate((X))
//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

History::History(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{

    dispatcher().assign("/revert-to-version/(.*)/(\\d+)", &History::revert_to_version, this, 1, 2);
    dispatcher().assign("/show-version/(\\d+)", &History::show_version, this, 1);

    dispatcher().assign("/diff-between", &History::diff_between, this);
    dispatcher().assign("/diff-between_treat", &History::diff_between_treat, this);
    dispatcher().assign("/all-versions-of/(.*)", &History::all_versions_of, this, 1);
    dispatcher().assign("/recent-changes", &History::recent_changes, this);
    dispatcher().assign("/show-diff-between/(\\d+)/(\\d+)/(\\d+)", &History::show_diff_between, this,1,2,3);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete


    historyModel = new models::History();
    articlesModel = new models::Articles();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
History::~History() {
    delete historyModel;
    delete articlesModel;
    //%%%NEXT_DEL_MODEL_CTRL%%%
}

/**
 *
 */
void History::revert_to_version(
    const std::string slug,
    const std::string versionStr 
) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    const int version = std::stoi(versionStr); 
    results::ArticleVersion articleVersion = historyModel->get_version(
        version
    );

    if (articleVersion.exists()) {

        articlesModel->edit_from_lang_and_slug(
            articleVersion.article.lang,
            slug,
            articleVersion.article.title,
            articleVersion.article.content
        );

        const std::string summary = (cppcms::locale::format(_(
            "Revert article to version {1}" 
        )) % version).str();

        historyModel->add_version(
            articleVersion.article,
            get_current_user_id(),
            summary
        );
        // we invalidate the cache for this article
        cache().rise(
            articleVersion.article.lang + slug
        );

    }

    //TODO: add a message to say if the revert has been done 
    //      or not
    redirect(
        "/articles/show/" + slug
    );
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


    int articleToTranslateId = articlesModel->get_id_from_lang_and_slug(
        get_interface_lang(),
        slug
    );
    if (articleToTranslateId == ARTICLE_DOESNT_EXIST_ERROR) {
        set_message(_("You can't see the history of this article, because this article does not exist."));
        go_back_to_previous_page();
        return;
    }


    contents::history::AllVersionsOf c;
    init_content(c);
    c.articleId = articleId;
    c.slug = slug;
    c.changes = historyModel->all_versions_of(
        get_interface_lang(),
        slug
    );

    render("history_all_versions_of", c);
}

/**
 *
 */
void History::recent_changes() {

    contents::history::RecentChanges c;
    init_content(c);
    c.articlesVersions = historyModel->recent_changes();

    render("history_recent_changes", c);
}

/**
 *
 */
void History::show_diff_between(
    const std::string articleIdStr,
    const std::string oldVersionStr,
    const std::string newVersionStr

) {

    const int articleId = std::stoi(articleIdStr);
    const int oldVersion = std::stoi(oldVersionStr);
    const int newVersion = std::stoi(newVersionStr);
    
    results::Diff diff = historyModel->diff(
        articleId,
        oldVersion,
        newVersion
    );
    
    if (diff.newContent.empty() || diff.oldContent.empty()) {
        set_message(_(
            "One of this two versions id maybe does not correspond to "
            "a version associated to this article"
        ));
        go_back_to_previous_page();
        return;
    }

    contents::history::ShowDiffBetween c;
    init_content(c);
    c.slug = articlesModel->get_from_id(articleId).slug;
    c.diff = diff; 
    c.oldVersion = oldVersion;
    c.newVersion = newVersion;

    render("history_show_diff_between", c);
}

// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
