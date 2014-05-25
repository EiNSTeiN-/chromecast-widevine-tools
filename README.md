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

Before compiling this project, some dependencies will be downloaded. This includes:
- precompiled arm toolchain from the 'chromecast-mirrored-source' repo.
- chromium source tree from the 'chromecast-mirrored-source' repo.
- openssl which is needed but somehow not provided with the chromium source tree.
- protobuf which is required for some headers.

Note that the arm toolchain needs a x86_64 environment to run.

How to run tests
----------------
```bash
sudo tests/lxc-bootstrap    # setup the lxc environment (only needed once; this will take a while).
make tests                  # run tests.
```

In order to test some of the tools provided by this project, LXC is used to build a cross-architecture container in which the tools can be run without
a real chromecast. The latest chromecast OTA update will be downloaded during this process.

In order to refresh your filesystem with the latest update, simply delete the file `staging/current`.

Anything related to kernel drivers and other chromecast-specific library calls
must be mocked out in order to keep the tools working.

