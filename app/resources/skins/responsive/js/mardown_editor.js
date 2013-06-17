(function() {
    "use strict";
    // this function display a form to enter an image
    // url or permit to upload an image directly
    function ajaxPictureUpload() {
        // Create dialog to show user
        // TODO i18n it

        //define the content
        var win = $('<form></form>');
        win.attr('method', 'POST');
        win.attr('action', '/media/upload-image_ajax');
        win.attr('enctype', 'multipart/form-data');

        var text = $('<span></span>');
        text.append("Enter image address or upload one:");//TODO i18n
        var url = $('<input type="text" name="url" value="http://"></input>');
        url.attr("id", "url");
        var imageDescription = $('<input type="text" ></input>');
        imageDescription.attr("name", "description");
        imageDescription.attr("value", "Image Description"); //TODO i18n
        imageDescription.attr("id", "description");
        var upload = $('<input name="_1" type="file" value=""></input>');
        var submit = $('<input type="submit"/>');
        submit.attr("value", "upload");//TODO i18n
        var ok = $('<br/><br/><button class="okbutton"></button>');
        ok.append("OK");//TODO i18n
        var cancel = $('<button class="cancelbutton"></button>');
        cancel.append("cancel");//TODO i18n

        $(win).append(text);
        $(win).append(url);
        $(win).append(upload).append(submit);
        $(win).append(imageDescription);
        $(win).append(ok).append(cancel);

        $(win).dialog({
            'autoshow': true,
            'bgiframe': true,
            'title': 'Add an image',//TODO i18n
            'closeOnEscape': true,
            'height': 300,//this should be big enough
            'width': 420  // to be visible in all interface lang
        });

        $(win).ajaxForm({
            dataType : 'json',
            success: function(obj) {
                //we lenght === 1 and not 0
                //because for the moment the errors array contains
                //always a final empty element
                //TODO correct this hack
                if (obj.errors.length === 1) {
                    $(url).attr("value",obj.data);
                } else {
                    
                    $.each(
                        obj.errors.slice(0,-1),
                        function(index,error) {
                            alert(error.text);
                        }
                    )
                }
            },
            error: function(){
                alert("error");
            }
        });

        $(win).children().filter('.okbutton').click(function() {

            // this does not work for some reason (i.e give me the default
            // value not the actual one
            //var urlValue = $('.url').attr('value');
            // so instead we used that, ugly but it works
            // TODO purify this
            var urlValue = document.getElementById("url").value;
            var altText = document.getElementById("description").value;

            $('#editor').markeditSetLinkOrImage(
                true,
                urlValue,
                altText
            );
            $(win).dialog('close');
            $(win).remove();
        });

        // if we click on cancel => close the window without doing
        // anything
        $(win).children().filter('.cancelbutton').click(function() {
            $(win).dialog('close');
            $(win).remove();
        });

    }

    // we now create the markdown editor
    var layout = 'bold italic ' +
        '| link quote code ajaximage ' +
        '| numberlist bulletlist heading line';

    $('#editor').markedit({
        'preview': 'selector',
        'selector': '#editor-preview',
        'toolbar' : {
            'layout' : layout,
            'buttons' : [{
                'id': 'ajaximage',
                'tip': 'Add an image',//TODO i18n
                'css': 'image',
                'click': ajaxPictureUpload
            }]
        }
    });


})();
