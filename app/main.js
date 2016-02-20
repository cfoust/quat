cc.game.onStart = function(){
    if(!cc.sys.isNative && document.getElementById("cocosLoading")) //If referenced loading.js, please remove it
        document.body.removeChild(document.getElementById("cocosLoading"));

    cc.view.enableRetina(true);

    // Adjust viewport meta
    cc.view.adjustViewPort(true);

    var w = window.innerWidth,
        h = window.innerHeight;

    // Setup the resolution policy and design resolution size
    cc.view.setDesignResolutionSize(w, h, cc.ResolutionPolicy.EXACT_FIT);
    cc.view.setFrameSize(w, h);
    
    // The game will be resized when browser size change
    cc.view.resizeWithBrowserSize(true);
    
    cc.director.runScene(new quat.solver.PuzzleScene(w,h));
};
cc.game.run();