chromecast-widevine-tools
=========================

Some experimental tools that are meant to run on a rooted chromecast in order to interact with the widevine library (libwvcdm).

Install build dependencies
--------------------------
```bash
apt-get install git subversion
```

Install test dependencies
-------------------------
```bash
apt-get install lxc qemu-system-arm qemu-user-static curl libxml2-utils \
  squashfs-tools binwalk pax
```

How to build
------------
```bash
make
```

How to run tests
----------------
```bash
sudo tests/lxc-bootstrap    # setup the lxc environment (only needed once; this will take a while).
make tests                  # run tests.
```
