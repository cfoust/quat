var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.TextIndicatorLayer = cc.Layer.extend({
    ctor:function (fontSize, gameBounds) {
        this._super();

        // "BAKE->HATE\nYOU: 5\nPAR: 5\nSCORE:\n200"
        // "I JUST WISH SHE WOULD COME BACK."

        var textLabel = new cc.LabelTTF("", "Ubuntu", fontSize*.6, null, cc.TEXT_ALIGNMENT_CENTER);
        textLabel.x = gameBounds.x + (gameBounds.width / 2);
        textLabel.y = gameBounds.y + (gameBounds.height / 2);
        textLabel.boundingWidth = gameBounds.width;

        this.textLabel = textLabel;
        this.addChild(textLabel);

        var fadeIn = cc.fadeIn(0.25),
            fadeOut = fadeIn.reverse();

        this.fadeIn = fadeIn;
        this.fadeOut = fadeOut;

        this._messages = [];
        this._animating = false;
        this._displayingSticky = false;
        this._stickyVisible = false;

        this.resetOpacity();
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

    displayMessage: function() {
        if (this._messages.length == 0) {
            return;
        }

        var message = this._messages.pop(),
            sticky = message.sticky,
            text = message.text,
            // Some placeholders that don't impede on the sequence
            // if they don't need to be used
            begin = cc.delayTime(0),
            end = cc.delayTime(0),
            retry = cc.delayTime(0),
            reset = cc.callFunc(this.resetOpacity, this);

        // Have to fade out the current text if it's sticky
        if (this._displayingSticky) {
            begin = this.fadeOut;
        }

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
                this.fadeOut,
                cc.hide()
            );
        }

        this._animating = true;

        var sequence = cc.sequence(
            // Generic begin action for fading out if necessary
            begin,

            cc.hide(),
            
            // Reset the opacity to 0
            reset,

            // Set the text string to the new message text
            cc.callFunc(function(text) { return function(){
                this.textLabel.string = text;
            };}(text), this),

            cc.show(),

            // Fade in
            this.fadeIn,

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

        // console.log("Running animation for", text);
        // Run the animation
        this.runAction(sequence);
    },

    addMessage: function(text, sticky) {
        var sticky = sticky || false;
        this._messages.push({text: text, sticky: sticky});
        this.displayMessage();
    },

    clearMessages: function() {
        this._messages = [];
        this._displayingSticky = false;
        this.resetOpacity();
    },
});