var quat = quat || {};
quat.solver = quat.solver || {};

// Colored background layer
quat.solver.BackgroundLayer = cc.Layer.extend({
    ctor:function () {
        this._super();

        var colorBackground = new cc.LayerColor(cc.color(0,0,205,255));

        this.colorBackground = colorBackground;
        this.addChild(colorBackground);

        return true;
    }
});