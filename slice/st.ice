// -*- mode: c++; coding: utf-8 -*-

module st {
  interface IBool  { void set(bool v, string sourceAddr); };
  interface IByte  { void set(byte v, string sourceAddr); };
  interface IFloat { void set(float v, string sourceAddr); };
  interface IStr   { void set(string v, string sourceAddr); };
  interface Active { void linkto(string observerAddr); };
};
