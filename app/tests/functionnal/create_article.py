#! /usr/bin/env python
from httpclient import Cookie, Session
from needs_login  import login
import urllib



def create_article(
    lang = 'en',
    title = 'test',
    slug = 'test',
    content = '#Hello',
    summary = 'created by an automated test'
):
    SHOW_ARTICLE_URL ='/articles/show/' + slug
    CREATE_ARTICLE_URL ='/articles/create/' + slug
    CREATE_ARTICLE_TREAT_URL ='/articles/create_treat'

    # we try to access to an article that does not exist
    # => we should be redirected to the page to create an article
    registerHTML = session.transmit(SHOW_ARTICLE_URL)
    if (not session.test_http_status([302])):
        print("ERROR while trying to access to a non-existing article")
        return False

    if (session.get_redirection() != CREATE_ARTICLE_URL):
        print("ERROR we should be redirected to the page to create an article")
        return False

    # now we post a form to create an article
    postData = {
        "_1" : slug,
        "_2" : title,
        "_3" : content,
        "_4" : summary,
        "save_and_view" : "blah"
    }
    session.transmit_post_form(
        post_url = CREATE_ARTICLE_TREAT_URL,
        post_data_array = postData
    )
    if (not session.test_http_status([302])):
        print("ERROR we should be redirected");
        print("status: " + str(session.status))
        return False
    if (session.get_redirection() != SHOW_ARTICLE_URL):
        return False
    return True

if __name__ == '__main__':
    error = False
    session = Session(print_cookies=False)
    login(session)
    if (not create_article(session)):
        error = True
        print("ERROR while trying to add a normal article")
    if (create_article(title = '',slug='prout')):
        error = True
        print("ERROR we're not supposed to create an article with an empty title")
    if (not error):
        print(OK)



