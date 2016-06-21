/*
File that creates some useful utilities for us to use.
 */

var quat = quat || {};

quat.fadeIn = cc.FadeIn.extend({
    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number} time time in seconds
     */
    update:function (time) {
        time = this._computeEaseTime(time);
        var fromOpacity = this._fromOpacity !== undefined ? this._fromOpacity : 255;
        this.target.setOpacity(fromOpacity + (this._toOpacity - fromOpacity) * time);
    },
});

quat.fadeOut = cc.FadeOut.extend({
    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number} time time in seconds
     */
    update:function (time) {
        time = this._computeEaseTime(time);
        var fromOpacity = this._fromOpacity !== undefined ? this._fromOpacity : 255;
        this.target.setOpacity(fromOpacity + (this._toOpacity - fromOpacity) * time);
    },
});