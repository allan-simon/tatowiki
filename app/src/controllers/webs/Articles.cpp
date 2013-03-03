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

#include <booster/log.h>
#include <cppcms_skel/generics/Config.h>

#include "Articles.h"


#include "contents/Articles.h"

#include "models/Articles.h"
#include "models/History.h"
//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


#include "generics/markdown.h"

//TODO certainly move this somewhere else
#define _(X) cppcms::locale::translate((X))

namespace controllers {
namespace webs {

Articles::Articles(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{

    dispatcher().assign("/remove/(.+)", &Articles::remove, this, 1);
    dispatcher().assign("/show/(.+)", &Articles::show, this, 1);

    dispatcher().assign("/edit/(.+)", &Articles::edit, this, 1);
    dispatcher().assign("/edit_treat", &Articles::edit_treat, this);

    dispatcher().assign("/create/(.+)", &Articles::create, this, 1);
    dispatcher().assign("/create_treat", &Articles::create_treat, this);
    dispatcher().assign("/show-all", &Articles::show_all, this);

    dispatcher().assign("/translate/(.+)", &Articles::translate, this, 1);
    dispatcher().assign("/translate_treat", &Articles::translate_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete




    articlesModel = new models::Articles();
    historyModel = new models::History();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Articles::~Articles() {
    delete articlesModel;
    delete historyModel;
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
}


/**
 *
 */
void Articles::show(std::string slug) {

    contents::articles::Show c;
    init_content(c);
    c.markdown = mymarkdown;

    std::string lang = get_interface_lang();

    c.cacheKey = lang + slug;
    
    c.article = articlesModel->get_from_lang_and_slug(
        lang,
        slug
    );
   
    // if the article does not exists we redirect to the
    // page to create one
    if (!c.article.exists()) {
        redirect(
            "/articles/create/" + slug
        );
        return;
    }


    c.translatedIn = articlesModel->get_group_of(
        c.article.id,
        c.article.groupId
    );
    render("articles_show", c);
}

/**
 *
 */
void Articles::edit(const std::string slug) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN();


    results::Article article = articlesModel->get_from_lang_and_slug(
        get_interface_lang(),
        slug
    );

    // if the articles does not exist we load the "create" form rather
    // than "edit" one
    if (!article.exists()) {
        redirect(
            "/articles/create/" + slug
        );
        return;
    }

    contents::articles::Edit c(article);
    init_content(c);

    render("articles_edit", c);
}


/**
 *
 */
void Articles::edit_treat() {
    TREAT_PAGE();
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    forms::articles::Edit form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
        return;
    }
    
    const std::string lang = get_interface_lang();
    const std::string slug = form.slug.value();
    const std::string title = form.title.value();
    const std::string content = form.content.value();
    articlesModel->edit_from_lang_and_slug(
        lang,
        slug,
        title,
        content
    );

    historyModel->add_version(
        lang,
        slug,
        title,
        content,
        get_current_user_id(),
        "" // TODO add something for the summary
    );

    // we invalidate the cache for this article
    cache().rise(lang+slug);

    // we show the edit articles if the user wants to 
    // save it
    if (form.saveAndView.value()) {
        redirect(
            "/articles/show/" + form.slug.value()
        );
    // we continue in edit mode if the user wants to save and continue
    // to edit
    } else if (form.saveAndContinue.value()) {
        redirect(
            "/articles/edit/" + form.slug.value()
        );
    } else {
        go_back_to_previous_page();
    }
}


/**
 *
 */
void Articles::create(std::string slug) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    results::Article article = articlesModel->get_from_lang_and_slug(
        get_interface_lang(),
        slug
    );

    // if the article exists there's no need to create it
    // we display it directly instead
    if (article.exists()) {
        //TODO use mapper instead
        redirect(
            "/articles/show/" + slug
        );
        return;
    }

    contents::articles::Create c(slug);
    init_content(c);

    render("articles_create", c);
}


/**
 *
 */
void Articles::create_treat() {
    TREAT_PAGE();
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    forms::articles::Create form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }
    
    const std::string lang = get_interface_lang();
    const std::string slug = form.slug.value();
    const std::string title = form.title.value();
    const std::string content = form.content.value();
    // we save in database the articles
    int articleId = articlesModel->create_from_lang_and_slug(
        lang,
        slug,
        title,
        content
    );

    if (articleId <= 0) {
        set_message(_("Error while trying to add the article"));
        go_back_to_previous_page();
        return;
    }

    // TODO add something to say that the article
    // as been created (and not simply that a "version"
    // has been added
    historyModel->add_version(
        lang,
        slug,
        title,
        content,
        get_current_user_id(),
        "" // TODO add something for the summary
    );


    // if save => display newly created articles
    if (form.saveAndView.value()) {
        redirect(
            "/articles/show/" + form.slug.value()
        );

    // if save and continue => turn now in edit mode
    } else if (form.saveAndContinue.value()) {
        redirect(
            "/articles/edit/" + form.slug.value()
        );
    } else {
        go_back_to_previous_page();
    }


}


/**
 *
 */
void Articles::remove(const std::string slug) {

    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    const bool success = articlesModel->remove(
        get_interface_lang(),
        slug
    );
    
    if (success) {
        set_message(_("The article has been removed"));
    } else {
        set_message(_("A problem occured while trying to remove"));
    }
    go_to_main_page();
}

/**
 *
 */
void Articles::show_all() {
    //TODO in the future would be better if paginated
    contents::articles::ShowAll c;
    init_content(c);

    c.articles = articlesModel->get_all();

    render("articles_show_all", c);
}

/**
 *
 */
void Articles::translate(const std::string slug) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    int articleToTranslateId = articlesModel->get_id_from_lang_and_slug(
        get_interface_lang(),
        slug
    );

    if (articleToTranslateId == ARTICLE_DOESNT_EXIST_ERROR) {
        set_message(_("The article you try to translate does not exist."));
        go_back_to_previous_page();
        return;
    }

    contents::articles::Translate c(slug);
    init_content(c);


    render("articles_translate", c);
}


/**
 *
 */
void Articles::translate_treat() {
    TREAT_PAGE();
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    forms::articles::Translate form;
    form.load(context());
    if (!form.validate()) {
        set_message(_("The form you've submitted is not valid"));
        go_back_to_previous_page();
    }

    
    const std::string origLang = get_interface_lang();
    const std::string origSlug = form.slug.value();
    const std::string translationSlug = form.translationSlug.value();
    const std::string translationLang = form.transLang.selected_id();
    const std::string title = form.title.value();
    const std::string content = form.content.value();


    int resultCode = articlesModel->translate_from_lang_and_slug(
       origLang,
       origSlug,
       translationLang,
       translationSlug,
       title,
       content
    );

    // TODO add something to say that the article
    // as been created (and not simply that a "version"
    // has been added
    // TODO also add something to keep trace of the
    //      translation link in the history 
    if (resultCode <= 0) {
        if (resultCode == ARTICLE_ALREADY_TRANSLATED_ERROR) {
            set_message(_("This article has already a translation in that language."));
        } else if (resultCode == ARTICLE_SAME_TRANSLATION_LANGUAGE_ERROR) {
            set_message(_("You can't translate an article in the same language."));
        } else {
            set_message(_("Error while trying to translate."));
        }
        go_back_to_previous_page();
        return;
    }
    historyModel->add_version(
        translationLang,
        translationSlug,
        title,
        content,
        get_current_user_id(),
        // TODO add something for the summary
        "translated from " + origLang + ":" + origSlug  
    );
    // we redirect to the article we've just added
    redirect(
        "http://" +
        translationLang +
        "." +
        Config::get_base_host() +
        "/articles/show/" + translationSlug
    );

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
