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
    return True


if __name__ == '__main__':
    session = Session()
    login(session)
    create_article(session)
    if (create_article(title = '',slug='prout')):
        print("ERROR we're not supposed to create an article with an empty title")



