var Ice = require("ice").Ice;

module.exports = function(RED) {

    function IceCommunicatorConfigNode(config) {
        RED.nodes.createNode(this, config);
        var node = this;

        var idata = new Ice.InitializationData();
        idata.properties = Ice.createProperties();

        // props needed for bidir connection
        // idata.properties.setProperty("Ice.ACM.Server.Close", "0");
        // idata.properties.setProperty("Ice.ACM.Heartbeat", "3");
        // idata.properties.setProperty("Ice.ACM.Timeout", "30");

        node.ic = Ice.initialize(idata);
    }

    RED.nodes.registerType("ice-communicator", IceCommunicatorConfigNode);
}
