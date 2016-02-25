var quat = quat || {};
quat.menu = quat.menu || {};

quat.menu.MenuLayer = cc.Layer.extend({
    ctor: function(gameBounds, fontSize) {
        this._super();

        this.gameBounds = gameBounds;
        this.fontSize = fontSize;

        return true;
    },

    

    onEnter: function() {
        this._super();

        
    },
});

