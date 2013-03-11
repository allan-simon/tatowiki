#! /usr/bin/env python
from httpclient import Cookie, Session
import urllib


#we first try to access to a page that require login
#we're supposed to be redirected to the login page

USERNAME = 'toto'
PASSWORD = 'toto'
CHECKED = 'y' 

NEW_ARTICLE_URL ='/articles/create/foo'
LOGIN_URL = '/users/login'
LOGIN_TREAT_URL = '/users/login_treat'

session = Session(print_cookies = False)

session.transmit(NEW_ARTICLE_URL)
if (session.status == 404):
    print("ERROR this page is supposed to exist")
if (session.status != 302):
    print("ERROR not supposed to access to this")

loginURL = session.get_redirection()
if (loginURL != '/users/login?from=%2farticles%2fcreate%2ffoo'):
    print('ERROR we\'re not redirected to the login page')

postData = urllib.urlencode({
    'username' : USERNAME,
    'password' : PASSWORD,
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
    exit()

newArticleHTML = session.transmit(
    NEW_ARTICLE_URL,
    headers = {'Cookie': session.received['cppcms_session'] }
);

if (session.status == 200):
    print("OK")
else:
    print("ERROR we're supposed to be logged in now")







