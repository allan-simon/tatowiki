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
 * @link     https://github.com/sysko/tatowiki
 */

#ifndef TatoWiki_ARTICLES
#define TatoWiki_ARTICLES


#include <cppcms_skel/models/SqliteModel.h>

#include "results/Articles.h"

#define ARTICLE_CREATION_ERROR -1
#define ARTICLE_DOESNT_EXIST_ERROR -2
#define ARTICLE_ALREADY_TRANSLATED_ERROR -3
#define ARTICLE_CREATE_TRANSLATION_ERROR -4
#define ARTICLE_ADD_TRANSLATION_LINK_ERROR -5
#define ARTICLE_SAME_TRANSLATION_LANGUAGE_ERROR -6
#define CONFLICT_CREATION_ERROR -7

namespace models {


/**
 * @class Articles
 * 
 * @brief @TODO
 * @since 30 October 2012       
 *
 */
class Articles : public SqliteModel {
    public:
        /**
         * @brief Constructor, load the article model and link it
         *        with the database given by the config.js file
         * @since 30 October 2012
         */
        Articles();

        /**
         * @brief Load the article models and link it with the database
         *        precised in parameters
         *
         * @param The database file path to link the model with
         *
         * @since 4 January 2013
         */
        Articles(const std::string &dbPath);

        /**
         * @brief Retrieve an article using the couple (lang,slug)
         *        that we extract from the URL
         * 
         * @param lang ISO code of the language in which the article
         *             is written
         * @param slug Slug of the article (i.e URL version of the
         *             title)
         *
         * @return The article corresponding to the criteria
         *
         * @since 30 October 2012
         */
        results::Article get_from_lang_and_slug(
            const std::string &lang,
            const std::string &slug
        );


        /**
         * @brief Save a new version of an article
         * 
         * @param lang    ISO code of the language in which the article
         *                is written
         * @param slug    Slug of the article (i.e URL version of the
         *                title)
         * @param title   The title of the article
         * @param content The main content of the article
         *
         * @return bool If the article has been correctly edited
         *
         * @since 30 October 2012
         */

        bool edit_from_lang_and_slug(
            const std::string &lang,
            const std::string &slug,
            const std::string &title,
            const std::string &content
        );

        /**
         * @brief Save a new article
         * 
         * @param lang    ISO code of the language in which the article
         *                is written
         * @param slug    Slug of the article (i.e URL version of the
         *                title)
         * @param title   The title of the article
         * @param content The main content of the article
         *
         * @return Id of the article that has been created
         *         or a negative value in case of errors
         *
         * @since 4 November 2012
         */
        int create_from_lang_and_slug(
            const std::string &lang,
            const std::string &slug,
            const std::string &title,
            const std::string &content
        );

        /**
         * @brief Remove an article from the list of viewable article
         *        it is actually not deleted totally in order to be able
         *        to revert it in case of error/vandalism
         * 
         * @param lang    ISO code of the language in which the article
         *                is written
         * @param slug    Slug of the article (i.e URL version of the
         *                title)
         * 
         * @return bool True if the articles as been removed correctly
         *
         * @since 16 November 2012
         *
         */
        bool remove(
            const std::string &lang,
            const std::string &slug
        );

        /**
         * @brief Retrieve the complit list of Articles (only the "title" part)
         *
         * @return Articles List of articles
         *
         * @since 18 November 2012
         */
        results::Articles get_all();

        /**
         * @brief Translate an article in an other language 
         * 
         * @param lang    ISO code of the language in which the article
         *                is written
         * @param slug    Slug of the article (i.e URL version of the
         *                title)
         * @param title   The title of the article
         * @param content The main content of the article
         *
         * @return Id of the translation, or a negative number
         *         if something wrong happens
         *
         * @since 4 November 2012
         */
        int translate_from_lang_and_slug(
            const std::string &origLang,
            const std::string &origSlug,
            const std::string &lang,
            const std::string &slug,
            const std::string &title,
            const std::string &content
        );

        /**
         * @brief Retrieve the id of an article based on its
         *        Lang and URL name
         *
         * @param lang Lang in which the article is
         * @param slug URL name of the article
         *
         * @return Id of the article, or a negative number
         *         if the articles does not exists or other
         *         kind of problems happen
         *
         * @since 28 November 2012
         */
        int get_id_from_lang_and_slug(
            const std::string &lang,
            const std::string &slug
        );
        
        /**
         * @brief Retrieve an article using the couple its id
         * 
         * @param id Id of the article
         *
         * @return The article corresponding to the criteria
         *
         * @since 20 March 2013
         */
        results::Article get_from_id(
            const int id
        );
        
        /**
         * @brief Retrieve the group id of an article based on its
         *        Lang and URL name
         *
         * @param lang Lang in which the article is
         * @param slug URL name of the article
         *
         * @return Group id of the article, or a negative number
         *         if the articles does not exists or other
         *         kind of problems happen
         *
         * @since  03 March 2013
         */
        int get_group_id_from_lang_and_slug(
            const std::string &lang,
            const std::string &slug
        );
  
        
        /**
         * @brief Add an article to a group of articles in other
         *        languages but about the same subject
         *        Note: it does not any test beforehand, so
         *        be sure the two ids exists etc.
         * 
         * @param groupId        Id of the group you want to add an article to
         * @param translationId  Id of the article to add to the group
         *
         * @since 03 March 2013
         */
        int add_to_group(
            const int groupId,
            const int translationId
        );
        
        /**
         * @brief Use to know if a group of article contains a certain
         *        language
         *
         * @param groupId   Id of the group to check  
         * @param lang      The code of the language
         *
         * @return True if the group is already translated in that language
         *         False otherwise
         *
         * @since 03 March 2013
         */
        bool group_contains_lang(
            const int groupId,
            const std::string &lang
        );

        /**
         * @brief Get the list of language:slug of the other articles 
         *        belonging to the same group than an article
         *
         * @param articleId The id of article
         * @paran groupId   Group to which the article belongs
         * 
         * @return A list of languages:slugs
         *
         * @since 27 December 2012
         */
        results::TranslatedIn get_group_of(
            const int articleId,
            const int groupId
        );
        
        /**
         * @brief Get an article which is the article as it should have been
         *        if the edition that generated a conflict was applied 
         *
         * @param conflictId The id of this conflict
         *
         * @return The article, as this conflict was trying to change it
         *
         * @since 14 March 2013
         */
        results::Article get_article_from_conflict(
            const int conflictId
        );
        
        /**
         * @brief Save an article which is the article as it should have been
         *        if the edition that generated a conflict was applied 
         *
         * @param article The article, as this conflict was trying to change it
         *
         * @return The id of this conflict
         *
         * @since 14 March 2013
         */

        int save_conflict(
           const results::Article &article 
        );

    //end public 
    private:
        /**
         * @brief get a complete article out of a cppdb result
         *
         * @param res A cppdb result that was given after executing a query
         *
         * @return An article with every field filled
         *
         * @since 20 March 2013
         */
        results::Article get_from_result(
            cppdb::result &res
        );
    
};

} // end namespace models 

#endif
