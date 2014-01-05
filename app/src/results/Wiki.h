/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2013 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  results
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

 #include <string>

namespace tatowiki {
namespace results {

    struct Logo {
        std::string url;
        unsigned height;
        unsigned width ;
        std::string text;
        bool isImage;
    };

    /**
     * @struct Wiki Structure used to contains the generic information
     *         about the current wiki
     * @since  15 September 2013
     */
    struct Wiki {
        std::string title;
        std::string copyright;
        Logo logo;
    };




} // end namespace results 
} // end namespace tatowiki

