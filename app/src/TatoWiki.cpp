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


#include <iostream>
#include <string>

#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/http_context.h>
#include <cppcms/session_interface.h>


#include <cppcms_skel/generics/Languages.h>

#include "TatoWiki.h"


// @TODO move the default language in the configuration
// file, so that it can easily changed without recompiling

#define DEFAULT_INTERFACE_LANG "en"

namespace apps {

/**
 *
 */
TatoWiki::TatoWiki(cppcms::service &serv) :
    cppcms::application(serv),
    //%%%NEXT_MAIN_APP_CTRL_CONSTRUCT_MARKER%%%
    search(serv),

    media(serv),
    
    img(serv),
    
    css(serv),
    
    js(serv),
    
    history(serv),
    
    users(serv),
    
    articles(serv),
    
    pages(serv)
{

    //add(sentencesApi, "^/api/sentences(.*)", 1);
    //NOTE important to add the page controller at the end
    //as its regexp is more global

    //add(#controller#,#mount_point#,1);

    add(articles,"^/articles(.*)",1);
    add(users,"^/users(.*)",1);
    add(history,"^/history(.*)",1);
    add(css,"^/css(.*)",1);
    add(js,"^/js(.*)",1);
    add(img,"^/img(.*)",1);
    add(media,"^/media(.*)",1);
    add(search,"^/search(.*)",1);
    //%%%NEXT_CONTROLLER_DISPATCHER_MARKER%%%, do not delete
    add(pages, "/(.*)", 1);


}

/**
 *
 */


void TatoWiki::main(std::string url) {
    
    std::string interfaceLang("");

    std::string serverName = request().http_host();
    std::string subdomain = serverName.substr(
        0,
        serverName.find('.')
    );
    

    // NextGen url "lang.wiki.tatoeba.org/url"
    // at the difference of tatoeba, here it's more likely that if someone share
    // with you en.wiki.tatoeba.org/something that he wanted you to see it in that
    // version, so the language in the URL is the one kept
    if (Languages::get_instance()->is_interface_lang(subdomain)) {
        interfaceLang = subdomain;
        session()["interfaceLang"] = interfaceLang ;
        // we set the locale in which the page will be generated
        context().locale(
            Languages::get_instance()->get_locale_from_lang(interfaceLang)
        );

        // and we call the appropriate controller
        application::main(url);

    // if no language set in the URL we take the default one using various
    // methods and we redirect
    } else {
        interfaceLang = get_default_interface_lang();
        response().set_redirect_header(
            "http://" + interfaceLang + "." +
            serverName +
            url
        );
    }


    
}

/**
 * 
 */
std::string TatoWiki::get_default_interface_lang() {
    
    std::string acceptedLanguage = request().http_accept_language();
       
    size_t size = acceptedLanguage.size(); 
    // if the browser has sent no header indicating what is its prefered
    // language
    if (size == 0) {
        return DEFAULT_INTERFACE_LANG;
    }

    std::string lang;
   
     
    if (size == 2 || size == 3) {
        lang = acceptedLanguage;
    } else  {
        lang = acceptedLanguage.substr(0,2);
    }

    // if this language is part of the supported languages
    if (Languages::get_instance()->is_interface_lang(lang)) {
        return lang;
    } 
    
    return DEFAULT_INTERFACE_LANG;
}



} // namespace apps
