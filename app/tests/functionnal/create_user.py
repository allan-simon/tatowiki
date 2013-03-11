#! /usr/bin/env python
from httpclient import Cookie, Session
import urllib

REGISTER_URL = '/users/register-new'
NEW_ARTICLE_URL ='/articles/create/foo'
REGISTER_TREAT_URL ="/users/register-new_treat"
USERNAME = 'toto'
PASSWORD = 'toto'
EMAIL = '12345@test.com'
QUIZ = '12345'
CHECKED = 'y' 


#we need something to keep trace of redirection etc.  to emulate a 'real' browser
#also something to send form , see the test in cppcms

session = Session()

#we first try to access to a page that require login
#we're supposed to be redirected to the login page
registerHTML = session.transmit(REGISTER_URL)
if (session.status == 404):
    print("ERROR this page is supposed to exist")
    exit()
if (session.status != 200):
    print("ERROR we're supposed to access to it directly")


#print(session.status)
#print(session.received)
#print(registerHTML)
#loginURL = session.get_redirection()
#loginHTML = session.transmit(
#    loginURL,
#    headers = {'Cookie': session.received['cppcms_session'] }
#)

#print(REGISTER_TREAT_URL)
postData = urllib.urlencode({
    'username' : USERNAME,
    'password' : PASSWORD,
    'email' : EMAIL,
    'quiz' : QUIZ,
    'termsofuse' : CHECKED,
    '_6' : 'Register'
})
registerTreatHTML = session.transmit(
    url = REGISTER_TREAT_URL,
    post_data = postData,
    headers = {'Cookie': session.received['cppcms_session'] }
);
if (session.status != 302):
    print("ERROR while trying to register")
    exit()

#print(session.status)
#print(session.received)
#print(registerTreatHTML)
#
newArticleHTML = session.transmit(
    NEW_ARTICLE_URL,
    headers = {'Cookie': session.received['cppcms_session'] }
);

if (session.status == 200):
    print("OK")
else:
    print("ERROR we're supposed to be logged in now")

#print(session.status)
#print(session.received)
#print(NewArticleHTML)
#
