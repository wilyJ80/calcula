// Define each callback function based on common character checks

// Checks if character is non-printing (e.g., whitespace)
export const isNonPrinting = (char) => /\s/.test(char);

// Checks if character is an alphabetical letter (A-Z, a-z)
export const isAlpha = (char) => /^[A-Za-z]$/.test(char);

// Checks if character is a digit (0-9)
export const isDigit = (char) => /^\d$/.test(char);

// Checks if character is alphanumeric or an underscore
export const isAlnumOrUnderscore = (char) => /^[A-Za-z0-9_]$/.test(char);

// Checks if character is not alphanumeric or underscore
export const isNotAlnumOrUnderscore = (char) => !isAlnumOrUnderscore(char);

// Checks if character is not a digit
export const isNotDigit = (char) => !isDigit(char);

// Checks if character is a plus sign "+"
export const isPlus = (char) => char === '+';

// Checks if character is a minus sign "-"
export const isMinus = (char) => char === '-';

// Checks if character is a slash "/"
export const isSlash = (char) => char === '/';

// Checks if character is a multiplication sign "*"
export const isMult = (char) => char === '*';

// Checks if character is an equals sign "="
export const isEqual = (char) => char === '=';

// Checks if character is an open parenthesis "("
export const isParenOpen = (char) => char === '(';

// Checks if character is a close parenthesis ")"
export const isParenClose = (char) => char === ')';
