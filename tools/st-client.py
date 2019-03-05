#!/usr/bin/python3 -u
# -*- mode: python; coding: utf-8 -*-

import os
import sys
import argparse
import Ice

SLICE = "../slice/st.ice"
if not os.path.exists(SLICE):
    SLICE = "/usr/share/slice/st/st.ice"

Ice.loadSlice(SLICE)
import st  # noqa


class Client(Ice.Application):
    def run(self, args):
        try:
            args = self.parse_args(args)
        except SystemExit:
            return -1

        {
            "bool": self.set_bool,
            "byte": self.set_byte,
            "float": self.set_float,
            "string": self.set_string,
        }[args.type](args)

    def set_bool(self, args):
        value = args.value != "0"
        prx = self.get_proxy(args)
        prx = st.IBoolPrx.uncheckedCast(prx)
        prx.set(value, "")
        print("bool set to", value)

    def set_byte(self, args):
        print("byte set to", args.value)

    def set_float(self, args):
        print("float set to", args.value)

    def set_string(self, args):
        print("string set to", args.value)

    def get_proxy(self, args):
        prx = self.communicator().stringToProxy(args.proxy)
        prx = prx.ice_encodingVersion(Ice.Encoding_1_0)
        print("Using proxy: '{}'".format(prx))
        return prx

    def parse_args(self, args):
        parser = argparse.ArgumentParser()

        parser.add_argument(
            "-t", dest="type", help="Value type of invocation", required=True,
            choices=["bool", "byte", "float", "string"],
        )
        parser.add_argument("-p", dest="proxy", help="Proxy to invoke")
        parser.add_argument("value", help="Value to send")

        return parser.parse_args(args[1:])



if __name__ == "__main__":
    Client().main(sys.argv)
