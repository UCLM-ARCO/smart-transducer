// -*- mode: c++; coding: utf-8 -*-

#include <node.ice>
#include <st.ice>

module LifeLike {
    interface LoadNode extends
        IoT::NodeAdmin,
        IoT::IDMAdmin,
        IoT::WiFiAdmin,
        st::IBool {
    };
};
