/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Apps
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_H
#define TATOWIKI_H

/**
 * @file TatoWiki.h
 */
#include <map>

#include <cppcms/application.h>
#include <cppdb/frontend.h>

#include <cppcms_skel/controllers/webs/Img.h>
#include <cppcms_skel/controllers/webs/Css.h>
#include <cppcms_skel/controllers/webs/Js.h>
#include "controllers/webs/Articles.h"
#include "controllers/webs/Users.h"
#include "controllers/webs/History.h"
#include "controllers/webs/Media.h"
#include "controllers/webs/Search.h"
#include "controllers/webs/Admin.h"
//%%%NEXT_CONTROLLER_INCLUDE_MARKER%%%, do not delete
#include "controllers/webs/Pages.h"

/**
 * @namespace apps
 */
namespace apps {

/**
 * @class TatoWiki
 * Application class representing the website
 * All http request will be dispatched by this class
 */
class TatoWiki : public cppcms::application {

private:
    //%%%NEXT_MAIN_APP_CTRL_ATTR%%%
    controllers::webs::Admin admin;
    controllers::webs::Search search;
    controllers::webs::Media media;
    controllers::webs::Img img;
    controllers::webs::Css css;
    controllers::webs::Js  js;
    controllers::webs::History history;
    controllers::webs::Users users;
    controllers::webs::Articles articles;
    controllers::webs::Pages pages;

    /**
     * @brief Based on http header, we will try to guess the most suitable
     *        interface language
     *
     * @return The interface language code
     *
     * @since 5 September 2011
     *
     * @TODO for the moment it's a very naive algo
     */
    std::string get_default_interface_lang();

public:
    /**
     * Constructor
     * Will connect every controllers to their respective paths
     * @param serv
     */
	TatoWiki(cppcms::service &serv);

    /**
     * Method who receive all web requests
     * get the user language of interface from url
     * @param url : url asked by user
     */
	void main(std::string url);
};
}
#endif
