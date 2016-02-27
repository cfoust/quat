var quat = quat || {};
quat.stats = quat.stats || {};

quat.stats.StatLayer = cc.Layer.extend({
    ctor: function(fontSize, leftSize, rightSize) {
        this._super();

        this.fontSize = fontSize;
        this.leftSize = leftSize;
        this.rightSize = rightSize;

        return true;
    },

    applyTheme: function(theme) {
        this.leftLabel.setColor(theme.colors.text);
        this.rightLabel.setColor(theme.colors.darkForeground);
    },

    onEnter: function() {
        this._super();

        var fontSize = this.fontSize * .8,
            leftSize = this.leftSize,
            rightSize = this.rightSize;
        
        // Sets up the title label
        var leftLabel = new cc.LabelTTF("QUAT", "Ubuntu", fontSize, null, cc.TEXT_ALIGNMENT_RIGHT);
        leftLabel.x = (leftSize / 2) * 0.9;
        leftLabel.boundingWidth = leftSize;
        leftLabel.zIndex = 1;
        this.leftLabel = leftLabel;
        this.addChild(leftLabel);
        leftLabel.string = "2500000000";

        // Sets up the title label
        var rightLabel = new cc.LabelTTF("QUAT", "Ubuntu", fontSize, null, cc.TEXT_ALIGNMENT_LEFT);
        rightLabel.x = leftSize + (rightSize / 2) * 1.1;
        rightLabel.boundingWidth = rightSize;
        rightLabel.zIndex = 1;
        this.rightLabel = rightLabel;
        this.addChild(rightLabel);
        rightLabel.string = "POINTS";
    },

    setLeft: function(text) {
        this.leftLabel.string = text;
    },

    setRight: function(text) {
        this.rightLabel.string = text;
    },

    setOpacity: function(opacity) {
        this.leftLabel.setOpacity(opacity);
        this.rightLabel.setOpacity(opacity);
    },

    setVisible: function(visibile) {
        this.leftLabel.setVisible(visibile);
        this.rightLabel.setVisible(visibile);
    }
});

