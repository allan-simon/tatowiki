$(function(){
    $("#toc").tableOfContents(
        $("#main_content")
    );
    // we need to do that to force the browser to
    // re-evaluate the hash in the url, now that it has
    // been created
    window.location.hash = window.location.hash;
})
