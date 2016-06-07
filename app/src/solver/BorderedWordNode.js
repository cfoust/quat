var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.BorderedWordNode = quat.solver.WordNode.extend({

	applyTheme: function(theme) {
        this._super(theme);

        this.setColor(this.default);

    },

    /**
     * Creates a WordNode with the given font size.
     * @param  {number} fontSize The size of the font to be initialized.
     * @param  {number} fontGap The distance between each letter.
     */
    ctor: function (fontSize, fontGap) {
        this._super(fontSize, fontGap);

        this.default = cc.color(255,255,255,64),
        this.selected = cc.color(255,255,255,153);

        var borders = [],
            fills = [],
        	size = fontSize * 1.25,
        	radius = fontSize * 0.24,
        	width = fontSize * 0.17;

        // Iterate through and create the rectangles
        for (var j = 0; j < 4; j++) {

            // Set up the border rectangle
            var border = new quat.RectRadius(size, size, radius, width, false),
            	bound = this.bounds[j];

            // Set them to be hidden
            border.x = bound.x + (bound.width / 2);
            border.y = bound.y + (bound.height / 2);
            border.zIndex = 1;

			border.setColor(cc.color(255,255,255,255));
            // Add it as a child to this layer
            this.addChild(border);

            borders.push(border);

            // Set up the fill rectangle
            var fill = new quat.RectRadius(size, size, radius, width, true);

            // Set them to be hidden
            fill.x = bound.x + (bound.width / 2);
            fill.y = bound.y + (bound.height / 2);
            fill.zIndex = 0;

            fill.setColor(this.default);
            // Add it as a child to this layer
            this.addChild(fill);

            fills.push(fill);
        }
        this.borders = borders;
        this.fills = fills;

        return true;
    },

    select: function(col) {
        this.fills[col].setColor(this.selected);
    },

    unselect: function() {
        for (var j = 0; j < 4; j++) {
            var rect = this.fills[j];
            rect.setColor(this.default);
        }
    },

    setOpacity: function(opacity) {
    	this._super(opacity);

    	for (var j = 0; j < 4; j++) {
            this.borders[j].setOpacity(opacity);
            this.fills[j].setOpacity(opacity);
        }
    },

    setColor: function(color) {
    	this._super(color);

    	for (var j = 0; j < 4; j++) {
            this.borders[j].setColor(color);
            this.fills[j].setColor(color);
        }
    }
});