import { isNonPrinting, isAlpha, isPlus, isMinus, isSlash, isMult, isEqual, isParenOpen, isParenClose, isDigit, isAlnumOrUnderscore, isNotAlnumOrUnderscore, isNotDigit } from "./controller.js";

/**
 * Transition representation.
 * Callback function advances the automata.
 * Non-null category determines a final state, and its value can be used to return the token category later.
 */
export const transitions = {
	0: [
		{ 0: isNonPrinting, category: null },
		{ 1: isAlpha, category: null },
		{ 3: isPlus, category: 'PLUS' },
		{ 4: isMinus, category: 'MINUS' },
		{ 5: isSlash, category: 'SLASH' },
		{ 6: isMult, category: 'STAR' },
		{ 7: isEqual, category: 'EQUAL' },
		{ 8: isParenOpen, category: 'PAREN_OPEN' },
		{ 9: isParenClose, category: 'PAREN_CLOSE' },
		{ 10: isDigit, category: null }
	],
	1: [
		{ 1: isAlnumOrUnderscore, category: null },
		{ 2: isNotAlnumOrUnderscore, category: 'ID' }
	],
	2: [],
	3: [],
	4: [],
	5: [],
	6: [],
	7: [],
	8: [],
	9: [],
	10: [
		{ 10: isDigit, category: null },
		{ 11: isNotDigit, category: 'DIGIT' }
	],
	11: []
};

/**
 * Create token.
 * @param {string} value
 * @param {string} category
 */
export const createToken = (value, category) => {
	const reprTag = `<${category}, ${value}>`;
	return { value, category, reprTag };
};
