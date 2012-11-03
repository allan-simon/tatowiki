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

#include <cppcms/session_interface.h>
#include "Articles.h"


#include "contents/Articles.h"

#include "models/Articles.h"
//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


#include "generics/markdown.h"

//TODO move it somewhere else
// HACK!

std::string mymarkdown(std::string const &s)
{
    int flags = mkd::no_pants;
    if(s.compare(0,10,"<!--toc-->")==0) {
        flags |= mkd::toc;
    }
    std::string html = markdown_to_html(
        s.c_str(),
        s.size(),flags
    );
    return html;
};



namespace controllers {
namespace webs {

Articles::Articles(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{

    dispatcher().assign("/remove", &Articles::remove, this);
    dispatcher().assign("/show/(.*)", &Articles::show, this, 1);

    dispatcher().assign("/edit/(.*)", &Articles::edit, this, 1);
    dispatcher().assign("/edit_treat", &Articles::edit_treat, this);

    dispatcher().assign("/create/(.*)", &Articles::create, this, 1);
    dispatcher().assign("/create_treat", &Articles::create_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete



    articlesModel = new models::Articles();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Articles::~Articles() {
    delete articlesModel;
    //%%%NEXT_DEL_MODEL_CTRL%%%
}

/**
 *
 */
void Articles::remove() {

    contents::articles::Remove c;
    init_content(c);


    render("articles_delete", c);
}

/**
 *
 */
void Articles::show(std::string slug) {

    contents::articles::Show c;
    init_content(c);
    c.markdown = mymarkdown;
    c.article = articlesModel->get_from_lang_and_slug(
        session()["interfaceLang"],
        slug
    );
   
    // if the article does not exists we redirect to the
    // page to create one
    if (!c.article.exists()) {
        response().set_redirect_header(
            "/articles/create/" + slug
        );
        return;
    }

    render("articles_show", c);
}

/**
 *
 */
void Articles::edit(const std::string slug) {


    results::Article article = articlesModel->get_from_lang_and_slug(
        session()["interfaceLang"],
        slug
    );

    // if the articles does not exist we load the "create" form rather
    // than "edit" one
    if (!article.exists()) {
        response().set_redirect_header(
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

    forms::articles::Edit form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
        return;
    }
    articlesModel->edit_from_lang_and_slug(
        session()["interfaceLang"],
        form.slug.value(),
        form.title.value(),
        form.content.value()
    );

    // we show the edit articles if the user wants to 
    // save it
    if (form.saveAndView.value()) {
        response().set_redirect_header(
            "/articles/show/" + form.slug.value()
        );
    // we continue in edit mode if the user wants to save and continue
    // to edit
    } else if (form.saveAndContinue.value()) {
        response().set_redirect_header(
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

    results::Article article = articlesModel->get_from_lang_and_slug(
        session()["interfaceLang"],
        slug
    );

    // if the article exists there's no need to create it
    // we display it directly instead
    if (article.exists()) {
        //TODO use mapper instead
        response().set_redirect_header(
            "/articles/show/" + form.slug.value()
        )
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

    forms::articles::Create form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
    }

    // we save in database the articles
    articlesModel->create_from_lang_and_slug(
        session()["interfaceLang"],
        form.slug.value(),
        form.title.value(),
        form.content.value()
    );

    // if save => display newly created articles
    if (form.saveAndView.value()) {
        response().set_redirect_header(
            "/articles/show/" + form.slug.value()
        );

    // if save and continue => turn now in edit mode
    } else if (form.saveAndContinue.value()) {
        response().set_redirect_header(
            "/articles/edit/" + form.slug.value()
        );
    } else {
        go_back_to_previous_page();
    }


}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
