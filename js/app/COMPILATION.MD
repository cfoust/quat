You can compile for web with the following command:
	cocos compile -p web --advanced
	cd publish/html5
	cclojure --compilation_level SIMPLE_OPTIMIZATIONS --js game.min.js --js_output_file game.out.js
This will compile all of the required javascript into one little bundle in
simulator/html5.

Sweet.