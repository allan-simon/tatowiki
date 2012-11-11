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
 * @category Tatoeba wiki
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */

#ifndef TatoWiki_USERS
#define TatoWiki_USERS



#include <cppcms_skel/models/SqliteModel.h>
namespace models {


/**
 * @class Users
 * 
 * @brief @TODO
 * @since 30 October 2012       
 *
 */
class Users : public SqliteModel {
    public:
        /**
         * @brief Constructor
         * @since 30 October 2012
         */
        Users();

};

} // end namespace models 

#endif
