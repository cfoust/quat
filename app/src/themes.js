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
	"WASH": {
		colors: {
			background: "#0000CD",
			text: "#FFFFFF",
			darkForeground: "#000080",
			lightForeground: "#00BFFF"
		},
		puzzles: [],
		unlock: 0
	},
	"LATE": {
		colors: {
			background: "#000000",
			text: "#FF0000",
			darkForeground: "#500000",
			lightForeground: "#B40000"
		},
		puzzles: [
			{
				text: 'I went to bed at around 9pm. My phone pulsed with an unread text message.',
				start: 'text',
				end: 'went',
				par: 3
			},
			{
				text: "\"I'm not over it. I've gotten a lot better about it, and I can pretend that I am, but seeing you just reminds me of everything.\"",
				start: 'that',
				end: 'over',
				par: 6
			},
			{
				text: "\"You just want me to come back.\"",
				start: 'back',
				end: 'come',
				par: 6
			},
			{
				text: "\"I guess I still don't understand how or why you feel the way you do. I'll just go.\"",
				start: 'feel',
				end: 'dont',
				par: 5
			},
			{
				text: "\"I do care about you too, I do. I feel the way I do for a lot of reasons.\"",
				start: 'care',
				end: 'dont',
				par: 5
			},
			{
				text: "\"All I seem to be doing is making your life so much harder.\"",
				start: 'hard',
				end: 'life',
				par: 5
			},
			{
				text: "\"You made me feel like that. Like I was some sort of stupid kid always getting in the way when all I was trying to do was care.\"",
				start: 'care',
				end: 'sort',
				par: 5
			},
			{
				text: "\"I didn't mean to get like this again.\"",
				start: 'this',
				end: 'like',
				par: 5
			},
			{
				text: "\"I'm sick of not being \"old enough\" for you or being a burden to you.\"",
				start: 'life',
				end: 'sick',
				par: 4
			},
			{
				text: "\"We can still be friends.\"",
				start: 'lies',
				end: 'more',
				par: 6
			},
		],
		unlock: 0
	},
	
	"GAME": {
		colors: {
			background: "#8B956D",
			text: "#414141",
			darkForeground: "#6B7353",
			lightForeground: "#C4CFA1"
		},
		puzzles: [
			{
				text: "My thumbs hurt after the first hour, but I didn't care. I stared into that monochromatic screen the whole night.",
				start: 'care',
				end: 'hurt',
				par: 4
			},
			{
				text: "I ripped out the game cart and threw it across the room. I wanted to beat that darn gorilla.",
				start: 'damn',
				end: 'beat',
				par: 6
			},
			{
				text: "Did you ever notice how it doesn't list your points anywhere while you play? That seems like bad game design.",
				start: 'play',
				end: 'ever',
				par: 6
			},
			{
				text: "The world the device created was violent, comical, and fun. Life was anything but.",
				start: 'time',
				end: 'good',
				par: 6
			},
			{
				text: "The machinations of a screen seemed more tangible than the world around me. I made friends with the leaping pixels, imagined arias to the tinny music.",
				start: 'note',
				end: 'root',
				par: 5
			},
			{
				text: "The screens weren't backlit then. I hid under the blankets with a flashlight like my father had with books.",
				start: 'boys',
				end: 'same',
				par: 5
			},
			{
				text: "\"A new challenger is approaching.\"",
				start: 'life',
				end: 'fake',
				par: 4
			},
		],
		unlock: 0
	},
	"SNOW": {
		colors: {
			background: "#FFFFFF",
			text: "#204C54",
			darkForeground: "#36818F",
			lightForeground: "#83C9FF"
		},
		puzzles: [
			{
				text: "It was quiet. You know the snow smell has? It's like nothing.",
				start: 'like',
				end: 'snow',
				par: 8
			},
			{
				text: "Water had soaked into my glove. The numbness made my grip loose around the sled's rope handles.",
				start: 'time',
				end: 'sled',
				par: 6
			},
		],
		unlock: 0
	},
	"BOOK": {
		colors: {
			background: "#FADFAF",
			text: "#332E23",
			darkForeground: "#CC8F00",
			lightForeground: "#573526",
			inverseButtons: true
		},
		puzzles: [
			{
				text: "\"And in her passing my madness passed.\"\nHOUSE OF LEAVES",
				start: 'word',
				end: 'pass',
				par: 5
			},
			{
				text: "\"It is a far, far better thing that I do, than I have ever done; it is a far, far better rest that I go to than I have ever known.\"\nA TALE OF TWO CITIES",
				start: 'down',
				end: 'cuts',
				par: 6
			},
		],
		unlock: 0
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
		unlock: 0
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
		unlock: 0
	},
	"WISH": {
		colors: {
			background: "#FAD6AB",
			text: "#A08800",
			darkForeground: "#111859",
			lightForeground: "#BA9E00",
		},
		puzzles: [],
		unlock: 0
	},
	"WOOD": {
		colors: {
			background: "#64371B",
			text: "#E37D3E",
			darkForeground: "#573018",
			lightForeground: "#A35A2D",
		},
		puzzles: [],
		unlock: 0
	},
	"SAIL": {
		colors: {
			background: "#171857",
			text: "#E37D3E",
			darkForeground: "#331C0E",
			lightForeground: "#64371B",
		},
		puzzles: [],
		unlock: 0
	},
	"DAYS": {
		colors: {
			background: "#00C1C2",
			text: "#4F4A44",
			darkForeground: "#CF9F3B",
			lightForeground: "#CF9C19",
			contrastText: true
		},
		puzzles: [],
		unlock: 0
	},
};