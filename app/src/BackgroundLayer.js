var quat = quat || {};

// Colored background layer
quat.BackgroundLayer = cc.Layer.extend({
    ctor:function () {
        this._super();

        var gradientBG = new cc.LayerGradient(cc.color('#f030b3'), cc.color('#5258fe'));
        this.gradientBG = gradientBG;
        this.addChild(gradientBG);

        return true;
    },

    applyTheme: function(theme) {
    	// this.colorBackground.setColor(theme.colors.background);
    }
});