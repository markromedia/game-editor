var fileEditor = {
    activeEditor : null,

    initializeEditor : function(element) {
        fileEditor.activeEditor = CodeMirror.fromTextArea(document.getElementById(element), {
            lineNumbers: true,
            mode: "javascript",
            value : ";",
            theme : "ambiance"
          });
        fileEditor.activeEditor.setSize("100%", "100%")
        setTimeout( fileEditor.activeEditor.refresh, 0);
    }
};

