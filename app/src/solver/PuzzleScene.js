var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.PuzzleScene = cc.Scene.extend({
    ctor: function(windowWidth, windowHeight) {
        this._super();

        this.windowWidth = windowWidth;
        this.windowHeight = windowHeight;

        return true;
    },

    /**
     * Calculates the size of the playing area based on the real resolution.
     *
     * Essentially, we can just fill the rest of the canvas up with the
     * background.
     * 
     * @return {Object} Object with 'width', 'height', 'x', and 'y'.
     */
    calculateSize: function() {
        var w = this.windowWidth,
            h = this.windowHeight,
            cWidth = 0, // The calculated width
            cHeight = h, // The calculated height (alwa)ys h)
            cX = 0, // The calculated X
            cY = 0; // The calculated Y (always 0)

        var NICE_WIDTH = 300;

        // Case 1: Landscape (and square) orientation
        if ((w >= h) || ((w < h) && (w > NICE_WIDTH))) {
            cWidth = Math.min(w, NICE_WIDTH);
            cX = (w / 2) - (cWidth / 2);
        // Case 2: Portrait orientation
        } else {
            cWidth = w;
            cX = 0;
        }

        return {
            width: cWidth,
            height: cHeight,
            x: cX,
            y: cY
        };
    },

    onEnter: function() {
        this._super();

        // Initialize the model and get a new puzzle
        var quatGame = new QuatModel();
        quatGame.newPuzzle();

        // Initialize our layers
        var backgroundLayer = new quat.solver.BackgroundLayer(),
            solutionSize = this.calculateSize(),
            fontSize = solutionSize.width * 0.18,
            solutionLayer = new quat.solver.SolutionLayer(solutionSize.width, 
                                              solutionSize.height,
                                              fontSize),
            chooseLetterLayer = new quat.solver.ChooseLetterLayer(
                                              solutionSize.width / 4,
                                              solutionSize.height,
                                              fontSize);

        chooseLetterLayer.setBaseLetter('D');
        chooseLetterLayer.setVisible(false);

        // Sets the solution layer to have its calculated bounds
        solutionLayer.x = solutionSize.x;
        solutionLayer.y = solutionSize.y;

        chooseLetterLayer.x = solutionSize.x;
        chooseLetterLayer.y = solutionSize.y;

        // Add each layer to this rendering target
        this.addChild(backgroundLayer);
        this.addChild(solutionLayer);
        this.addChild(chooseLetterLayer);

        // Have them be accessible from other methods
        this.backgroundLayer = backgroundLayer;
        this.solutionLayer = solutionLayer;
        this.chooseLetterLayer = chooseLetterLayer;

        // Update the solution layer's current status and goal
        solutionLayer.updateSolution(quatGame.getCurrentSteps());
        solutionLayer.updateGoal(quatGame.getGoal());


        // Keeps track of the current state of the UI
        var states = {
                /*
                When only the current solution progress is showing.
                 */
                IDLE: 0,
                /*
                When the user clicked on one of the letters in the current word,
                but has not dragged out of the current word yet.
                 */
                CHOOSING_LETTER: 1,
                /*
                The user has dragged out of the current word (selecting a new
                letter) and has stayed in a single column.
                 */
                CHANGING_LETTER_DRAG: 2,
                CHANGING_LETTER_NODRAG: 3,
            },
            state = states.IDLE,
            lastColumn = -1,
            lastMouseDown = {},
            previousOffset = 0;


        /**
         * Takes in a mouse (or touch) event and transposes it into
         * solution space.
         * @param  {Event} event Mouse or touch event with x and y coordinates.
         * @return {Object}       Object containing 'x' and 'y' fields that
         *                        have been moved to be in solutionLayer
         *                        space.
         */
        var transpose = function(event) {
            return {
                x: event.getLocationX() - solutionSize.x,
                y: event.getLocationY() - solutionSize.y
            };
        };

        var inputMoved = function(x,y) {
            if (state == states.CHOOSING_LETTER) {
                var currentLetter = solutionLayer.pointInCurrentWord(x,y);

                // In other words, the mouse moved out of the original area
                // And not into another letter
                if (currentLetter === false) {
                    var currentColumn = solutionLayer.pointInColumn(x,y);

                    // If the user stayed within the current column
                    if (currentColumn == lastColumn) {
                        var offset = y - lastMouseDown.y;
                        state = states.CHANGING_LETTER_DRAG;
                        chooseLetterLayer.setOffset(offset);

                    // Otherwise close everything out
                    } else {
                        state = states.IDLE;
                        chooseLetterLayer.setVisible(false);
                        return;
                    }
                } else {
                    chooseLetterLayer.x = (currentLetter * (solutionSize.width / 4)) + solutionSize.x;
                    chooseLetterLayer.setBaseLetter(quatGame.getCurrentWord()[currentLetter]);
                    lastColumn = currentLetter;
                }
            }
            else if (state == states.CHANGING_LETTER_DRAG) {
                var offset = y - lastMouseDown.y;
                // var offset = y - lastMouseDown.y;
                chooseLetterLayer.setOffset(offset);
            }
        };

        var inputDone = function(x,y) {
            var finishWord = function() {
                state = states.IDLE;
                chooseLetterLayer.setVisible(false);

                var oldWord = quatGame.getCurrentWord(),
                    newWord = oldWord.substr(0,lastColumn) + chooseLetterLayer.getBaseLetter() + oldWord.substr(lastColumn + 1);

                newWord = newWord.toLowerCase();

                var result = quatGame.addWord(newWord);
                if (result) {
                    if (quatGame.atGoal()) {
                        quatGame.newPuzzle();
                        solutionLayer.updateGoal(quatGame.getGoal());
                    }
                    solutionLayer.updateSolution(quatGame.getCurrentSteps());
                } else {
                    console.log(newWord + " is not a word");
                }
            };

            if (state == states.CHOOSING_LETTER) {
                chooseLetterLayer.setVisible(false);
                state = states.IDLE;
            }
            else if (state == states.CHANGING_LETTER_DRAG) {
                var currentLetter = solutionLayer.pointInCurrentWord(x,y);
                var currentColumn = solutionLayer.pointInColumn(x,y);

                if ((currentLetter === false) && (currentColumn !== false)) {
                    chooseLetterLayer.setBaseLetter(chooseLetterLayer.getBaseLetter());
                    state = states.CHANGING_LETTER_NODRAG;
                } else if ((currentLetter === lastColumn) && (currentColumn == lastColumn)) {
                    finishWord();
                }
            }
            else if (state == states.CHANGING_LETTER_NODRAG) {
                finishWord();   
            }
        };

        var inputBegan = function(x,y) {
            lastMouseDown = {x: x, y: y};

            if (state == states.IDLE) {
                // Check to see if this is a click in the current word
                var currentLetter = solutionLayer.pointInCurrentWord(x,y);
                if (currentLetter !== false) {
                    chooseLetterLayer.x = (currentLetter * (solutionSize.width / 4)) + solutionSize.x;
                    chooseLetterLayer.setBaseLetter(quatGame.getCurrentWord()[currentLetter]);
                    chooseLetterLayer.setVisible(true);
                    lastColumn = currentLetter;
                    state = states.CHOOSING_LETTER;
                }
            }
            else if (state == states.CHANGING_LETTER_NODRAG) {
                var currentColumn = solutionLayer.pointInColumn(x,y);

                if ((currentColumn === false) || (currentColumn != lastColumn)) {
                    chooseLetterLayer.setVisible(false);
                    state = states.IDLE;
                } 
                // else if (y >= solutionLayer.topOfCurrentWord()){
                else {
                    state = states.CHANGING_LETTER_DRAG;
                }
            }
        };

        // Touch listener
        var trackingTouch = false;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: function(event) {
                if (trackingTouch) {
                    return false;
                } else {
                    trackingTouch = true;
                }
                
                var coords = transpose(event);
                inputBegan(coords.x, coords.y);

                return true;
            },
            onTouchMoved: function(event){
                var coords = transpose(event);
                inputMoved(coords.x, coords.y);
                return true;
            },
            onTouchEnded: function(event){

                var coords = transpose(event);
                inputDone(coords.x, coords.y);
                trackingTouch = false;
                return true;
            }
        },this);

        cc.eventManager.addListener({
            event: cc.EventListener.KEYBOARD,
            onKeyReleased: function(keyCode, event){
                var key = String.fromCharCode(keyCode);

                // If key is a number string
                if (!isNaN(key)) {
                    // It is, so convert it into a number
                    var number = +key;

                    if ((number < 1) || (number > 4)) {
                        state = states.IDLE;
                        chooseLetterLayer.setVisible(false);
                        return;
                    }

                    // Shift the number down one to match the indexes of letters
                    number -= 1;

                    // Set the last
                    lastColumn = number;

                    // Let the user drag from this point on if they want
                    state = states.CHANGING_LETTER_NODRAG;

                    // Show the letter layer now
                    chooseLetterLayer.x = (number * (solutionSize.width / 4)) + solutionSize.x;
                    chooseLetterLayer.setBaseLetter(quatGame.getCurrentWord()[number]);
                    chooseLetterLayer.setVisible(true);
                    return;
                }

                // Try to understand they key as a letter
                var letterCode = (key.charCodeAt(0) - 65);

                /* 
                If we have a letter chooser open and the user enters a letter
                of the alphabet.
                */ 
                if ((state == states.CHANGING_LETTER_NODRAG) && 
                    (letterCode < 26) &&
                    (letterCode >= 0)) {

                    var oldWord = quatGame.getCurrentWord(),
                        newWord = oldWord.substr(0,lastColumn) + key + oldWord.substr(lastColumn + 1);

                    newWord = newWord.toLowerCase();

                    var result = quatGame.addWord(newWord);
                    if (result) {
                        if (quatGame.atGoal()) {
                            quatGame.newPuzzle();
                            solutionLayer.updateGoal(quatGame.getGoal());
                        }
                        solutionLayer.updateSolution(quatGame.getCurrentSteps());
                    } else {
                        console.log(newWord + " is not a word");
                    }

                    chooseLetterLayer.setVisible(false);
                    state = states.IDLE;
                }
                // If the user enters a backspace while the letter chooser
                // is shown, hide the letter chooser
                else if ((state == states.CHANGING_LETTER_NODRAG) &&
                         (keyCode == 8)) {
                    chooseLetterLayer.setVisible(false);
                    state = states.IDLE;
                }
                // If the user enters a backspace while idle, see if we
                // can remove one of the last words
                else if ((state == states.IDLE) &&
                         (keyCode == 8)) {
                    quatGame.goBack();
                    solutionLayer.updateSolution(quatGame.getCurrentSteps());
                }

            }
        }, this);

        
    }
});

