var quat = quat || {};
quat.menu = quat.menu || {};

quat.menu.MenuLayer = cc.Layer.extend({
    ctor: function(gameScene, gameBounds, fontSize, gameState) {
        this._super();

        this.gameScene = gameScene;
        this.gameBounds = gameBounds;
        this.fontSize = fontSize;
        this.quatGame = gameState;

        return true;
    },

    applyTheme: function(theme) {
        this.textLabel.setColor(theme.colors.text);

        for (var i = 0; i < this.buttons.length; i++) {
            this.buttons[i].applyTheme(theme);
        }
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
            "PLAY": function(self) {
                self.gameScene.SSC.GAME();
            },
        	"LOOK": function(self) {
        		self.gameScene.SSC.LOOK();
        	},
        	"STATS": function(self) {
        		self.gameScene.SSC.STATS();
        	},
        	"ABOUT": function(self) {
        		self.gameScene.SSC.ABOUT();
        	}
        };

        var buttonHeight = fontSize * 1.3,
        	buttonGap = buttonHeight * 1.1,
            numButtons = Object.keys(buttons).length;

        // Calculate the offset needed to center all of the buttons
        var totalHeight = fontSize + (numButtons * buttonGap);
            offset = (((1 - (fontSize / totalHeight)) * totalHeight) - (totalHeight / 2)) / 2;
        // I have no idea why that worked but #yolo

        // Reset the offset of the QUAT label
        textLabel.y += offset;

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
	        menuButton.y = gameBounds.y + (gameBounds.height / 2) + (-buttonGap * i) + offset;
	        this.addChild(menuButton);
	        this.buttons.push(menuButton);
        }
        
    },

    setOpacity: function(opacity) {
    	this.textLabel.setOpacity(opacity);

    	for (var i = 0; i < this.buttons.length; i++) {
    		this.buttons[i].setOpacity(opacity);
    	}
    },

    setVisible: function(visibile) {
    	this._super(visibile);

    	if (!this.buttons) {
    		return;
    	}
    	
    	for (var i = 0; i < this.buttons.length; i++) {
    		this.buttons[i].setVisible(visibile);
    	}
    }
});

