/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Main
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
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
    Config::set_values(app.settings().at("TatoWiki"));

    tatowiki::Config::isPrivate(
        app.settings().at("TatoWiki.private").boolean()
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

