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
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */


#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <cppdb/frontend.h>
#include <cppcms/util.h>
#include <cppcms/crypto.h>
#include <booster/posix_time.h>

#include "models/Users.h"

using namespace cppcms::crypto;

namespace models {

/**
 *
 */
Users::Users() :
    SqliteModel()
{
}


/**
 *
 */
bool Users::is_login_correct(
    const std::string &login,
    const std::string &pass
) {
    
    cppdb::statement checkPasswd = sqliteDb.prepare(
        "SELECT 1 FROM users "
        "WHERE username = ? AND password = ? LIMIT 1"
    );
    const std::string passHashed = cppcms::util::md5hex(pass);
    checkPasswd.bind(login);
    checkPasswd.bind(passHashed);
    cppdb::result res = checkPasswd.row();
    int checkresult = 0;
    res.fetch(0,checkresult);

    // Don't forget to reset statement
    checkPasswd.reset();

    if (checkresult == 1 ) {
        return true;
    }
    return false;

}

/**
 *
 */
bool Users::add(
    const std::string &login,
    const std::string &pass,
    const std::string &email
) {       

    
    cppdb::statement addUser = sqliteDb.prepare(
        "INSERT INTO users(username, password, email, since)"
        "VALUES(?,?,?,?)"
    );

    const std::string passHashed = cppcms::util::md5hex(pass);
    addUser.bind(login);
    addUser.bind(passHashed);
    std::cout << cppcms::util::md5hex(pass) << std::endl;
    addUser.bind(email);
    addUser.bind(
        booster::ptime::now().get_seconds()
    );
          
    try {
        addUser.exec();    
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        addUser.reset();
        return false;
    }
    addUser.reset();
    return true;
}     


} // end namespace models


