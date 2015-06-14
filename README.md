#Introduction to Tatowiki

Tatowiki is a wiki in c++ built upon cppcms and cppcms-skeleton, it is made for generic purpose and high performance.

**Note:** This software is still at a very early stage, but since April 2013, it's now have several skin and a quite neutral and responsive one, so it can start to be used by people who need a basic wiki, with high performance and a low memory-print or a wiki that display fine on a mobile phone.

Other features will be added step by step. The goal at the end is to have a complete wiki, that can easily be extended with plugins. 

#Requirement for Tatowiki

To run it you need:
    
  * cppcms
  * cppcms-skeleton
  * sqlite3 
  * discount (libmarkdown)

To compile it you need a little more

  * python3 
  * cmake 
  * a compiler that supports c++11
  * clang

#Installation instruction
    

    git clone https://github.com/allan-simon/tatowiki.git
    cd tatowiki/app
    mkdir build ; cd build ; cmake .. ; make

After this you need to create the dabatase schema, note for the moment we
only support sqlite3 and you need to create it manually 

if you're in the 'build' directory, simply do 

    sqlite3 ../data/sqlite6.db < ../sql/sqlite3.sql

**Note:** Of course the name and path for the database (sqlite6.db) is purely
arbitrary and can be changed without problems (you simply need to adapt your
config.js)

#Configuration

Edit `app/config.js` according to your needs (change YOURHOST by your
hostname). On a local installation, you can use a local domain such as
.tato.wiki.local and define it your `/etc/hosts` like this.

```
127.0.0.1       tato.wiki.test ja.tato.wiki.test en.tato.wiki.test de.tato.wiki.test ...
```

If you’re using a port different than 80, make sure to specify it
in the `baseHost` option too, like this.

```js
{
    "service" : {
            "api" : "http",
            "port" : 8081,
            "ip" : "0.0.0.0"
    },

    /* ... */

    "baseHost" : "tato.wiki.test:8081",

    /* ... */
}
```

Tatowiki needs to have write access to the following directories and files:
* The sqlite database (`app/data/sqlite6.db`)
* `app/data/`
* `app/upload/`


#Running it 

    ./tatowiki -c ../config.js #from the build directory


#Note:

    For the moment you can't run it from a raw ip address as it use a subdomain for
    storing the current interface language (it will be changed in the future)


