var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.BorderedWordNode = quat.solver.WordNode.extend({

	applyTheme: function(theme) {
        this._super(theme);

        for (var j = 0; j < 4; j++) {
            var rect = this.rects[j];
            rect.setColor(theme.colors.darkForeground);
        }
    },

    /**
     * Creates a WordNode with the given font size.
     * @param  {number} fontSize The size of the font to be initialized.
     * @param  {number} fontGap The distance between each letter.
     */
    ctor: function (fontSize, fontGap) {
        this._super(fontSize, fontGap);

        var rects = [],
        	size = fontSize * 1.1,
        	radius = fontSize * 0.2,
        	width = fontSize * 0.08;

        // Iterate through and create the rectangles
        for (var j = 0; j < 4; j++) {
            var rect = new quat.RectRadius(size, size, radius, width, false),
            	bound = this.bounds[j];

            // Set them to be hidden
            rect.x = bound.x + (bound.width / 2);
            rect.y = bound.y + (bound.height / 2);

			rect.setColor(cc.color(255,255,255,255));
            // Add it as a child to this layer
            this.addChild(rect);

            rects.push(rect);
        }
        this.rects = rects;

        return true;
    },

    setOpacity: function(opacity) {
    	this._super(opacity);

    	for (var j = 0; j < 4; j++) {
            var rect = this.rects[j];
            rect.setOpacity(opacity);
        }
    },

    setColor: function(color) {
    	this._super(color);

    	for (var j = 0; j < 4; j++) {
            var rect = this.rects[j];
            rect.setColor(color);
        }
    }
});