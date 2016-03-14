var quat = quat || {};

/*
Layer that controls a DrawNode for the purpose of drawing rectangles with 
borders of a certain radius.
 */
quat.RectRadius = cc.Layer.extend({
    /**
     * @param  {Number} width sets the width of the rectangle.
     * @param  {Number} height sets the height of the rectangle.
     * @param  {Number} borderRadius is the radius of the border edges in pixels.
     * @param  {[type]}
     * @return {[type]}
     */
    ctor:function (width, height, borderRadius, borderWidth, filled) {
        this._super();

        this._width = width;
        this._height = height;

        // Handle bad inputs (if there isn't enough space for this radius)
        var doubleBorder = borderRadius * 2;
        if (doubleBorder > width) {
            borderRadius = width / 2;
        }
        if (doubleBorder > height) {
            borderRadius = height / 2;
        }

        this._borderWidth = borderWidth;
        this._filled = filled;

        this.node = new cc.DrawNode();
        this.node.x = 0;
        this.node.y = 0;
        this.addChild(this.node);

        // Sets up the variables for generating a quarter of a circle
        var points = 30, // Number of points (steps, more is smoother)
            curve = [],
            step = (Math.PI/2) / points, // Step size
            radius = borderRadius; // Circle radius

        // Go through and generate the points
        for (var i = 0; i < points; i++) {
            var angle = i*step;
            var p = cc.p(radius * Math.cos(angle), radius * Math.sin(angle));
            curve.push(p);
        }

        var points = [],
            diffX = (width / 2) - borderRadius,
            diffY = (height / 2) - borderRadius;
        for (var i = 0; i < 4; i++) {
            var dx = 1,
                dy = 1;

            // Sets the way the curve is reflected
            dx *= ((i == 1) || (i == 2)) ? -1 : 1;
            dy *= ((i == 2) || (i == 3)) ? -1 : 1;

            // Iterate over the curve points
            for (var j = 0; j < curve.length; j++) {
                var p = null;

                // These if statements correct the orientation of the curve
                if ((i == 1) || (i == 3)) {
                    p = cc.p(curve[(curve.length - 1) - j]);
                } else {
                    p = cc.p(curve[j]);
                }

                p.x += diffX;
                p.y += diffY;

                p.x *= dx;
                p.y *= dy;
                points.push(p);
            }
        }
        this.points = points;
        this.color = cc.color.RED;


        this.drawRect();

        return true;
    },

    drawRect: function() {
        var node = this.node,
            borderWidth = this._borderWidth,
            filler = this._filled ? this._color : null;
        node.clear();
        node.drawPoly(this.points, filler, borderWidth, this._color);
    },

    setColor: function(color) {
    	this._color = color;
        this.drawRect();
    },

    setOpacity: function(opacity) {
        this._color.a = opacity;
        this.drawRect();
    }
});