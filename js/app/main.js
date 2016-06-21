cc.game.onStart = function(){
    if(!cc.sys.isNative && document.getElementById("cocosLoading")) //If referenced loading.js, please remove it
        document.body.removeChild(document.getElementById("cocosLoading"));

    cc.view.enableRetina(true);
    
    var resources = [
         {type:"font", name:"Ubuntu", srcs:["res/Ubuntu.ttf"]},
         {type:"font", name:"FontAwesome", srcs:["res/fontawesome-webfont.ttf"]},
    ];

    // Adjust viewport meta
    cc.view.adjustViewPort(true);
    
    var w = window.innerWidth,
        h = window.innerHeight;
    
    // If we're native, grab the resolution from th
    if (cc.sys.isNative) {
        var rect = cc.visibleRect;

        w = rect.width;
        h = rect.height;
        
        cc.view.setDesignResolutionSize(w, h, cc.ResolutionPolicy.SHOW_ALL);
    } else {
        // Setup the resolution policy and design resolution size
        cc.view.setDesignResolutionSize(w, h, cc.ResolutionPolicy.EXACT_FIT);
        cc.view.setFrameSize(w, h);
        
        // The game will be resized when browser size change
        cc.view.resizeWithBrowserSize(true);
    }

    cc.LoaderScene.preload(resources, function () {
        cc.director.runScene(new quat.GameScene(w,h));
    }, this);
};
cc.game.run();