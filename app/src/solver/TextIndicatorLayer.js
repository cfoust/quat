var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.TextIndicatorLayer = cc.Layer.extend({
    ctor:function (fontSize, gameBounds) {
        this._super();

        var textLabel = new cc.LabelTTF("", "Ubuntu", fontSize*.5, null, cc.TEXT_ALIGNMENT_CENTER);
        textLabel.x = gameBounds.x + (gameBounds.width / 2);
        textLabel.y = gameBounds.y + (gameBounds.height * 0.37);
        textLabel.boundingWidth = gameBounds.width;
        textLabel.opacity = 0;
        textLabel.string = "";
        this.textLabel = textLabel;
        this.addChild(textLabel);

        this._messages = [];
        this._animating = false;
        this._displayingSticky = false;
        this._stickyVisible = false;

        return true;
    },

    applyTheme: function(theme) {
        this.textLabel.setColor(theme.colors.text);
    },

    setOpacity: function(opacity) {
    	this.textLabel.setOpacity(opacity);
    },

    setAnimating: function() {
        this._animating = true;
    },

    setNotAnimating: function() {
        this._animating = false;
    },

    resetOpacity: function() {
    	this.textLabel.setOpacity(0);
    },

    _displayMessageWeb: function(message) {
        var sticky = message.sticky,
            text = message.text,
            // Some placeholders that don't impede on the sequence
            // if they don't need to be used
            begin = cc.delayTime(0),
            end = cc.delayTime(0),
            retry = cc.delayTime(0),
            reset = cc.callFunc(this.resetOpacity, this);

        // Have to fade out the current text if it's sticky
        if (this._displayingSticky) {
            begin = cc.fadeOut(0.25);
        }
        this.setVisible(true);

        if (sticky) {
            // We can assume this is the only sticky message in the queue
            this._displayingSticky = true;

            // We push it back on in case another message comes along and
            // we want to return to the sticky message
            this._messages.push(message);

            fade = this.fadeIn;

            end = cc.callFunc(function(){
                this._stickyVisible = true;
            }, this);

        } else {
            this._stickyVisible = false;

            reset = cc.delayTime(0);

            this.stopAllActions();
        
            // Fade out the word after 5 seconds
            end = cc.sequence(
                cc.delayTime(5),
                cc.fadeOut(0.25)
            );
        }

        this._animating = true;

        var sequence = cc.sequence(
            // Generic begin action for fading out if necessary
            begin,

            // cc.hide(),
            
            // Reset the opacity to 0
            reset,

            // Set the text string to the new message text
            cc.callFunc(function(text) { return function(){
                this.textLabel.string = text;
            };}(text), this),

            // cc.show(),

            // Fade in
            cc.fadeIn(0.25),

            // Do the rest of what we needed to do:
            // * If this one was sticky, it will just stay faded in
            // * If this one was normal, it will fade out
            end,

            // Make it known that this isn't animating anymore
            cc.callFunc(function(){this._animating = false;}, this),

            cc.callFunc(function(){
                if ((this._stickyVisible) && (this._messages.length == 1)) {
                    return;
                }
                this.displayMessage()
            }, this)
        );

        // Run the animation
        this.runAction(sequence);
    },

    _displayMessageNative: function(message) {
        var sticky = message.sticky,
            text = message.text,
            textLabel = this.textLabel;

        textLabel.setVisible(false);
        textLabel.string = text;
        if (sticky) {
            textLabel.setOpacity(255);
            textLabel.setVisible(true);
            this._messages.push(message);
        } else {
            cc.log("Trying to display message");

            textLabel.setVisible(false);
            textLabel.setOpacity(0);
            textLabel.string = text;
            textLabel.stopAllActions();
            textLabel.setVisible(true);
            textLabel.runAction(cc.sequence(
               cc.fadeIn(0.3),
               cc.delayTime(2),
               cc.fadeOut(0.3),
               cc.callFunc(function(){
                    if ((this._stickyVisible) && (this._messages.length == 1)) {
                        return;
                    }
                    this.displayMessage()
                }, this)
            ));
        }
    },

    displayMessage: function() {
        if (this._messages.length == 0) {
            return;
        }

        var message = this._messages.pop();
        if (cc.sys.isNative) {
            this._displayMessageNative(message);
        } else {
            this._displayMessageWeb(message);
        }
    },

    addMessage: function(text, sticky) {
        var sticky = sticky || false;
        if (this._displayingSticky && sticky) {
            return;
        }
        this._messages.push({text: text, sticky: sticky});
        this.displayMessage();
    },

    clearMessages: function() {
        this.stopAllActions();
        this._messages = [];
        this._displayingSticky = false;
        this.resetOpacity();
        this.textLabel.string = "";
    },
});