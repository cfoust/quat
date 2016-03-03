var quat = quat || {};
quat.solver = quat.solver || {};

/* A conglomeration of four labels we use to display a word. */
quat.solver.WordNode = cc.Node.extend({
    /**
     * Creates a WordNode with the given font size.
     * @param  {number} fontSize The size of the font to be initialized.
     * @param  {number} fontGap The distance between each letter.
     */
    ctor: function (fontSize, fontGap) {
        this._super();

        // Store these for later
        this.fontSize = fontSize;
        this.fontGap = fontGap;

        // Create a pool of labels we can use to draw this word
        var rowPool = []
        for (var j = 0; j < 4; j++) {
            var letterLabel = new cc.LabelTTF("A", "Ubuntu", fontSize);

            // Set them to be hidden
            letterLabel.x = (j * this.fontGap);
            letterLabel.y = 0;

            // letterLabel.setColor(cc.color(176,196,222,255));
			letterLabel.setColor(cc.color(255,255,255,255));
            // Add it as a child to this layer
            this.addChild(letterLabel);

            rowPool.push(letterLabel);
        }
        this.rowPool = rowPool;

        return true;
    },

    

    /**
     * Replaces the text of this word with a given word.
     * @param  {[type]} word [description]
     */
    changeWord: function(word) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.rowPool[j];
            letterLabel.string = word[j].toUpperCase();
        }
    },

    setColor: function(color) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.rowPool[j];
            letterLabel.setColor(color);
            letterLabel.setVisible(false);
            letterLabel.setVisible(true);
        }
    },

    setOpacity: function(opacity) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.rowPool[j];
            letterLabel.setOpacity(opacity);
        }
    }
});