var quat = quat || {};

// Colored background layer
quat.BackgroundLayer = cc.Layer.extend({
    ctor:function () {
        this._super();

        var colorBackground = new cc.LayerColor(cc.color(0,0,205,255));

        this.colorBackground = colorBackground;
        this.addChild(colorBackground);

        return true;
    },

    applyTheme: function(theme) {
    	this.colorBackground.setColor(theme.colors.background);
    }
});