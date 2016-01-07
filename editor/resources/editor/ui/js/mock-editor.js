var editor = {
    init : function() {
        browser.absoluteDirectoryPath = 'c:/flight/.build/editor/Debug/resources';
    },

    listDirectory :function(directory) {
        return "[" +
                    '{"name" : "..", "icon" : "res/folder_icon.png", "isDirectory" : "true"},' +
                    '{"name" : "editor", "icon" : "res/folder_icon.png", "isDirectory" : "true"},' +
                    '{"name" : "rocket", "icon" : "res/folder_icon.png", "isDirectory" : "true"},' +
                    '{"name" : "shader", "icon" : "res/folder_icon.png", "isDirectory" : "true"},' +
                    '{"name" : "skybox", "icon" : "res/folder_icon.png", "isDirectory" : "true"},' +
                    '{"name" : "awesomium_logo.png", "icon" : "", "isDirectory" : "false"},' +
                    '{"name" : "entity.lua", "icon" : "", "isDirectory" : "false"}' +
                "]";
    },

    loadFileContents: function(file) {
        return "var a = 1;\nvar b = 2;";
    }
};



