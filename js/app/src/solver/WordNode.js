var quat = quat || {};
quat.solver = quat.solver || {};

/* A conglomeration of four labels we use to display a word. */
quat.solver.WordNode = cc.Node.extend({

    applyTheme: function(theme) {
        this.setColor(theme.colors.text);
    },

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

        var offset = -1 * ((fontGap * 1.5));

        // Create a pool of labels we can use to draw this word
        var letterPool = [];
        for (var j = 0; j < 4; j++) {
            var letterLabel = new cc.LabelTTF("A", "Ubuntu", fontSize);

            // Set them to be hidden
            letterLabel.x = (j * this.fontGap) + offset;
            letterLabel.y = 0;

            // letterLabel.setColor(cc.color(176,196,222,255));
			letterLabel.setColor(cc.color(255,255,255,255));
            // Add it as a child to this layer
            this.addChild(letterLabel);

            letterPool.push(letterLabel);
        }
        this.letterPool = letterPool;

        this.recalculateBounds();
        this.oldX = this.x;
        this.oldY = this.y;

        return true;
    },

    recalculateBounds: function() {
        // Don't recalculate if x hasn't moved
        if ((this.oldX == this.x) && (this.oldY == this.y)) {
            return;
        }

        var x = this.x,
            y = this.y,
            fontHeight = this.fontSize,
            fontHeightHalf = fontHeight / 2,
            fontWidth = fontHeight * 0.8,
            fontWidthHalf = fontWidth / 2,
            bounds = [];

        // Calculate bound rectangles for all the letters
        for (var j = 0; j < 4; j++) {
            var letter = this.letterPool[j];

            // Set them to be hidden
            bounds.push(cc.rect(x - letter.x - fontWidthHalf, 
                                y - fontHeightHalf,
                                fontWidth,
                                fontHeight));
        }

        // Not sure why we need this
        bounds.reverse();

        // Calculate the bound rectangle for the whole word
        var first = bounds[0],
            last = bounds[3],
            whole = cc.rect(first.x, 
                            first.y, 
                            ((last.x + last.width) - first.x),
                            first.height);

        // Store the bounds
        this.bounds = bounds;
        this.wholeBounds = whole;
        this.oldX = x;
        this.oldY = y;
    },

    pointInWord: function(point) {
        var letterPool = this.letterPool;

        this.recalculateBounds();
        
        var bounds = this.bounds;
        for (var j = 0; j < 4; j++) {
            var bound = bounds[j];
            if (cc.rectContainsPoint(bound, point)) {
                return j;
            }
        }

        return false;
    },

    pointInWhole: function(point) {
        return cc.rectContainsPoint(this.wholeBounds, point);
    },

    /**
     * Replaces the text of this word with a given word.
     * @param  {[type]} word [description]
     */
    changeWord: function(word) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.letterPool[j];
            letterLabel.string = word[j].toUpperCase();
        }
    },

    getWord: function() {
        var str = "";
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.letterPool[j];
            str += letterLabel.string;
        }
        return str;
    },

    changeLetter: function(column, letter) {
        this.letterPool[column].string = letter;
    },

    getLetter: function(column) {
        return this.letterPool[column].string;
    },

    setColor: function(color) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.letterPool[j];
            letterLabel.setColor(color);
            letterLabel.setVisible(false);
            letterLabel.setVisible(true);
        }
    },

    setOpacity: function(opacity) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.letterPool[j];
            letterLabel.setOpacity(opacity);
        }
    }
});