var quat = quat || {};
quat.solver = quat.solver || {};

// Colored background layer
quat.solver.BackgroundLayer = cc.Layer.extend({
    ctor:function () {
        this._super();

        var colorBackground = new cc.LayerColor(cc.color(63,74,33,255));

        this.colorBackground = colorBackground;
        this.addChild(colorBackground);

        return true;
    }
});