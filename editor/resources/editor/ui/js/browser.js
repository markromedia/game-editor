/***
 * The global for the information contained in either the entity brower
 * or file browser
 */
browser = {
    //the current directory
    absoluteDirectoryPath : 'c:/',
    relativeDirectoryPath : '/',

    /**
     * Show the directory browser
     */
    showDirectory : function() {
        //grab the directories
        var json = editor.listDirectory(browser.absoluteDirectoryPath);
        var files = jQuery.parseJSON(json);

        $('#directory-list').empty();
        files.forEach(function(file) {
            var icon = '';
            if (file.icon != '') {
                icon = '<img src="' + file.icon + '"/>';
            }
            $('#directory-list').
                append('<li ondblclick=\'browser.fileClicked("' + file.name + '",'
                                                                +  '"' + file.icon + '",'
                                                                + '"' + file.isDirectory + '",'
                                                                + 'this)\'>' +
                            '<div>' + icon + '</div>' + file.name +
                      '</li>')
        });

        $('#tab1').css('z-index', '1');
        $('#tab2').css('z-index', '0');
        $('#files-tab-header').css({"border-bottom-width" : "0", "color" : "white"});
        $('#entity-tab-header').css({"border-bottom-width" : "1px", "color" : "#999"});
    },

    fileClicked : function(filename, icon, isDirectory, el) {
        $('#directory-list').find('li').removeClass("file-highlighted");
        el.className  += 'file-highlighted';

        if (isDirectory == 'true') {
            this.absoluteDirectoryPath += '/' + filename;
            this.relativeDirectoryPath += '/' + filename;
            this.showDirectory();
        } else {
            window.fileEditor.initializeEditor("codemirror-editor-textarea");
            if (browser.endsWith(filename, ".html") ||
                browser.endsWith(filename, ".lua") ||
                browser.endsWith(filename, ".js") ||
                browser.endsWith(filename, ".vert") ||
                browser.endsWith(filename, ".frag")) {
                window.fileEditor.activeEditor.setValue(editor.loadFileContents(this.absoluteDirectoryPath + '/' + filename));
            }
        }
    },

    /**
     * Show the entity browser
     */
    showEntity : function() {
        $('#tab1').css('z-index', '0');
        $('#tab2').css('z-index', '1');
        $('#files-tab-header').css({"border-bottom-width": "1px", "color": "#999"});
        $('#entity-tab-header').css({"border-bottom-width": "0", "color": "white"});
    },

    /**
     * Utility for str.endswith
     */
    endsWith : function (str, suffix) {
        return str.indexOf(suffix, str.length - suffix.length) !== -1;
    }
};
