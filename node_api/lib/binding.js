const addon = require("../build/Release/pokodb-native");

function Pokodb() {
  this.insert = function (key, value) {
    return _addonInstance.insert(key, value);
  };

  this.get = function (key) {
    return _addonInstance.get(key);
  };

  this.delete = function (key) {
    return _addonInstance.delete(key);
  };

  this.update = function (key, value) {
    return _addonInstance.update(key, value);
  };

  this.close = function () {
    return _addonInstance.close();
  };

  var _addonInstance = new addon.Pokodb();
}

module.exports = Pokodb;
