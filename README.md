# metaphone-ptbr@1.0.7

Algoritmo de Metaphone para a língua portuguesa praticada no Brasil, agradecimentos para [@cjordao](https://metaphoneptbr.sourceforge.io) que escreveu o metaphone-ptbr em C. Utilizado em muitas aplicações Python PostgreSQL e PHP, agora também Node. :heart_eyes:

### TL;DR ###

```js
const metaphone = require('metaphone-ptbr');
console.log(metaphone('Casas Bahia')); # KZSB
```

## Installation
Download node at [nodejs.org](http://nodejs.org) and install it, if you haven't already.

```sh
npm install metaphone-ptbr --save
```

This package is provided in these module formats:

- CommonJS

## Dependencies

- [diacritics](https://github.com/andrewrk/node-diacritics): remove diacritics from strings
- [nan](https://github.com/nodejs/nan): Native Abstractions for Node.js: C++ header for Node 0.8 -> 11 compatibility
- [node-gyp](https://github.com/nodejs/node-gyp): Node.js native addon build tool
- [por-extenso](https://github.com/tallesl/por-extenso): Brazilian Portuguese numbers in full


## Dev Dependencies

- [eslint](https://github.com/eslint/eslint): An AST-based pattern checker for JavaScript.
- [eslint-config-airbnb-base](https://github.com/airbnb/javascript): Airbnb's base JS ESLint config, following our styleguide
- [eslint-plugin-import](https://github.com/benmosher/eslint-plugin-import): Import with sanity.


## License
[MIT](https://opensource.org/licenses/MIT)
