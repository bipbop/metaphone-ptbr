const { remove: removeDiacritics } = require('diacritics');
const porExtenso = require('por-extenso');
// eslint-disable-next-line import/no-unresolved
const { metaphone: metaphoneNative } = require('./build/Release/addon');

const companyRule = /\s(SA|LTDA|MEI|ME|EPP|EIRELI)(\s|$)/ig;
const nonCharOrSpace = /[^\w ]/ig;

function metaphone(text, additionalPhases = [
  [companyRule, ''],
]) {
  let userText = removeDiacritics(porExtenso(text))
    .toLowerCase()
    .replace(nonCharOrSpace, '');

  if (additionalPhases) {
    additionalPhases.forEach(([from, to]) => {
      userText = userText.replace(from, to);
    });
  }

  return metaphoneNative(userText);
}

metaphone.companyRules = companyRule;
module.exports = metaphone;
