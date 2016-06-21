var quat = quat || {};

quat.themes = {
	// #################################################
	//                 EXAMPLE THEME:
	// #################################################
	// 
	// // The four-letter word describing the theme
	// "NAME": {
	// 
	// 	// Details all of the colors of the theme
	// 	colors: {
	// 		// The background color
	// 		background: "#FFFFFF",
	// 		
	// 		// The color of all text (except the goal word)
	// 		textColor: "#FFFFFF",
	// 		
	// 		// Color used in the following places:
	// 		// * Text color for goal word
	// 		// * Background on letter chooser
	// 		// * Background on menu buttons
	// 		darkForeground: "#FFFFFF",
	// 		
	// 		// Color used in the following places:
	// 		// * Background on the goal word
	// 		// * Background on menu buttons when selected
	// 		lightForeground: "#FFFFFF",
	// 		
	// 		// Optional parameter that sets buttons to the following colors
	// 		// when selected:
	// 		//  	text color: darkForeground
	// 		//		background color: lightForeground
	// 		// Instead of the normal behavior.
	// 		inverseButtons: true,
	// 		
	// 		// For now, used only on the stats screen. It changes the text color
	// 		// on the right to the theme's text color instead of lightForeground
	// 		contrastText: false
	// 	},
	// 	
	// 	// List of puzzles related to this theme. These have a small chance of
	// 	// being shown while the user is playing on this theme.
	// 	puzzles: [
	// 		{
	// 			// 'text' will be automatically capitalized.
	// 			text: 'This is the text that will be displayed in the center indicator. It wraps automatically.'
	// 			start: '[four letter start word]',
	// 			end: '[four letter end word]',
	// 			par: 0
	// 		}
	// 	],
	// 	
	// 	// The number of points the user has to have to unlock this theme
	// 	unlock: 999
	// },
	"QUAT": {
		colors: {
			background: "#D29034",
			text: "#523914",
			darkForeground: "#926424",
			lightForeground: "#B87F2E"
		},
		puzzles: [],
		unlock: 0
	},
	// Revisit this theme
	// "WASH": {
	// 	colors: {
	// 		background: "#0000CD",
	// 		text: "#FFFFFF",
	// 		darkForeground: "#000080",
	// 		lightForeground: "#00BFFF"
	// 	},
	// 	puzzles: [],
	// 	unlock: 0
	// },
	"LATE": {
		colors: {
			background: "#000000",
			text: "#FF0000",
			darkForeground: "#500000",
			lightForeground: "#B40000"
		},
		puzzles: [],
		unlock: 0
	},
	
	"GAME": {
		colors: {
			background: "#8B956D",
			text: "#414141",
			darkForeground: "#6B7353",
			lightForeground: "#C4CFA1"
		},
		puzzles: [],
		unlock: 0
	},
	"SNOW": {
		colors: {
			background: "#FFFFFF",
			text: "#204C54",
			darkForeground: "#36818F",
			lightForeground: "#83C9FF"
		},
		puzzles: [],
		unlock: 200
	},
	"BOOK": {
		colors: {
			background: "#FADFAF",
			text: "#332E23",
			darkForeground: "#CC8F00",
			lightForeground: "#573526",
			inverseButtons: true
		},
		puzzles: [],
		unlock: 300
	},
	"PINE": { // Maybe revisit this one's colors
		colors: {
			background: "#002E16",
			text: "#147503",
			darkForeground: "#2B1302",
			lightForeground: "#665905",
			inverseButtons: true
		},
		puzzles: [],
		unlock: 400
	},
	"RISE": {
		colors: {
			background: "#355C7D",
			text: "#C06C84",
			darkForeground: "#6C5B7B",
			lightForeground: "#F67280"
		},
		puzzles: [],
		unlock: 500
	},
	"DEAD": {
		colors: {
			background: "#000000",
			text: "#FFFFFF",
			darkForeground: "#000000",
			lightForeground: "#FFFFFF",
			inverseButtons: true
		},
		puzzles: [],
		unlock: 600
	},

	// Revisit this theme
	// "WISH": {
	// 	colors: {
	// 		background: "#FAD6AB",
	// 		text: "#A08800",
	// 		darkForeground: "#111859",
	// 		lightForeground: "#BA9E00",
	// 	},
	// 	puzzles: [],
	// 	unlock: 0
	// },
	
	// Revisit this theme
	// "WOOD": {
	// 	colors: {
	// 		background: "#64371B",
	// 		text: "#E37D3E",
	// 		darkForeground: "#573018",
	// 		lightForeground: "#A35A2D",
	// 	},
	// 	puzzles: [],
	// 	unlock: 0
	// },
	
	"SAIL": {
		colors: {
			background: "#171857",
			text: "#E37D3E",
			darkForeground: "#331C0E",
			lightForeground: "#64371B",
		},
		puzzles: [],
		unlock: 700
	},

	// Revisit this theme
	// "DAYS": {
	// 	colors: {
	// 		background: "#00C1C2",
	// 		text: "#4F4A44",
	// 		darkForeground: "#CF9F3B",
	// 		lightForeground: "#CF9C19",
	// 		contrastText: true
	// 	},
	// 	puzzles: [],
	// 	unlock: 0
	// },
};