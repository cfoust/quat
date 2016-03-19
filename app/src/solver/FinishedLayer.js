var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.FinishedLayer = cc.Layer.extend({
    ctor:function (fontSize, gameBounds) {
        this._super();

        // Sets up the text string
        var text = new cc.LabelTTF("PUZZLE DONE", "Ubuntu", fontSize*.45, null, cc.TEXT_ALIGNMENT_CENTER);
        text.x = gameBounds.x + (gameBounds.width / 2);
        text.y = gameBounds.y + (gameBounds.height * 0.75);
        text.opacity = 0;
        this.text = text;
        this.addChild(text);

        // Bigger icon above it
        var icon = new cc.LabelTTF("\uf058", "FontAwesome", fontSize * 1.5, null, cc.TEXT_ALIGNMENT_CENTER);
        icon.x = gameBounds.x + (gameBounds.width / 2);
        icon.y = text.y + fontSize;
        icon.opacity = 0;
        this.icon = icon;
        this.addChild(icon);

        // The animation sequence used to bring this layer in and out
        this.sequence = cc.sequence(
            cc.fadeIn(0.3),
            cc.delayTime(2),
            cc.fadeOut(0.3)
        );

        return true;
    },

    /**
     * Sets the title and icon, then fades in and out.
     * @param  {String} title     Subtext under the icon.
     * @param  {String} charPoint Codepoint for the icon.
     */
    run: function(title, charPoint) {
        var text = this.text,
            icon = this.icon;

        text.setVisible(false);
        icon.setVisible(false);

        text.setOpacity(0);
        icon.setOpacity(0);

        text.string = title;
        icon.string = charPoint;

        text.stopAllActions();
        icon.stopAllActions();

        text.setVisible(true);
        icon.setVisible(true);

                                            text.runAction(cc.sequence(
                                                                       cc.fadeIn(0.3),
                                                                       cc.delayTime(2),
                                                                       cc.fadeOut(0.3)
                                                                       ));
                                            icon.runAction(cc.sequence(
                                                                       cc.fadeIn(0.3),
                                                                       cc.delayTime(2),
                                                                       cc.fadeOut(0.3)
                                                                       ));
    },

    /**
     * Indicates that the user finished a puzzle.
     */
    done: function() {
        this.run("PUZZLE DONE", "\uf058");
    },

    /**
     * Indicates that the user made par when finishing a puzzle.
     */
    par: function() {
        this.run("MADE PAR!", "\uf118");
    },

    applyTheme: function(theme) {
        this.text.setColor(theme.colors.text);
        this.icon.setColor(theme.colors.text);
    },

    setOpacity: function(opacity) {
        this.text.setOpacity(opacity);
    	this.icon.setOpacity(opacity);
    },
});