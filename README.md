#Introduction to Tatowiki

Tatowiki is a wiki in c++ built upon cppcms and cppcms-skeleton

**Note:** This software is still at a very early stage, for the moment it's focused on producing something usable for Tatoeba, but in the future the goal would be to provide an easy to setup/custom/extand wiki.

#Requirement for Tatowiki

To run it you need:
    
  * cppcms
  * cppcms-skeleton
  * sqlite3 

To compile it you need a little more

  * python3 
  * cmake 
  * a compiler that supports c++11

#Installation instruction
    

    git clone git://github.com/allan-simon/tatowiki.git
    cd tatowiki
    mkdir build ; cd build ; cmake .. ; make

After this you need to create the dabatase schema, note for the moment we
only support sqlite3 and you need to create it manually 

if you're in the 'build' directory, simply do 

    sqlite3 ../data/sqlite6.db < ../sql/sqlite3.sql

**Note:** Of course the name and path for the database (sqlite6.db) is purely
arbitrary and can be changed without problems (you simply need to adapt your
config.js)


#Running it 

    ./TatoWiki -c ../config.js #from the build directory


#Note:

    For the moment you can't run it from a raw ip address as it use a subdomain for
    storing the current interface language (it will be changed in the future)


