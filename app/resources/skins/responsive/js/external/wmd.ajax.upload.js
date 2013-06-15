$(document).ready(function(){
    $(document).on(
        "click",
        ".wmd-image-button",
        function(){
            var div = $("<div>");
            var form = $("<form>").attr({action: "create_new_blog_post/submit_image", method: "post"})
            var file = $("<input/>").attr({type: "file", name: "image"});
            var name = $("<input/>").attr({type: "text", name: "name", placeholder: "Name"});
            var submit = $("<input/>").attr("type", "submit");
            form.append(name, file, submit);
            div.append(form).dialog({title: "Upload Image"});
        }
    );
    $(document).on(
        "click",
        ".wmd-link-button",
        function(){
            setTimeout(
                function(){
                    $(".wmd-prompt-dialog").css("opacity", "1");
                },
                100
            );
        }
    );
});
