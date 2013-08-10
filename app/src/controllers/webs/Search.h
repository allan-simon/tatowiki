/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */

#ifndef TATOWIKI_CONTROLLERS_WEBS_SEARCH_H
#define TATOWIKI_CONTROLLERS_WEBS_SEARCH_H

#include "cppcms_skel/controllers/webs/Controller.h"


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace models {
    class Search;
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%%
}

namespace controllers {
namespace webs {
/**
 * @class Search @TODO add a description
 * @since 18 June 2013
 */
class Search : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 18 June 2013
         */
        Search(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 18 June 2013
         */
        ~Search();

    private:
        /**
         * @brief TODO
         * @since %%MODEL_CTRL_TODAY%%
         */
        models::Search *searchModel;

        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%


        /**
         * @brief @TODO add a description
         * @since 18 June 2013
         */
        void simple();

        /**
         * @brief Page to display the result of a search request
         * @since 21 June 2013
         */
        void result();

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers

#endif
