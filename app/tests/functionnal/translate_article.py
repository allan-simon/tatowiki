#! /usr/bin/env python
# -*- coding: utf-8 -*-
from httpclient import Cookie, Session
from needs_login  import login
import urllib



def translate_article(
    session = Session(),
    lang = 'en',
    slug = 'test',
    translateLang = 'zh',
    translateSlug = 'test-zh',
    translateTitle= 'Test Zh',
    content = u'nihao',
    summary = u'created by an automated test in chinese'
):
    SHOW_ARTICLE_URL ='/articles/show/' + slug
    TRANSLATE_ARTICLE_URL ='/articles/translate/' + slug
    TRANSLATE_ARTICLE_TREAT_URL ='/articles/translate_treat'

    registerHTML = session.transmit(SHOW_ARTICLE_URL)
    if (not session.test_http_status([200])):
        return False

    session.transmit(TRANSLATE_ARTICLE_URL)
    if (not session.test_http_status([200])):
        print("ERROR while trying to access to the form to translate an article")
        return False


    # now we post a form to create an article
    postData = {
        "_1" : slug,
        "_2" : translateTitle,
        "_3" : translateLang,
        "translationSlug" : translateSlug,
        "_5" : content,
        "_6" : summary,
        "save_and_view" : "blah"
    }
    session.transmit_post_form(
        post_url = TRANSLATE_ARTICLE_TREAT_URL,
        post_data_array = postData
    )
    if (not session.test_http_status([302])):
        print("ERROR we should be redirected");
        print("status: " + str(session.status))
        return False
    if (session.get_redirection().find(translateSlug) == -1):
        return False
    return True

if __name__ == '__main__':
    error = False
    session = Session(print_cookies=False)
    login(session)
    if (not translate_article(session)):
        error = True
        print("ERROR while trying to translate a normal article")
    if (translate_article(session,slug='doesnotexist')):
        error = True
        print("ERROR we're not supposed to be able to translate a non-existing article")
    if (not error):
        print("OK")



