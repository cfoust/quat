var quat = quat || {};
quat.stats = quat.stats || {};

quat.stats.StatsLayer = cc.Layer.extend({
    ctor: function(gameScene, gameBounds, fontSize, gameState) {
        this._super();

        this.gameScene = gameScene;
        this.gameBounds = gameBounds;
        this.fontSize = fontSize;
        this.quatGame = gameState;

        return true;
    },

    applyTheme: function(theme) {
        for (var i = 0; i < this.stats.length; i++) {
            var stat = this.stats[i];
            stat.object.applyTheme(theme);
        }
        this.colorBackground.setColor(theme.colors.lightForeground);
    },

    updateData: function() {
        var game = this.quatGame;
        for (var i = 0; i < this.stats.length; i++) {
            var stat = this.stats[i];
            stat.object.setLeft(stat.func(this, game));
        }
    },

    milliToString: function(milli) {
        var str = "";

        var second = 1000,
            minute = second * 60,
            hour = minute * 60,
            day = hour * 24;


        // This could be a lot shorter but it's a direct copy of a function
        // I wrote in 2007. There's some nostalgia here
        
        if (milli > day) {
            str += ((milli - (milli % day)) / day).toString() + "d";
            milli %= day;
        }

        if (milli > hour) {
            str += ((milli - (milli % hour)) / hour).toString() + "h";
            milli %= hour;
        }

        if (milli > minute) {
            str += ((milli - (milli % minute)) / minute).toString() + "m";
            milli %= minute;
        }

        if (milli > second) {
            str += ((milli - (milli % second)) / second).toString() + "s";
            milli %= second;
        }

        return str;
    },

    onEnter: function() {
        this._super();

        var gameBounds = this.gameBounds,
        	fontSize = this.fontSize * .6,
            leftSize = gameBounds.width * .6,
            rightSize = gameBounds.width * .6,
            gap = fontSize;

        var dataPoints = {
            POINTS: function(self, game) {
                return game.getUser().getPoints();
            },
            PUZZLES: function(self, game) {
                return game.getUser().getPuzzlesPlayed();
            },
            PLAYED: function(self, game) {
                return self.milliToString(game.getUser().getTimePlayed());
            },
            "AVG.": function(self, game) {
                return "28s";
            },
            "P's": function(self, game) {
                return "3";
            }
        };

        var keys = Object.keys(dataPoints),
            stats = [];
        for (var i = 0; i < keys.length; i++) {
            var key = keys[i];

            // Displays points
            var stat = new quat.stats.StatLayer(fontSize, leftSize, rightSize);
            stat.x = gameBounds.x;
            stat.y = gameBounds.y + gameBounds.height + (-1 * gap * (i + 1));
            stat.zIndex = 1;
            this.addChild(stat);
            stat.setRight(key);

            stats.push({
                object: stat,
                func: dataPoints[key]
            });
        }
        this.stats = stats;

        this.updateData();


        // Long background on the right
        var colorBackground = new cc.LayerColor(cc.color(0,0,205,255));
        colorBackground.width = rightSize;
        colorBackground.height = gameBounds.height;
        colorBackground.x = gameBounds.x + leftSize;
        colorBackground.zIndex = 0;
        this.colorBackground = colorBackground;
        this.addChild(colorBackground);
    },

    setOpacity: function(opacity) {
        for (var i = 0; i < this.stats.length; i++) {
            var stat = this.stats[i];
            stat.object.setOpacity(opacity);
        }
        this.colorBackground.setOpacity(opacity);
    },

    setVisible: function(visibile) {
        for (var i = 0; i < this.stats.length; i++) {
            var stat = this.stats[i];
            stat.object.setVisible(visibile);
        }
        this.colorBackground.setVisible(visibile);
    }
});

