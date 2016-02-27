var quat = quat || {};

quat.themes = {
	// EXAMPLE THEME:
	// // The four-letter word describing the theme
	// "NAME": {
	// 	// Details all of the colors of the theme
	// 	colors: {
	// 		// The background color
	// 		background: "#FFFFFF",
	// 		// The color of all text (except the goal word)
	// 		textColor: "#FFFFFF",
	// 		// Color used in the following places:
	// 		// * Text color for goal word
	// 		// * Background on letter chooser
	// 		// * Background on menu buttons
	// 		darkForeground: "#FFFFFF",
	// 		// Color used in the following places:
	// 		// * Background on the goal word
	// 		// * Background on menu buttons when selected
	// 		lightForeground: "#FFFFFF"
	// 	},
	// 	// List of puzzles related to this theme. These have a small chance of
	// 	// being shown while the user is playing on this theme.
	// 	puzzles: [
	// 		{
	// 			// 'text' will be automatically capitalized.
	// 			text: 'This is the text that will be displayed in the center indicator. It wraps automatically.'
	// 			start: '[four letter start word]',
	// 			end: '[four letter end word]'
	// 		}
	// 	],
	// 	// The number of points the user has to have to unlock this theme
	// 	unlock: 999
	// },
	"WASH": {
		colors: {
			background: "#0000CD",
			text: "#FFFFFF",
			darkForeground: "#000080",
			lightForeground: "#00BFFF"
		},
		puzzles: [{
			text: 'I went to bed at around 9pm. My phone pulsed with an unread text message.',
			start: 'went',
			end: 'text'
		}],
		unlock: 0
	},
	"LATE": {
		colors: {
			background: "#000000",
			text: "#FF0000",
			darkForeground: "#500000",
			lightForeground: "#B40000"
		},
		puzzles: [{
			text: 'I went to bed at around 9pm. My phone pulsed with an unread text message.',
			start: 'went',
			end: 'text'
		}],
		unlock: 20
	},
	"GAME": {
		colors: {
			background: "#8B956D",
			text: "#414141",
			darkForeground: "#6B7353",
			lightForeground: "#C4CFA1"
		},
		puzzles: [{
			text: "Did you ever notice how it doesn't list your points anywhere while you play? That seems like bad game design.",
			start: 'ever',
			end: 'play'
		}],
		unlock: 50
	},
};