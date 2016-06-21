var quat = quat || {};
quat.solver = quat.solver || {};



quat.solver.TapToast = cc.Layer.extend({
    ctor: function(title, width, height, callback) {
        this._super();

        this.title = title;
        this.width = width;
        this.height = height;
        this.callback = callback;

        return true;
    },

    applyTheme: function(theme) {
        this.textLabel.setColor(theme.colors.background);
        this.rect.setColor(theme.colors.text);
    },

    _enabled: true,
    enabled: function(enabled) {
        this._enabled = enabled;
    },

    isEnabled: function() {
        return this._enabled;
    },

    onEnter: function() {
        this._super();

        var height = this.height,
            width = this.width,
            fontSize = height * 0.4;

        var textLabel = new cc.LabelTTF(this.title, "Ubuntu", fontSize, null, cc.TEXT_ALIGNMENT_CENTER);
        textLabel.x = width / 2;
        textLabel.y = height / 2;
        textLabel.boundingWidth = width;
        textLabel.zIndex = 2;
        this.textLabel = textLabel;
        this.addChild(textLabel);

        var borderRadius = height * 0.2,
            borderWidth = height * 0.08;

        var rect = new quat.RectRadius(width, height, borderRadius, borderWidth, true);
        rect.x = width / 2;
        rect.y = height / 2;
        this.addChild(rect);
        rect.node.setOpacity(0);
        this.rect = rect;

        // Touch listener
        var button = this,
            trackingTouch = false,
            bounds = this.getBoundingBox(),
            contains = function(event) {
                return cc.rectContainsPoint(bounds, cc.p(event.getLocationX(), event.getLocationY()));
            };
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: false,
            onTouchBegan: function(event) {
                if (!button.isVisible() || !button.isEnabled()) {
                    return false;
                }

                if (!contains(event)) {
                    return true;
                }

                if (trackingTouch) {
                    return false;
                } else {
                    trackingTouch = true;
                }

                return true;
            },
            onTouchMoved: function(event) {
                var insideThis = contains(event);
                if (trackingTouch && !insideThis) {
                    trackingTouch = false;
                }
                else if (!trackingTouch && insideThis) {
                    trackingTouch = true;
                }
            },
            onTouchEnded: function(event){
                if (contains(event)) {
                    if (button.callback != null) {
                        button.callback();
                    }
                }
                trackingTouch = false;
                return true;
            }
        },this);
    },

    setText: function(text) {
        this.textLabel.string = text;
    },

    /**
     * Shows a clickable toast.
     * @param  {String}   message  Message to show.
     * @param  {Function} callback Callback to run if the user clicks.
     */
    showToast: function(message, callback) {

        // Follow the callback
        this.callback = callback;

        // Update the text
        this.setText(message);

        this.setOpacity(0);

        cc.log(quat.fadeIn(0.3), cc.fadeIn(0.3));

        this.runAction(cc.sequence(
            quat.fadeIn(0.3),
            cc.delayTime(8),
            quat.fadeOut(0.3)
        ));

        // var seq = cc.sequence(
        //     cc.callFunc(function(t) {
        //         return function() {
        //             t.enabled(true);};
        //     }(this)),
        //     cc.fadeIn(0.3),
        //     cc.delayTime(8),
        //     cc.fadeOut(0.3),
        //     cc.callFunc(function(t) {
        //         return function() {
        //             t.enabled(false);};
        //     }(this))
        // );

        // Run the action
        // this.textLabel.setOpacity(0);
        // this.rect.setOpacity(0);

        // this.textLabel.setVisible(true);
        // this.rect.setVisible(true);

        // cc.log("Showing toast for text", message);
        // this.textLabel.runAction(cc.sequence(
        //     cc.fadeIn(0.3),
        //     cc.delayTime(8),
        //     cc.fadeOut(0.3)
        // ));
        // this.rect.runAction(cc.sequence(
        //     cc.fadeIn(0.3),
        //     cc.delayTime(8),
        //     cc.fadeOut(0.3)
        // ));
        // this.rect.runAction(seq.clone());
    },

    getOpacity: function() {
        cc.log("getting opacity", this.opacity, this._op);
        return this._op;
    },

    setOpacity: function(opacity) {
        this._super(opacity);

        cc.log("TapToast opacity", opacity);
        // Set all children opacity
        var children = this.children;
        for (var i = 0; i < this.childrenCount; i++) {
            var obj = children[i];
            obj.setOpacity(opacity);
        }
    },
});

