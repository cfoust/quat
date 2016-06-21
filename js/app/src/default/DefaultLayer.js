var quat = quat || {};
quat.default = quat.default || {};

quat.default.DefaultLayer = cc.Layer.extend({
    ctor: function(gameBounds, fontSize) {
        this._super();

        this.fontSize = fontSize;
        this.gameBounds = gameBounds;

        return true;
    },

    applyTheme: function(theme) {
        this.text.setColor(theme.colors.text);
    },

    onEnter: function() {
        this._super();

        var fontSize = this.fontSize,
            gameBounds = this.gameBounds;


        var text = new cc.LabelTTF("QUAT", "Ubuntu", fontSize * 1.5, null, cc.TEXT_ALIGNMENT_CENTER);

        text.x = gameBounds.x + (gameBounds.width / 2);
        text.y = gameBounds.y + (gameBounds.height * 0.75);
        text.boundingWidth = gameBounds.width;
        this.addChild(text);
        this.text = text;
        
    },

    setOpacity: function(opacity) {
        this.text.setOpacity(opacity);
    },

    setVisible: function(visibile) {
        this.text.setVisible(visibile);
    }
});

