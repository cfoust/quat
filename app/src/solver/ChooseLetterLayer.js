var quat = quat || {};
quat.solver = quat.solver || {};

/* Layer for letting the user choose a new letter for a given one in
   the current word. */
quat.solver.ChooseLetterLayer = cc.Layer.extend({
    ctor:function (width, height, fontSize) {
        this._super();
        this.fontSize = fontSize;
        var fontGap = 10;
        var fontTotal = (fontSize + fontGap * 2);

        // We calculate how many letters can fit on the screen with our params
        var letterPoolCount = Math.ceil(height / fontSize) + 1;

        // Total height of all the letters in the alphabet
        var totalHeight = 26 * fontTotal;

        // Create a pool because we only need so many
        var letterPool = [];
        for (var i = 0; i < letterPoolCount; i++) {
            // Initialize the label
            var letterLabel = new cc.LabelTTF("A", "Arial", fontSize);
            letterLabel.x = (width / 2);
            letterLabel.y = (fontTotal / 2) + fontSize + (i * fontSize);
			letterLabel.setColor(cc.color(176,196,222,255));
            // letterLabel.y = (fontTotal / 2) + (i * fontSize);
            letterLabel.zIndex = 1;
            this.addChild(letterLabel);
            letterPool.push(letterLabel);
        }
        this.letterPool = letterPool;

        // Add a background behind the letter selector
        var colorBackground = new cc.LayerColor(cc.color(25,25,112,255));

        // Make it the same dimensions as the selector
        colorBackground.width = width;
        colorBackground.height = height;

        // Place it above the goal word
        colorBackground.y = (fontTotal / 2) + fontSize / 2;

        // Make it so the letters sit above it
        colorBackground.zIndex = 0;


        this.colorBackground = colorBackground;
        this.addChild(colorBackground);

        this.uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

        return true;
        

        var uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
        var offsetMajor = 0;
        var pos = 0;
        // Scrolls the letters to a certain offset
        var tletter = 0;
        var setScroll = function(offset) {
            /* If this isn't in here, things get messy.
               Yeah, we could fix this in the future to work like it should,
               but that's an S.E.P. if I've ever seen one.*/
            if ((offset % 100) == 0) {
                offset += .001;
            }

            /* Modulus has odd behavior in JS, have to use other logic*/
            if (offset < 0) {
                offset += totalHeight;
            } else {
                offset = offset % totalHeight;
            }

            // We have to inverse the offset because A-Z goes from top to bottom
            var relativeDiff = totalHeight - offset;
            // Get the index of the LAST letter displayed on the screen 
            var letter = (relativeDiff - (relativeDiff % font_total)) / font_total;
            // Get its location on the screen
            var location = -1*(offset % font_total) + (font_total / 2);

            // Iterate through all our letter objects
            for (var i = 0; i < letterPool.length; i++) {
                var letterObj = letterPool[i];
                letterObj.y = location + (i * font_total);

                var letterIndex = (letter - i + 1) % 26;
                
                if (letterIndex < 0) {
                    letterIndex += 26;
                }

                letterObj.string = uppercase[letterIndex % 26];
            }
        }

        var shown = false;
        var hideScroll = function() {
            shown = false;
            for (var i = 0; i < letterPool.length; i++) {
                letterPool[i].setOpacity(0);
            }
        }
        var showScroll = function(region) {
            shown = true;
            for (var i = 0; i < letterPool.length; i++) {
                var letterObj = letterPool[i];
                letterObj.x = (region * fourths) + (fourths / 2);
                letterObj.setOpacity(255);
            }
        }

        
        cc.eventManager.addListener({
            event: cc.EventListener.MOUSE,
            onMouseMove: function(event){
                if (!shown) {
                    return;
                }

                var delta = pos - event.getLocationY();
                // delta *= -1;
                setScroll(offsetMajor + delta);
            },
            onMouseUp: function(event){
                hideScroll();
            },
            onMouseDown: function(event){
                var x = event.getLocationX();

                // Records the original click position
                pos = event.getLocationY();

                // Gets the region the click was in (there are four, 0-3)
                var loc = (x - (x % fourths)) / fourths;
                
                // The letter (of LAKE) that we get the index of
                var letter = word[loc].charCodeAt(0) - 65;

                var offset = (totalHeight - (letter * font_total));
                

                offset = offset - (size.height / 2) + font_total / 2;

                // Remember the original offset we were at
                offsetMajor = offset;

                // Set the scroll position (should keep letter in middle)
                setScroll(offset);

                showScroll(loc);
            },
            onMouseScroll: function(event){
            }
        },colorBackground);

        return true;
    },

    redrawFromLetter: function(letter) {
        var uppercase = this.uppercase;
        var index = letter.charCodeAt(0) - 65;

        for (var i = 0; i < this.letterPool.length; i++) {
            var letterLabel = this.letterPool[i];
            var newIndex = (index - i) % uppercase.length;
            if (newIndex < 0) {
                newIndex += uppercase.length;
            }
            letterLabel.string = uppercase[newIndex];
        }
    },

    setBaseLetter: function(letter) {
        letter = letter.toUpperCase();
        this.redrawFromLetter(letter);
        this.baseLetterIndex = letter.charCodeAt(0) - 65;
    },

    getBaseLetter: function() {
        return this.letterPool[0].string;
    },

    setOffset: function(offset) {
        var newIndex = this.baseLetterIndex + Math.floor(offset / this.fontSize);
        newIndex %= this.uppercase.length;
        if (newIndex < 0) {
            newIndex += this.uppercase.length;
        }
        this.redrawFromLetter(this.uppercase[newIndex]);
    },
	
	shift: function(delta) {
		var newIndex = this.baseLetterIndex + delta;
		newIndex %= this.uppercase.length;
        if (newIndex < 0) {
            newIndex += this.uppercase.length;
        }
		this.setBaseLetter(this.uppercase[newIndex]);
	}
});