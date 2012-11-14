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

        /**
         * @brief Return the id of the user having the given name
         *
         * @param string username User's name of whom we want the id
         *
         * @return mix We can return the id as a string or as an int
         */
        template <class T> T get_id_from_name(
            const std::string &username
        );


        /**
         * @brief Test if the pair login/pass exists in the database
         *
         * @param string login The username
         * @param string pass  Password entered by the user in the form
         *
         * @return bool True if the pair login/pass exists
         *
         * @since 13 November 2012
         *
         */        
        bool is_login_correct(
            const std::string &login,
            const std::string &pass
        );         
 
                   
        /**        
         * @brief Add a new user with the given login/pass/mail
         *
         * @param string login The user's name on the website
         * @param string pass  His password
         * @param string email His email address
         *
         * @return bool False if the user can't be added
         *              (login already taken etc.)
         *
         * @since 13 November 2012
         */        
        bool add(
            const std::string &login,
            const std::string &pass,
            const std::string &email
        );         
                   


};


/**
* @brief          User to retrieve the identifier of a given user
* @TODO           Throw an exception when the user does not exists
*
* @tparam T       Type under which we want the id (int or std::string)
* @param username Name of the user want the id of
* 
*
* @return         The id in the requested type 
*/
template <class T> T models::Users::get_id_from_name(
    const std::string &username
) {
    cppdb::statement getIdFromUsername = sqliteDb.prepare(
        "SELECT id FROM users WHERE username = ? LIMIT 1"
    );
    getIdFromUsername.bind(username);
    cppdb::result res = getIdFromUsername.row();

    T userId;
    res.fetch(0, userId);
    getIdFromUsername.reset();
    
    return userId;

}


} // end namespace models 

#endif
