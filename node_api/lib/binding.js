const addon = require('../build/Release/pokodb-native');

function Pokodb(name) {
    this.greet = function(str) {
        return _addonInstance.greet(str);
    }

    var _addonInstance = new addon.Pokodb(name);
}

module.exports = Pokodb;
