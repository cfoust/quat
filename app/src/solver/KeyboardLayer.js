var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.KeyboardLayer = cc.Layer.extend({
    ctor:function (gameBounds, fontSize) {
        cc.log(gameBounds,fontSize);
        this._super();

        this.gameBounds = gameBounds;

        this.rows = [
            'QWERTYUIOP',
            'ASDFGHJKL',
            'ZXCVBNM'
        ];

        var width = this.width,
            height = this.height,
            gameBounds = this.gameBounds;

        // Sets a baseline for how high the keyboard should be.
        // We scale down from this until it fits, as this is the max.
        var keyboardHeight = gameBounds.height * 0.30,
            keyboardY = (gameBounds.height / 2)  - (keyboardHeight - (fontSize * 0.2));

        // Ratio of width over height
        var ratio = 2.265;

        // Figure out how wide the keyboard should be
        var keyboardWidth = ratio * keyboardHeight;
        
        // If the keyboard is bigger than the view
        if (width < keyboardWidth) {
            // Recalculates the keyboard to be that width
            keyboardWidth = width;
            keyboardHeight = (1 / ratio) * keyboardWidth;
        }

        // Calculate the key sizes and bounds
        var halfWidth = keyboardWidth / 2,
            keyHeight = keyboardHeight * 0.27,
            keyFontSize = keyHeight * 0.6,
            // keyWidth = keyboardWidth * 0.09,
            keyWidth = keyboardWidth * 0.080,
            verticalGap = keyboardHeight * 0.07,
            horizontalGap = keyboardWidth * 0.02;

        // The offsets to make the keyboard staggered like a real one
        var offsets = [
            0,
            keyboardWidth * 0.05,
            keyboardWidth * 0.16
        ];

        // Generate all the buttons with some magic
        for (var j = 0; j < this.rows.length; j++) {
            for (var i = 0; i < this.rows[j].length; i++) {
                var button = new quat.menu.Button(this.rows[j].charAt(i), keyFontSize, keyWidth, keyHeight, null);
                button.x = (width / 2) + offsets[j] + (i * (horizontalGap + keyWidth)) - halfWidth + (horizontalGap / 2);
                button.y = ((this.rows.length - (j+1)) * (keyHeight + verticalGap)) + (height * 0.02) + keyboardY;
                this.addChild(button);
            }
        }

        this.keyBounds = cc.rect((width / 2) - keyboardWidth / 2,keyboardY,keyboardWidth, keyboardHeight);
        

        return true;
    },

    pointInKeyboard: function(point) {
        return cc.rectContainsPoint(this.keyBounds, point);
    },

    pointInLetter: function(point) {
        var children = this.children;
        for (var i = 0; i < this.childrenCount; i++) {
            var child = children[i],
                bound = child.getBoundingBox();
            if (cc.rectContainsPoint(bound, point)) {
                return child.textLabel.string;
            }
        }

        return false;
    },

    applyTheme: function(theme) {
        var children = this.children;
        for (var i = 0; i < this.childrenCount; i++) {
            var obj = children[i];
            obj.applyTheme(theme);
        }
    },
});