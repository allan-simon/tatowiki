begin;
    drop table if exists articles;
    drop table if exists users;

    -- table representing a user 
    CREATE TABLE users (
        "id"          integer primary key autoincrement not null , 
        "username"    text    not null unique,             -- his nickname 
        "email"       text    not null unique,             -- his email address
        "image"       text    not null default "unknown" , -- his personnal image 
        "password"    text    not null,                    -- his password hashed
        "since"       integer not null,                    -- his registering date
        "homepage"    text    default "",                  -- his personnal webpage/website
        "description" text    default ""                   -- his self-written description
    );
    CREATE INDEX users_username_idx ON users (username);

    -- table representing an article (i.e a page of the wiki)
    -- TODO maybe have something to do a more precise restriction (for example authorizing only some kind of users
    --      to edit a given pages (e.g only moderators/only admin)
    -- TODO same things for the visibility 
    create table articles (
        id integer primary key autoincrement not null,
        lang text not null,                            -- code iso 639-3 alpha 3 in which the articles is written
        slug text not null,                            -- "url" name of the article 
        title text not null,                           -- title of the article 
        content text not null,                         -- the content of the article itself
        locked boolean,                                -- if the articles can be edited or not
        unique (lang,slug)                             -- in order to not have several articles on the same url
    );

    -- table storing the different version of the articles 
    -- TODO storing user_id so that we know who did the change
    create table history (
        version integer primary key autoincrement not null default 1, 
        lang text not null,
        slug text not null,
        title text not null,
        content text not null,
        edit_time timestamp default (strftime('%s', 'now')),-- when the edition has been made
        summary text not null                              -- text to explain what has been done

    );



commit ;
