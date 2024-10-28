import { isNonPrinting } from "./controller.js";
import { transitions } from "./model.js";

const exampleString = 'jaca = b * 2 / 7';
const arr = exampleString.split('');

let state = 0;
let token = '';
let tokenType = '';
let tokens = [];
let index = 0;

while (index < arr.length) {
	const char = arr[index];

	//// Skip non-printing characters (e.g., spaces, tabs)
	//if (isNonPrinting(char)) {
	//	// If there's a token, finalize it
	//	//if (token) {
	//	//	tokens.push({ value: token, type: tokenType }); // Use a default type if needed
	//	//	token = '';  // Reset token for the next one
	//	//}
	//	//index++;
	//	continue;
	//}

	const possibleTransitions = transitions[state];
	let matchedTransition = false;

	for (const transition of possibleTransitions) {
		const nextState = parseInt(Object.keys(transition)[0], 10);
		const condition = transition[nextState];
		const final = transition.final || false;
		tokenType = transition.type || 'unknown'; // Default type if not set

		if (condition(char)) {
			// Finalize the token if we're in a final state
			if (final) {
				if (token) {
					tokens.push({ value: token, type: tokenType }); // Save the token with type
				} else {
					tokens.push({ value: char, type: tokenType });
				}
				token = '';         // Reset token for the next one
				state = 0;          // Reset to initial state
				break;
			}

			// Add the current character to the token
			token += char;
			state = nextState; // Move to the next state
			matchedTransition = true;

			break;
		}
	}

	// If no match found, finalize current token and reset state
	if (!matchedTransition) {
		if (token) {
			tokens.push({ value: token, type: tokenType }); // Use a default type if needed
			token = '';
		}
		state = 0; // Reset to start a new token
	}
	index++;
}

// Push any remaining token at the end of input
if (token) tokens.push({ value: token, type: tokenType }); // Use a default type if needed

tokens.forEach((token) => {
	console.log(`Token: "${token.value}", Type: "${token.type}"`);
});
console.log(`Final State: ${state}`);
