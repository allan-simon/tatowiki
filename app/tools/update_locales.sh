#!/bin/bash
# script to update the .po files of the different languages 
# it can be called by using make update_locale
xgettext\
    --keyword=translate:1,1t\
    --keyword=_\
    ../build/view_web.cpp\
    ../src/*.cpp\
    ../src/controllers/webs/*.cpp\
    ../src/contents/forms/*.h\
    ../src/models/*.cpp
# it's just to avoid a warning 
sed -ie 's/CHARSET/utf-8/'  messages.po
msgmerge ../locale/messages.po messages.po -U --backup=none
rm messages.po

# we use locale/* -maxdepth 0 instead of locale -maxdepth 0 
# because otherwise find would have returned 'locale' which is
# not what we want
for D in `find ../locale/* -maxdepth 0 -type d `
do
    msgmerge  ../locale/$D/LC_MESSAGES/messages.po  ../locale/messages.po -U --backup=none
    msgfmt ../locale/$D/LC_MESSAGES/messages.po -o ../locale/$D/LC_MESSAGES/messages.mo
done
