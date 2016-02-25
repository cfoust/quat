var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.TextIndicatorLayer = cc.Layer.extend({
    ctor:function (fontSize, gameBounds, windowWidth, windowHeight) {
        this._super();

        // "BAKE->HATE\nYOU: 5\nPAR: 5\nSCORE:\n200"
        // "I JUST WISH SHE WOULD COME BACK."

        var textLabel = new cc.LabelTTF("", "Ubuntu", fontSize*.6, null, cc.TEXT_ALIGNMENT_CENTER);
        textLabel.x = windowWidth / 2;
        textLabel.y = windowHeight / 2;
        textLabel.boundingWidth = gameBounds.width;

        this.textLabel = textLabel;
        this.addChild(textLabel);

        var shortFade = cc.fadeIn(0.25);
        this.resetOpacity();
        this.shortSeq = cc.sequence(cc.show(),
        						   shortFade, 
        						   cc.delayTime(5), 
        						   shortFade.reverse(), 
        						   cc.hide());

        // textLabel.runAction(modifyWidth);

        return true;
    },

    setOpacity: function(opacity) {
    	this.textLabel.setOpacity(opacity);
    },

    resetOpacity: function() {
    	this.textLabel.setOpacity(0);
    },

    longIn: function(text) {
    	this.textLabel.string = text;
    	this.resetOpacity();
    	this.textLabel.runAction(this.shortSeq);
    }
});