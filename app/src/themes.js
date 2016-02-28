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
	// 			end: '[four letter end word]',
	// 			par: 0
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
				start: 'went',
				end: 'text',
				par: 3
			},
			{
				text: "\"I'm not over it. I've gotten a lot better about it, and I can pretend that I am, but seeing you just reminds me of everything.\"",
				start: 'over',
				end: 'that',
				par: 6
			},
			{
				text: "\"You just want me to come back.\"",
				start: 'come',
				end: 'back',
				par: 6
			},
			{
				text: "\"I guess I still don't understand how or why you feel the way you do. I'll just go.\"",
				start: 'dont',
				end: 'feel',
				par: 5
			},
			{
				text: "\"I do care about you too, I do. I feel the way I do for a lot of reasons.\"",
				start: 'dont',
				end: 'care',
				par: 5
			},
			{
				text: "\"All I seem to be doing is making your life so much harder.\"",
				start: 'life',
				end: 'hard',
				par: 5
			},
			{
				text: "\"You made me feel like that. Like I was some sort of stupid kid always getting in the way when all I was trying to do was care.\"",
				start: 'sort',
				end: 'care',
				par: 5
			},
			{
				text: "\"I didn't mean to get like this again.\"",
				start: 'like',
				end: 'this',
				par: 5
			},
			{
				text: "\"We can still be friends.\"",
				start: 'more',
				end: 'lies',
				par: 6
			},
			{
				text: "\"I'm sick of not being \"old enough\" for you or being a burden to you.\"",
				start: 'sick',
				end: 'life',
				par: 4
			}
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
			start: 'hurt',
			end: 'care',
			par: 4
		},
		{
			text: "I ripped out the game cart and threw it across the room. I wanted to beat that damn ape.",
			start: 'beat',
			end: 'damn',
			par: 6
		},
		{
			text: "Did you ever notice how it doesn't list your points anywhere while you play? That seems like bad game design.",
			start: 'ever',
			end: 'play',
			par: 6
		}],
		unlock: 0
	},
	"SNOW": {
		colors: {
			background: "#FFFFFF",
			text: "#204C54",
			// darkForeground: "#285F69",
			darkForeground: "#36818F",
			lightForeground: "#83C9FF"
		},
		puzzles: [],
		unlock: 0
	},
	"BOOK": {
		colors: {
			background: "#FADFAF",
			text: "#332E23",
			darkForeground: "#CC8F00",
			lightForeground: "#573526"
		},
		puzzles: [],
		unlock: 0
	},
};