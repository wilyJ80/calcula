import { isNonPrinting, isAlpha, isPlus, isMinus, isSlash, isMult, isEqual, isParenOpen, isParenClose, isDigit, isAlnumOrUnderscore, isNotAlnumOrUnderscore, isNotDigit } from "./recognizeChar.js";

/**
 * Creates a transition. In the C version, we likely would use resultingCategory as an enum, and the recognizeChar callback as a function pointer.
 * @callback recognizeChar
 * @param {number} nextState
 * @param {recognizeChar} recognizeChar
 * @param {string} resultingCategory
 */
const createTransition = (nextState, recognizeChar, resultingCategory) => {
	return { nextState, recognizeChar, resultingCategory };
}

/**
 * Describes transitions.
 * @callback recognizeChar
 * @type {Array<Array<Object.<number, recognizeChar, string>>>}
 */
export const transitions = [
	// For state 0
	[
		createTransition(0, isNonPrinting, 'NON_ACCEPTING'),
		createTransition(1, isAlpha, 'NON_ACCEPTING'),
		// Does not transition to 2
		createTransition(3, isPlus, 'PLUS'),
		createTransition(4, isMinus, 'MINUS'),
		createTransition(5, isSlash, 'SLASH'),
		createTransition(6, isMult, 'STAR'),
		createTransition(7, isEqual, 'EQUAL'),
		createTransition(8, isParenOpen, 'PAREN_OPEN'),
		createTransition(9, isParenClose, 'PAREN_CLOSE'),
		createTransition(10, isDigit, 'NON_ACCEPTING')
		// Does not transition to 11
	],
	// For state 1
	[
		createTransition(1, isAlnumOrUnderscore, 'NON_ACCEPTING'),
		createTransition(2, isNotAlnumOrUnderscore, 'ID')
		// No other valid transitions

	],
	// For state 2
	[
		// No valid transitions: accepting
	],
	// For state 3
	[
		// No valid transitions: accepting
	],
	// For state 4
	[
		// No valid transitions: accepting
	],
	// For state 5
	[
		// No valid transitions: accepting
	],
	// For state 6
	[
		// No valid transitions: accepting
	],
	// For state 7
	[
		// No valid transitions: accepting
	],
	// For state 8
	[
		// No valid transitions: accepting
	],
	// For state 9
	[
		// No valid transitions: accepting
	],
	// For state 10
	[
		createTransition(10, isDigit, 'NON_ACCEPTING'),
		createTransition(11, isNotDigit, 'DIGIT')
	],
	// For state 11
	[
		// No valid transitions: accepting
	]
];
