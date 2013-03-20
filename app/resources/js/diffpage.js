function diffUsingJS() {
    // get the baseText and newText values from the two textboxes, and split them into lines
    var base = difflib.stringAsLines(document.getElementById("old").innerHTML);
    var newtxt = difflib.stringAsLines(document.getElementById("new").innerHTML);

    // create a SequenceMatcher instance that diffs the two sets of lines
    var sm = new difflib.SequenceMatcher(base, newtxt);

    // get the opcodes from the SequenceMatcher instance
    // opcodes is a list of 3-tuples describing what changes should be made to the base text
    // in order to yield the new text
    var opcodes = sm.get_opcodes();
    var diffoutputdiv = document.getElementById("showDiff");
    contextSize = null;

    // build the diff view and add it to the current DOM
    var table = diffview.buildView({
        baseTextLines: base,
        newTextLines: newtxt,
        opcodes: opcodes,
        // set the display titles for each resource
        baseTextName: "Base Text",
        newTextName: "New Text",
        contextSize: contextSize,
        viewType:  1
    });
    var wrap = document.createElement('div');
    wrap.appendChild(table.cloneNode(true));
    diffoutputdiv.innerHTML = wrap.innerHTML;

    // scroll down to the diff view window.
    location = document.URL + "#showDiff";
}

window.onload =diffUsingJS();
