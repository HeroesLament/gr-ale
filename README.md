# gr-ale

`gr-ale` is a MIL-STD-188-141a (ALE 2G) decoding block for GNU Radio.

## Usage

The block accepts float input from a USB demod sampled at 8000Hz and outputs decoded data to stdout. It is also capable of recording voice traffic after a 3-step ALE handshake is detected for a preconfigured period of time.

## Known Problems

Incomplete support of ALE protocol features, currently only sounding and call establishment are decoded.

## Getting Help and Reporting Bugs

Please contact gat3way@gat3way.eu or via GitHub issues.

## Installation from Source

```bash
$ git clone https://github.com/HeroesLament/gr-ale.git gr-ale.git
$ cd gr-ale.git
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

There is a nice Python multi-channel ALE decoder under the examples/ directory. On my machine (six-core AMD bulldozer), it can decode ~22 channels before librtlsdr starts complaining about overruns.

## Credits and License

`gr-ale` is written by Milen Rangelov (gat3way@gmail.com) and licensed under the GNU General Public License.

Significant portions of the source code were based on the LinuxALE project (under GNU License):
 * Copyright (C) 2000 - 2001 
   * Charles Brain (chbrain@dircon.co.uk)
   * Ilkka Toivanen (pile@aimo.kareltek.fi)

This project includes a snapshot of `xmlrpc-c`, a lightweight RPC library based on XML and HTTP. `xmlrpc-c` is used under its respective license:
 * For more information about `xmlrpc-c`, visit [their GitHub mirror](https://github.com/mirror/xmlrpc-c).
