var quat = quat || {};
quat.menu = quat.menu || {};

quat.menu.Button = cc.Layer.extend({
    ctor: function(title, fontSize, width, height, callback, radius) {
        this._super();

        this.title = title;
        this.width = width;
        this.height = height;
        this.radius = radius;
        this.fontSize = fontSize;
        this.callback = callback;

        return true;
    },

    applyTheme: function(theme) {
        if (theme.colors.inverseButtons) {
            this._invert = true;
        } else {
            this._invert = false;
        }
    },

    _selected: false,
    selected: function(selected) {
        if (selected) {
            this.background.setColor(this.selectedColor);
        } else {
            this.background.setColor(this.defaultColor);
        }
        this._selected = selected;
    },

    isSelected: function() {
        return this._selected;
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

        var textLabel = new cc.LabelTTF(this.title, "Ubuntu", this.fontSize, null, cc.TEXT_ALIGNMENT_CENTER);
        textLabel.x = this.width / 2;
        textLabel.y = this.height / 2;
        textLabel.boundingWidth = this.width;
        textLabel.zIndex = 2;
        this.textLabel = textLabel;
        this.addChild(textLabel);

        this.defaultColor = cc.color(255,255,255,64),
        this.selectedColor = cc.color(255,255,255,153);

        var borderRadius = (this.radius === undefined) ? this.fontSize * 0.3 : this.radius,
            borderWidth = this.fontSize * 0.18;

        var border = new quat.RectRadius(this.width, this.height, borderRadius, borderWidth, false);
        border.x = this.width / 2;
        border.y = this.height / 2;
        border.zIndex = 1;
        border.setColor(cc.color.WHITE);
        this.addChild(border);
        this.border = border;

        var background = new quat.RectRadius(this.width, this.height, borderRadius, borderWidth, true);
        background.x = this.width / 2;
        background.y = this.height / 2;
        background.zIndex = 0;
        background.setColor(this.defaultColor);
        this.addChild(background);
        this.background = background;

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
                button.selected(true);

                return true;
            },
            onTouchMoved: function(event) {
                var insideThis = contains(event);
                if (trackingTouch && !insideThis) {
                    trackingTouch = false;
                    button.selected(false);
                }
                else if (!trackingTouch && insideThis) {
                    trackingTouch = true;
                    button.selected(true);
                }
            },
            onTouchEnded: function(event){
                button.selected(false);
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

    setOpacity: function(opacity) {
        // Set all children opacity
        var children = this.children;
        for (var i = 0; i < this.childrenCount; i++) {
            var obj = children[i];
            obj.setOpacity(opacity);
        }
    },


});

