var _ = console.info.bind(console);

var Ice = require("ice").Ice;
var st = require("st").st;

module.exports = function(RED) {

    function IBoolSetNode(config) {
        RED.nodes.createNode(this, config);
        var node = this;
        var ic_config = RED.nodes.getNode(config.ic);

        var ic = ic_config.ic;
        var proxy = ic.stringToProxy(config.proxy);
        proxy = proxy.ice_encodingVersion(Ice.Encoding_1_0);
        proxy = st.IBoolPrx.uncheckedCast(proxy);
        this.log(proxy.toString());

        this.on('input', async function(msg) {
            try {
                await proxy.set(msg.payload, "");
                var addr = proxy.ice_getIdentity();
                node.log(ic.identityToString(addr) +
                    ".set(" + msg.payload +") called");
            }
            catch(ex) {
                node.error("ERROR: " + ex.toString());
            }
        });
    }

    RED.nodes.registerType("ibool-set", IBoolSetNode);
}
