import { transitions } from "./transition.js";

/**
 * Return next token. Processing the full file, providing all tokens for the user and printing the token tag is delegated for caller. 
 */
export const getNextToken = (readableStream) => {
	// stream processing
	let buffer = ''; // for "ungetting" char if needed
	readableStream.on('readable', () => {
		let chunk;
		let state = 0;
		let token;

		while (true) {
			// process ungetted character
			if (buffer.length > 0) {
				chunk = buffer[0];
				buffer = buffer.slice(1);
			} else {
				// consume and process next character from stream
				chunk = readableStream.read(1);
				if (chunk === null) {
					// handle EOF here
					token = null;
					break;
				}
			}

			// process characters here
			// should:
			// 1) get next token. EOF checking above. DONE

			// all possible transitions for a given state
			const possibleTransitions = transitions[state];

			// look for a valid transition to advance state
			for (const transition of possibleTransitions) {

				if (transition.recognizeChar(chunk)) {
					// 3) non-accepting states only advance state and increment the token, expecting the building to end there. accepting states return whatever was the token. IF THE NON ACCEPTING TOKEN HAS A VALID TRANSITION, AND THE STATE IS NOT ZERO, ALSO UNGET THE CHARACTER
				}
			}

			// *) also handle "end of expression type token"
			// 4) print token tag with value and category.

			// chunk is here! do what you need!
			//console.log(chunk);

			// example character ungetting
			//	if (chunk === ')') {
			//		console.log('closing parens yeahhh');
			//		buffer = ')' + buffer;
			//	}
			//}
		}
	});
};
