#! /usr/bin/env python
from httpclient import Cookie, Session


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


    # we should be redirected to the login page when we try to access
    # to a page reserved to registered users
    session.transmit(NEW_ARTICLE_URL)
    if (not session.test_http_status([302])):
        print('ERROR we should be redirected when not logged');
        return False
    loginURL = session.get_redirection()
    #replace the encoded url by url encode
    if (loginURL != '/users/login?from=%2farticles%2fcreate%2ffoo'):
        print('ERROR we\'re not redirected to the login page')
        return False


    # we post the form
    postData = {
        'username' : username,
        'password' : password,
        'rememberMe' : CHECKED,
        'login' : 'Log in'
    }
    loginTreatHTML = session.transmit_post_form(
        post_url = LOGIN_TREAT_URL,
        post_data_array = postData
    )
    if (not session.test_http_status([302])):
        print("ERROR while trying to login")
        return False

    # now try to access to a login-only page
    newArticleHTML = session.transmit(
        NEW_ARTICLE_URL,
    );
    if (not session.test_http_status([200])):
        print("ERROR we're supposed to be logged in now")
        return False
        
    return True

if __name__ == '__main__':
    login()







