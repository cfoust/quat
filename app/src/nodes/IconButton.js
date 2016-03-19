var quat = quat || {};

quat.IconButton = cc.Node.extend({

    applyTheme: function(theme) {
        this.defaultColor = theme.colors.text;
        this.selectedColor = theme.colors.lightForeground;
        this.icon.setColor(this.defaultColor);
    },

    /**
     * @param  {Number} width sets the width of the rectangle.
     * @param  {Number} height sets the height of the rectangle.
     * @param  {Number} borderRadius is the radius of the border edges in pixels.
     * @param  {[type]}
     * @return {[type]}
     */
    ctor:function (size, iconString, callback) {
        this._super();

        this.callback = callback;

        // Always square
        this.width = size;
        this.height = size;

        var fontSize = size;

        var icon = new cc.LabelTTF(iconString, "FontAwesome", fontSize);
        icon.x = size / 2;
        icon.y = size / 2;
        this.icon = icon;
        this.addChild(icon);

        return true;
    },

    _selected: false,
    selected: function(selected) {
        if (selected) {
            if (this._invert) {
                this.icon.setColor(this.selectedColor);
            } else {
                this.icon.setColor(this.defaultColor);
            }
        } else {
            this.icon.setColor(this.defaultColor);
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

        // Touch listener
        var button = this,
            trackingTouch = false,
            contains = function(self) {
                return function(event) {
                    return cc.rectContainsPoint(self.getBoundingBox(), cc.p(event.getLocationX(), event.getLocationY()));
                };
            }(this);

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
                    button.callback();
                }
                trackingTouch = false;
                return true;
            }
        },this);
    },  

    setColor: function(color) {
    	this.icon.setColor(color);
    },

    setOpacity: function(opacity) {
        this.icon.setOpacity(opacity);
    },

    setVisible: function(visible) {
        this._super(visible);
        this.enabled(visible);
    }
});