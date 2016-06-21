var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.FinishedLayer = cc.Layer.extend({
    ctor:function (fontSize, gameBounds) {
        this._super();

        // Sets up the text string
        var text = new cc.LabelTTF("Done!", "Ubuntu", fontSize*.45, null, cc.TEXT_ALIGNMENT_CENTER);
        text.x = gameBounds.x + (gameBounds.width / 2);
        text.y = gameBounds.y + (gameBounds.height * 0.70);
        text.opacity = 0;
        text.setColor(cc.color.WHITE);
        this.text = text;
        this.addChild(text);

        return true;
    },

    /**
     * Sets the title and icon, then fades in and out.
     * @param  {String} title     Subtext under the icon.
     * @param  {String} charPoint Codepoint for the icon.
     */
    run: function(title) {
        var text = this.text,
            icon = this.icon;

        text.setVisible(false);

        text.setOpacity(0);

        text.string = title;

        text.stopAllActions();

        text.setVisible(true);

        text.runAction(cc.sequence(
           cc.fadeIn(0.3),
           cc.delayTime(2),
           cc.fadeOut(0.3)
        ));
    },

    /**
     * Indicates that the user finished a puzzle.
     */
    done: function() {
        this.run("Done!");
    },

    /**
     * Indicates that the user made par when finishing a puzzle.
     */
    par: function() {
        this.run("Perfect!");
    },

    /**
     * Shows a clickable toast.
     * @param  {String}   message  Message to show.
     * @param  {Function} callback Callback to run if the user clicks.
     */
    showToast: function(message, callback) {
    },

    applyTheme: function(theme) {
        // this.text.setColor(theme.colors.text);
    },

    setOpacity: function(opacity) {
        this.text.setOpacity(opacity);
    },
});