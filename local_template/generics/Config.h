/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Singletons
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef SHDICT_CONTENT_CONFIG_H
#define SHDICT_CONTENT_CONFIG_H

#include <map>
#include "generics/Singleton.h"

/**
 * Singleton class that store some value used in html generation
 * such as the path for css files etc.
 */
class Config : public Singleton<Config> {
    friend class Singleton<Config>;

    private:

        /**
         * Default constructor, do nothing for the moment
         */
        Config();

    public:
        /**
         * Store the path for css files
         */
        std::string cssPath;

        /**
         * Store the path for images files
         */
        std::string imgPath;

        /**
         * Store the root URL of the website
         */
        std::string webPath;


        /**
         * Store the path where the sqlite3 database is stored
         */
        std::string sqlite3Path;
};

#endif


