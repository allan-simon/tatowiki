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
 * @package  Apps
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
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
