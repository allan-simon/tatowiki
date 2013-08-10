/**
 * Tatoeba wiki  Wiki made with cppcmsskel
 *
 * Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category Tatoeba wiki
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @link     https://github.com/allan-simon/tatowiki
 */


#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <cppdb/frontend.h>


#include "models/History.h"


namespace models {

/**
 *
 */
History::History() :
    SqliteModel()
{
}


/**
 *
 */
bool History::add_version(
    const results::Article &article,
    const int userId,
    const std::string &summary = ""

) {
    cppdb::statement addVersion = sqliteDb.prepare(
        "INSERT INTO history("
        "    article_id,"
        "    title,"
        "    content,"
        "    lang,"
        "    slug,"
        "    user_id,"
        "    summary,"
        "    version"
        ") VALUES ("
        "    ?,"
        "    ?,"
        "    ?,"
        "    ?,"
        "    ?,"
        "    ?,"
        "    ?,"
        // COALESCE = either we do version = version + 1 or
        // version = 1 (1+0) if no previous version
        "    1 + COALESCE("
        "       (SELECT max(version) FROM history),"
        "       0"
        "    )"
        ")"
    );
    // insert part
    addVersion.bind(article.id);
    addVersion.bind(article.title);
    addVersion.bind(article.content);
    addVersion.bind(article.lang);
    addVersion.bind(article.slug);
    addVersion.bind(userId);
    addVersion.bind(summary);

    try {
        addVersion.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what();
        addVersion.reset();
        return false;
    }
    addVersion.reset();
    return true;
}

/**
 *
 */
int History::get_last_version_id_of(
    const int articleId
) {
    cppdb::statement statement = sqliteDb.prepare(
        "SELECT "
        "   MAX(version) as last_version "
        "FROM history "
        "WHERE "
        "   article_id = ?"
    );
    statement.bind(articleId);
   
    cppdb::result res = statement.row();

    int lastVersion = NO_HISTORY_FOR_ARTICLE_ERROR;
    if (!res.empty()) {
        lastVersion = res.get<int>("last_version");
    }
    statement.reset();

    return lastVersion; 

}

/**
 *
 */
results::Changes History::all_versions_of(
    const std::string &lang,
    const std::string &slug
) {

    cppdb::statement allVersionOf = sqliteDb.prepare(
        "SELECT "
        "   version, "
        "   edit_time, "
        "   summary, "
        "   user_id, "
        "   username "
        "FROM history "
        "JOIN users ON (history.user_id = users.id) "
        "WHERE "
        "   lang = ? "
        "   AND slug = ?"  
        "ORDER BY edit_time DESC"
    );
    allVersionOf.bind(lang);
    allVersionOf.bind(slug);


    results::Changes changes;
    changes.newestId = -1;
    changes.oldestId = -1;
    
    cppdb::result res = allVersionOf.query();
    while (res.next()) {
    
        int version = res.get<int>("version");

        results::Change tmpChange(
            version,
            res.get<unsigned int>("edit_time"),
            res.get<std::string>("summary"),
            res.get<std::string>("username"),
            res.get<int>("user_id"),
            changes.oldestId
        );

        // we change newestId only one time
        if (changes.newestId == -1) {
           changes.newestId = version; 
        }
        // we set oldest to the last known version
        changes.oldestId = version;
        
        // we set the "previoustVersion" of the change we've 
        // added at the previous iteration to the current version
        if (!changes.empty()) {
            changes.back().previousVersion = version;
        }
        
        changes.push_back(tmpChange);
    }
    allVersionOf.reset();
    return changes;

}

/**
 *
 */
results::ArticleVersion History::get_version(const int version) {

    cppdb::statement getVersion = sqliteDb.prepare(
        "SELECT "
        "    article_id,"
        "    title,"
        "    content,"
        "    lang,"
        "    slug,"
        "    summary,"
        "    version "
        "FROM history "
        "WHERE version = ?;"
    );
    getVersion.bind(version); 

    cppdb::result res = getVersion.row();
    results::ArticleVersion articleVersion;

    if (!res.empty()) {
        articleVersion.article.id = res.get<int>("article_id");
        articleVersion.article.title = res.get<std::string>("title");
        articleVersion.article.content = res.get<std::string>("content");
        articleVersion.article.lang = res.get<std::string>("lang");
        articleVersion.article.slug = res.get<std::string>("slug");

        articleVersion.change.summary = res.get<std::string>("summary");
        articleVersion.change.version = res.get<int>("version");
    } else {
        articleVersion.change.version = 0;
    }
    getVersion.reset();
    return articleVersion;
}

/**
 *
 */
results::ArticlesVersions History::recent_changes(
    const int number
) {

    cppdb::statement recentChanges = sqliteDb.prepare(
        "SELECT "
        "   article_id,"
        "   lang, "
        "   slug, "
        "   title,"
        "   version, "
        "   edit_time, "
        "   summary, "
        "   user_id, "
        "   username "
        "FROM history "
        "JOIN users ON (history.user_id = users.id) "
        "ORDER BY edit_time DESC "
        "LIMIT ?"
    );

    recentChanges.bind(number);
    cppdb::result res = recentChanges.query();
    results::ArticlesVersions articlesVersions;
    while (res.next()) {
        results::ArticleVersion tmpArticleVersion;
        
        tmpArticleVersion.change = results::Change(
            res.get<int>("version"),
            res.get<unsigned int>("edit_time"),
            res.get<std::string>("summary"),
            res.get<std::string>("username"),
            res.get<int>("user_id")
        );
        tmpArticleVersion.article = results::Article(
            res.get<int>("article_id"),
            res.get<std::string>("lang"),
            res.get<std::string>("slug"),
            res.get<std::string>("title")
        );

        articlesVersions.push_back(tmpArticleVersion);
    }
    recentChanges.reset();
    return articlesVersions;


}

/**
 *
 */
results::Diff History::diff(
    const int articleId,
    const int oldVersion,
    const int newVersion
) {
    cppdb::statement statement = sqliteDb.prepare(
        "SELECT "
        "    content,"
        "    version, "
        "    edit_time "
        "FROM history "
        "WHERE "
        "   article_id = ? AND "
        "   version IN (?,?) "
        "LIMIT 2"
    );
    statement.bind(articleId); 
    statement.bind(oldVersion); 
    statement.bind(newVersion); 
    
    cppdb::result res = statement.query();
    results::Diff diff;
    while (res.next()) {
        if (res.get<int>("version") == oldVersion) {
            diff.oldContent = res.get<std::string>("content");
            diff.oldVersionTime = res.get<int>("edit_time");
        } else {
            diff.newContent = res.get<std::string>("content");
            diff.newVersionTime = res.get<int>("edit_time");
        }
    }
    statement.reset();
    return diff;

}

/**
 *
 */
int History::get_version_of_before(
    const int articleId,
    const int version
) {
    cppdb::statement statement = sqliteDb.prepare(
        "SELECT "
        "  version "
        "FROM history "
        "WHERE "
        "   article_id = ? AND"
        "   version < ? "
        "ORDER BY version DESC "
        "LIMIT 1"
    );
    statement.bind(articleId);
    statement.bind(version);
   
    cppdb::result res = statement.row();

    int versionBefore = HISTORY_UNKOWN_ERROR;
    if (!res.empty()) {
        versionBefore= res.get<int>("version");
    }
    statement.reset();

    return versionBefore; 

}





} // end namespace models


