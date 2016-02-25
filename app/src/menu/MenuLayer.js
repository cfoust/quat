var quat = quat || {};
quat.menu = quat.menu || {};

quat.menu.MenuLayer = cc.Layer.extend({
    ctor: function(gameBounds, fontSize) {
        this._super();

        this.gameBounds = gameBounds;
        this.fontSize = fontSize;

        return true;
    },

    

    onEnter: function() {
        this._super();

        var gameBounds = this.gameBounds,
        	fontSize = this.fontSize;

        // Sets up the title label
        var textLabel = new cc.LabelTTF("QUAT", "Ubuntu", fontSize, null, cc.TEXT_ALIGNMENT_CENTER);
        textLabel.x = gameBounds.x + (gameBounds.width / 2);
        textLabel.y = gameBounds.y + (gameBounds.height / 2) + fontSize * 2;
        textLabel.boundingWidth = gameBounds.width;
        this.textLabel = textLabel;
        this.addChild(textLabel);

        // Describes what happens when you click each menu button
        var buttons = {
        	"LOOK": function(self) {
        		console.log("LOOK AT THAT CUTIE");
        	},
        	"STATS": function(self) {
        		console.log("WHAT ARE YOUR STATS BRO?");
        	},
        	"ABOUT": function(self) {
        		console.log("TELL ME MORE ABOUT HER");
        	}
        };

        var buttonHeight = fontSize * 1.3,
        	buttonGap = buttonHeight * 1.1;

        var buttonKeys = Object.keys(buttons);
        this.buttons = [];
        for (var i = 0; i < buttonKeys.length; i++) {
        	// Grab the key (the button title)
        	var key = buttonKeys[i];

        	// Grab its callback
        	var func = buttons[key];

        	// Bake it into a contextless action
        	var action = function(self, func) {
        		return function() {
        			func(self);
        		};
        	}(this, func);

        	// Initialize a menu button
        	var menuButton = new quat.menu.Button(key, fontSize, gameBounds.width, buttonHeight, action);
	        
	        // Move it properly
	        menuButton.x = gameBounds.x;
	        menuButton.y = gameBounds.y + (gameBounds.height / 2) + (-buttonGap * i);
	        this.addChild(menuButton);
	        this.buttons.push(menuButton);
        }
        
    },

    setOpacity: function(opacity) {
    	this.textLabel.setOpacity(opacity);

    	for (var i = 0; i < this.buttons.length; i++) {
    		this.buttons[i].setOpacity(opacity);
    	}
    }
});

