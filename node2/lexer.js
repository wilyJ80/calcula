import { isNonPrinting } from "./controller.js";
import { createToken, transitions } from "./model.js";

/** Returns next token
 * @param {Array} input
 * @returns {Array<Object>} tokens
 * */
export const getTokens = (input) => {
	/** initial state */
	let state = 0;
	/** running token value */
	let tokenValue = '';
	/** token storage for later returning by the lexer */
	const tokens = [];
	/** For iterating over the input */
	let index = 0;

	while (index < input.length) {

		// consume next character
		const ch = input[index];

		// Perform checks on whether state increments or returns token

		/** possible transitions for given state */
		const possibleTransitions = transitions[state];

		// Iterate over possible transitions, stop if valid transition was reached
		for (const transition of possibleTransitions) {
			const nextState = parseInt(Object.keys(transition)[0], 10);

			/** Condition is the function corresponding to the target state */
			const condition = transition[nextState];
			const tokenCategory = transition.category;

			if (condition(ch)) {
				// If state is final, return token and push to token array
				if (tokenCategory !== null) {
					// PROBLEM: must know if token value was being built. If not, push the char and reset the token value again!
					let token;
					if (tokenValue.length > 0) {
						token = createToken(tokenValue, tokenCategory);
					} else {
						token = createToken(ch, tokenCategory);
					}
					tokens.push(token);
					// reset running token value
					tokenValue = '';
					// back to initial state
					state = 0;

					// If state is not final, increment token
				} else {
					// if is non printing, do NOT increment !!!
					if (isNonPrinting(ch)) {
						tokenValue = '';
					} else {
						// increment token
						tokenValue += ch;
					}
					// advance state
					state = nextState;
				}

				// break loop over possible transitions for a given state after transition was valid and state advancement was performed
				break;
			}
		}

		// go to next character
		index++;
	}
	return tokens;
}

// must take \n in account to increment line counter
const exampleString = `
var b = 8
b + 1
`;
const arr = exampleString.split('');
const tokens = getTokens(arr);

for (const token of tokens) {
	console.log(token.reprTag);
}
