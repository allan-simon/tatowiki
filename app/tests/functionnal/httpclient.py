#!/usr/bin/env python
# coding=UTF-8
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

PORT=8080
HOST = 'en.tatolocal.org'

import httplib
import urllib

class Cookie:

    def __init__(self,content=''):
        self.max_age = None
        self.domain = None
        self.path = None
        self.name = ''
        self.value = ''
        secure = False

        values=content.split(';')
        self.name = values[0].strip().split('=')[0]
        self.value = values[0].strip().split('=')[1]
        for vin in values[1:]:
            v=vin.strip();
            vals = v.split('=')
            parname = vals[0].lower()
            if parname=='domain':
                self.domain=vals[1]
            elif parname == 'path':
                self.path=vals[1]
            elif parname == 'max-age':
                self.max_age = vals[1]

    def __str__(self):
        s=self.pair()
        if self.domain:
            s+='; Domain=' + self.domain
        if self.path:
            s+='; Path='+self.path
        if self.max_age:
            s+='; Max-Age='+self.max_age
        return s

    def pair(self):
        return self.name + '=' + self.value 

def parse_cookies(response):
    cookies=[]
    hdr = response.getheader('set-cookie')
    if hdr:
        vals = hdr.split(',')
        for val in vals:
            cookies.append(Cookie(val))
    cm={}
    for c in cookies:
        cm[c.name]=c
    return cm

class Session:
    api = 'http'
    def __init__(self,print_cookies = True, debug_level = 0):
        self.state={}
        self.headers =[]
        self.received={}
        self.print_cookies = print_cookies
        self.debug_level = debug_level

    def getcookies(self):
        allcookies=''
        for key,value in self.state.items():
            if allcookies == '':
                allcookies = value.pair()
            else:
                allcookies+= '; ' + value.pair()
        return allcookies

    def transmit(self,url,post_data=None,content_type='application/x-www-form-urlencoded',headers={}):
        received={}
        conn=httplib.HTTPConnection(HOST,PORT)
        conn.set_debuglevel(self.debug_level)
        headers['Cookie']=self.getcookies() 
        if post_data:
            headers['Content-Type']=content_type
            conn.request('POST',url,post_data,headers)
        else:
            conn.request('GET', url,None,headers)
        r=conn.getresponse()
        
        self.status = r.status
        self.headers = r.getheaders()
        content = r.read();
        self.received=parse_cookies(r)
        self.update_state()
        return content

    ################
    def get_redirection(self):
        if (self.status in [302,303]):
            for name,value in self.headers:
                if (name == 'location'):
                    return value
        return ''
    
    ################
    def update_state(self):
        if self.print_cookies:
            print("Got following cookies")
        for name,cookie in self.received.items():
            if self.print_cookies:
                print(cookie)
            if name in self.state:
                if cookie.max_age=='0':
                    del self.state[name]
                else:
                    self.state[name] = cookie
            else:
                if cookie.max_age != '0':
                    self.state[name] = cookie
        if self.print_cookies:
            print("---------------------")
    def debug_cookies(self):
        print("Debug cookies")
        for name,cookie in self.received.items():
            print(cookie)
        print("---------------------")

    ################
    def test_http_status(
        self,
        authorized = [200]
    ):
        if self.status not in authorized :
            if 404 in authorized:
                print("ERROR this page is not supposed to exist")
            if 200 in authorized:
                print("ERROR we're supposed to access to this page directly")
            if 302 in authorized:
                print("ERROR we're supposed to be redirected")
            return False
        return True

        
    ################
    def transmit_post_form(
        self,
        post_url,
        post_data_array,
    ):
        postData = urllib.urlencode(post_data_array)
        return self.transmit(
            url = post_url,
            post_data = postData
        )
