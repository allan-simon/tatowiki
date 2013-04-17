#! /usr/bin/env python
from httpclient import Cookie, Session
from needs_login  import login
from create_article import create_article
import urllib



def delete_article(
    session = Session(),
    lang = 'en',
    slug = 'test-delete',
):
    SHOW_ARTICLE_URL ='/articles/show/' + slug
    CREATE_ARTICLE_URL ='/articles/create/' + slug
    REMOVE_ARTICLE_URL ='/articles/remove/' + slug

    session.transmit(REMOVE_ARTICLE_URL)
    if (not session.test_http_status([302])):
        print("ERROR while trying to remove an article")
        return False

    # now trying to access to the article should redirect us ...
    registerHTML = session.transmit(SHOW_ARTICLE_URL)
    if (not session.test_http_status([302])):
        print("ERROR while trying to access to a non-existing article")
        return False

    # ... to the page to create it
    if (session.get_redirection() != CREATE_ARTICLE_URL):
        print("ERROR we should be redirected to the page to create an article")
        return False

    return True

if __name__ == '__main__':
    error = False
    session = Session(print_cookies=False)
    login(session)
    if (not create_article(session, title="test delete", slug = 'test-delete')):
        error = True
        print("ERROR while trying to add a normal article")
    if (not delete_article(session)):
        error = True
        print("ERROR while trying to remove a normal article")
    if (not error):
        print("OK")



