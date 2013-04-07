function init_editor() {
    new WMDEditor({
        input: "editor",
        button_bar: "editor-button-bar",
        preview: "editor-preview",
        buttons: "bold italic link  ol ul  heading code image",
        modifierKeys: false,
        autoFormatting: false
    });

}

window.onload = init_editor();
