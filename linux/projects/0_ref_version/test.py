#!/usr/bin/env py.test
import fcntl
import os

IOCTL_VERSION_MODIFIED = (1 << 30) | (1 << 18) | (ord('V') << 8) | 1
IOCTL_VERSION_RESET = (ord('V') << 8) | 2

base_version = open('/proc/sys/kernel/version', 'rb').read()[:-1]

def test_read():
    with open("/dev/version", "r+b", buffering=0) as f:
        assert os.read(f.fileno(), 20) == base_version


def test_write():
    with open("/dev/version", "r+b", buffering=0) as f:
        assert os.write(f.fileno(), b'\0') == 1
        assert os.read(f.fileno(), 20) == b''

        assert os.write(f.fileno(), b'test\0') == 5
        assert os.read(f.fileno(), 20) == b'test'


def test_ioctl():
    with open("/dev/version", "r+b", buffering=0) as f:

        assert fcntl.ioctl(f, IOCTL_VERSION_RESET) == 0

        x = bytearray(4)
        assert fcntl.ioctl(f, IOCTL_VERSION_MODIFIED, x) == 0
        assert x == bytearray(4)

        assert os.write(f.fileno(), b'foobar\0') == 7

        assert fcntl.ioctl(f, IOCTL_VERSION_MODIFIED, x) == 0
        assert x[0] == 1;

        assert fcntl.ioctl(f, IOCTL_VERSION_RESET) == 0
        assert os.read(f.fileno(), 20) == base_version

        x = bytearray(4)
        assert fcntl.ioctl(f, IOCTL_VERSION_MODIFIED, x) == 0
        assert x == bytearray(4)
