#Introduction to Tatowiki

Tatowiki is a wiki in c++ built upon cppcms and cppcms-skeleton, it is made for generic purpose and high performance.

**Note:** This software is still at a very early stage, but since April 2013, it's now have several skin and a quite neutral and responsive one, so it can start to be used by people who need a basic wiki, with high performance and a low memory-print or a wiki that display fine on a mobile phone.

Other features will be added step by step. The goal at the end is to have a complete wiki, that can easily be extended with plugins. 

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

    ./tatowiki -c ../config.js #from the build directory


#Note:

    For the moment you can't run it from a raw ip address as it use a subdomain for
    storing the current interface language (it will be changed in the future)


