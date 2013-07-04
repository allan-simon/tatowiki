-- this script add the support for search request introduced by feature #72

    -- table used for the search engine
    create virtual table search using fts4(
        slug ,
        title,
        content,
        lang,
        tokenize=porter
    );

    ---------------------------------------------
    --
    -- Triggers to keep the search table sync 
    -- with the articles tables
    --
    ---------------------------------------------
    
    -- when we update an article we delete the older one from 
    -- the search engine
    create trigger articles_bu before update on articles BEGIN
        delete from search where docid=old.id;
    end;

    -- after we've updated, we add the updated article to
    -- the search engine
    create trigger articles_au after update on articles begin
        insert into search(
            docid,
            slug,
            title,
            content,
            lang
        ) values (
            new.id,
            new.slug,
            new.title,
            new.content,
            new.lang
        );
    end;
    
    -- when delete in article, we also delete in the search engine
    create trigger articles_bd before delete on articles begin
        delete from search where docid=old.id;
    end;


    -- when we insert, we also insert in the search engine
    create trigger articles_ai after insert on articles begin
        insert into search(
            docid,
            slug,
            title,
            content,
            lang
        ) values (
            new.id,
            new.slug,
            new.title,
            new.content,
            new.lang
        );
    end;

-- fill the search table with preexisting data
INSERT INTO search(
    docid,
    slug,
    title,
    content,
    lang
) SELECT
    id,
    slug,
    title,
    content,
    lang
FROM articles;
-- reogarnize correctly the index of the search table
insert into search(search) values("optimize");

