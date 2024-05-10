# /dev/lorem-ipsum

Just playing around with Linux Kernel Module programming.

## What is this?

A Linux driver for a device which outputs
[Lorem ipsum](https://en.wikipedia.org/wiki/Lorem_ipsum).

## Usage

*Disclaimer:* You should probably run this kernel module in a virtual machine,
as it is literally running in kernel-space, and I don't consider my Linux kernel
module programming experience high enough to confidently claim that this won't
wreak complete havoc on your machine. It works on my machine, though.

### Building

Clone this repository, `cd` to it, then run `make`.

### Loading

After building the module, run `insmod lorem_ipsum.ko` with root privileges to
load it.

### Using the device

After loading the module, you can read Lorem ipsum from `/dev/lorem-ipsum`
(you'll probably need root privileges to access the device):

```sh
head -c 500 /dev/lorem-ipsum
```

Output:

```
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing el
```

### Unloading

Run `rmmod lorem_ipsum` with root privileges to unload the module.
