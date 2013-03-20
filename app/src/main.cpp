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
 * @package  Main
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */


#include <iostream>


#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppdb/frontend.h>
#include <cppcms/json.h>
#include <cppcms_skel/generics/Config.h>
#include <cppcms_skel/generics/Languages.h>

#include "generics/Config.h"
#include "TatoWiki.h"
#include "controllers/webs/Articles.h"


using namespace std;
using namespace cppcms;

int main(int argc,char ** argv)
{
    //TODO send notice message to logs instead of cout

    service app(argc, argv);
    /*load some conf defined variables*/

    Config::get_instance()->sqlite3Path = app.settings().get<string>(
        "TatoWiki.sqlite3.path"
    );

    Config::set_base_host(
        app.settings().get<string>(
            "TatoWiki.baseHost"
        )
    );

    Config::set_css_path(
        app.settings().get<string>(
            "TatoWiki.cssPath"
        )
    );

    Config::set_img_path(
        app.settings().get<string>(
            "TatoWiki.imgPath"
        )
    );

    Config::set_js_path(
        app.settings().get<string>(
            "TatoWiki.jsPath"
        )
    );


    Config::set_inner_css_folder(
        app.settings().get<string>(
            "TatoWiki.innerCssFolder"
        )
    );

    Config::set_inner_img_folder(
        app.settings().get<string>(
            "TatoWiki.innerImgFolder"
        )
    );

    Config::set_inner_js_folder(
        app.settings().get<string>(
            "TatoWiki.innerJsFolder"
        )
    );



    tatowiki::Config::set_lang_to_main_pages(
        app.settings().at("TatoWiki.mainPages").array()
    );

    /* we generate the main pages of the wiki if they're not there */
    cout << "[NOTICE] database check" << endl;
    controllers::webs::Articles::generate_main_pages(
        tatowiki::Config::get_lang_to_main_pages()
    );

    /*load the languages*/
    Languages::get_instance();
    Languages::get_instance()->init(
        app.settings().at("TatoWiki.languages").array(),
        app.settings().at("TatoWiki.interfacelangs").array()
    );
        
    //singletons::ActionId::get_instance();
    /*instantiate the website application*/
    cout << "[NOTICE] website to be launched" << endl;

    //booster::intrusive_ptr<apps::Tatoeba> tatoApp = new apps::Tatoeba(app);


    app.applications_pool().mount(
        cppcms::applications_factory<apps::TatoWiki>()
    );
    /*launch it */
    cout << "[NOTICE] website launched" << endl;
    app.run();
    cout << "[NOTICE] website stopped" << endl;

    /*time to destroy all the singletons*/
    //SearchEngine::kill();
    Languages::kill();
    Config::kill();
    tatowiki::Config::kill();
}

