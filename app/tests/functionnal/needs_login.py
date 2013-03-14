#! /usr/bin/env python
from httpclient import Cookie, Session
import urllib


#we first try to access to a page that require login
#we're supposed to be redirected to the login page

def login(
    session = Session(print_cookies = False),
    username = 'toto',
    password = 'toto'
):
    CHECKED = 'y' 
    NEW_ARTICLE_URL ='/articles/create/foo'
    LOGIN_URL = '/users/login'
    LOGIN_TREAT_URL = '/users/login_treat'


    session.transmit(NEW_ARTICLE_URL)
    if (session.status == 404):
        print("ERROR this page is supposed to exist")
        return None
    if (session.status != 302):
        print("ERROR not supposed to access to this")
        return None

    loginURL = session.get_redirection()
    if (loginURL != '/users/login?from=%2farticles%2fcreate%2ffoo'):
        print('ERROR we\'re not redirected to the login page')
        return None

    postData = urllib.urlencode({
        'username' : username,
        'password' : password,
        'rememberMe' : CHECKED,
        'login' : 'Log in'
    })
    loginTreatHTML = session.transmit(
        url = LOGIN_TREAT_URL,
        post_data = postData,
        headers = {'Cookie': session.received['cppcms_session'] }
    );
    if (session.status != 302):
        print("ERROR while trying to login")
        return None

    newArticleHTML = session.transmit(
        NEW_ARTICLE_URL,
        headers = {'Cookie': session.received['cppcms_session'] }
    );

    if (session.status == 200):
        print("OK")
    else:
        print("ERROR we're supposed to be logged in now")
        return None
    return session
    
if __name__ == '__main__':
    login()







