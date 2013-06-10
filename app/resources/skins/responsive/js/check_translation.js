(function() {
    "use strict";
    // check if the slug is correct (i.e not a complete URL see #70)
    function check_slug() {
        var slugInput = document.getElementById("translationSlug");
        var slug = slugInput.value;
        if (slug.indexOf("http://") === -1 ) {
            if (slug.indexOf("articles/show/") === -1) {
                return true;
            }
        }
        //TODO replace this alert by something sexier
        alert("The 3rd field must contain only the last part of the URL, for example only 'linux' not 'http://example.com/articles/show/linux'");
        return false;
    }
    
    //check if the translation form is likely to validate
    function check_translation_form() {
        return check_slug();
    }
    var form = document.getElementById("translateform");
    form.onsubmit = check_translation_form;


}());
