var quat = quat || {};
quat.menu = quat.menu || {};

quat.menu.Button = cc.Layer.extend({
    ctor: function(title, fontSize, width, height, callback) {
        this._super();

        this.title = title;
        this.width = width;
        this.height = height;
        this.fontSize = fontSize;
        this.callback = callback;

        return true;
    },

    

    onEnter: function() {
        this._super();

        // var gameBounds = this.gameBounds,
        // 	fontSize = this.fontSize;

        var textLabel = new cc.LabelTTF(this.title, "Ubuntu", this.fontSize, null, cc.TEXT_ALIGNMENT_CENTER);
        textLabel.x = this.width / 2;
        textLabel.y = this.height / 2;
        textLabel.boundingWidth = this.width;
        textLabel.zIndex = 2;
        this.textLabel = textLabel;
        this.addChild(textLabel);

        var defaultColor = cc.color(0,0,128,255),
            selectedColor = cc.color(0,191,255,255);
        
        // The button's background
        var background = new cc.LayerColor(defaultColor);
        background.width = this.width;
        background.height = this.height;
        background.zIndex = 1;
        this.background = background;
        this.addChild(background);


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
                if (!button.isVisible()) {
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

                button.background.setColor(selectedColor);

                return true;
            },
            onTouchMoved: function(event) {
                var insideThis = contains(event);
                if (trackingTouch && !insideThis) {
                    trackingTouch = false;
                    button.background.setColor(defaultColor);
                }
                else if (!trackingTouch && insideThis) {
                    trackingTouch = true;
                    button.background.setColor(selectedColor);
                }
            },
            onTouchEnded: function(event){
                if (contains(event)) {
                    button.callback();
                }
                button.background.setColor(defaultColor);
                trackingTouch = false;
                return true;
            }
        },this);
    },

    setOpacity: function(opacity) {
        this.textLabel.setOpacity(opacity);
    	this.background.setOpacity(opacity);
    }
});

