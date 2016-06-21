var quat = quat || {};
quat.about = quat.about || {};

quat.about.AboutLayer = cc.Layer.extend({
    ctor: function(fontSize, gameBounds) {
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

        var fontSize = this.fontSize * .8,
            gameBounds = this.gameBounds;

        var text = new cc.LabelTTF("TEST", "Ubuntu", fontSize*.6, null, cc.TEXT_ALIGNMENT_CENTER);
        text.x = gameBounds.x + (gameBounds.width / 2);
        text.y = gameBounds.y + (gameBounds.height / 2);
        text.boundingWidth = gameBounds.width;
        this.addChild(text);
        this.text = text;

        text.string = "Quat was produced by a multinational NGO with the aims of unifying the human race under a love for word puzzles. All references to intellectual property, be they real or imagined, are maintained as the rights of their creators.\n\nThis one is for those golden afternoons in St. Germaine.\n\ndev@quatga.me\n@quatgame";
        text.string = text.string.toUpperCase();
    },

    setOpacity: function(opacity) {
        this.text.setOpacity(opacity);
    },

    setVisible: function(visibile) {
        this.text.setVisible(visibile);
    }
});

