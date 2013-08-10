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

#ifndef TATOWIKICONTROLLERS_WEBS_MEDIA_H
#define TATOWIKICONTROLLERS_WEBS_MEDIA_H

#include "cppcms_skel/controllers/webs/Controller.h"


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace cppcmsskel {
namespace models {
    class Uploads;
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%%
}
}

namespace controllers {
namespace webs {
/**
 * @class Media Class that contains all the pages to deal with
 *              uploading/managing uploaded files
 * @since 19 May 2013
 */
class Media : public Controller {
    public:
        /**
         * @brief Constructor
         * @since 19 May 2013
         */
        Media(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 19 May 2013
         */
        ~Media();

    private:
        /**
         * @brief Pointer to the medial model to save file
         * @since 7 June 2013
         */
        cppcmsskel::models::Uploads* uploadsModel;

        /**
         * @brief Display a page containing a form to upload an image
         * @since 19 May 2013
         */
        void upload_image();

        /**
         * @brief Display nothing, only to treat a form that upload an image
         * @since 19 May 2013
         */
        void upload_image_treat();

        void upload_image_ajax();
        /**
         * @brief Paginated page that display in list the uploaded files
         * @TODO  it's not yet paginated
         * @since 13 June 2013
         */
        void list_all();

        /**
         * @brief Not a page, send the requested file
         *        Note: only for testing purpose, in production use your
         *        web server to server directly files
         *
         * @TODO  add a test to not work if in 'production'
         *
         * @param filename  Name of the file to serve
         * @param extension Extension of the file (i.e 3/4 last letters)
         *
         * @since 13 June 2013
         */
        void get(
            const std::string filename,
            const std::string extension
        );

        /**
         * @brief Utility function, get the MIME type from the extension
         *
         * @TODO maybe move it to cppcms_skel
         *
         * @param extension Extension of the file (i.e 3/4 last letters)
         *
         * @since 13 June 2013
         */
        const std::string mime_from_extension(
            const std::string &extension
        );


// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers

#endif
