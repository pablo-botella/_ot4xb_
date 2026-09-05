Argon2 source folder:

The argon2 folder contains the reference C implementation of Argon2,
copied from its owners' repository:

https://github.com/P-H-C/phc-winner-argon2

The copy was taken from the master branch (snapshot added to this
project on 2025-01-14; the last upstream tagged release at that time
was 20190702). The upstream layout was flattened when copying: the
contents of src/ and src/blake2/ went to argon2/ and argon2/blake2/,
the public header include/argon2.h went to argon2/argon2.h, and the
upstream README.md is kept as argon2/README.md.

---------
Argon2:

Argon2 is the password-hashing function that won the Password
Hashing Competition (PHC). It can be used to hash passwords for
credential storage, key derivation, or other applications.

Argon2 belongs to its legitimate owners. Except for the components
listed below, the Argon2 code is copyright (c) 2015 Daniel Dinu,
Dmitry Khovratovich (main authors), Jean-Philippe Aumasson and
Samuel Neves, and dual licensed under the CC0 License and the
Apache 2.0 License.

The string encoding routines in encoding.c are copyright (c) 2015
Thomas Pornin, and under CC0 License.

The BLAKE2 code in blake2/ is copyright (c) Samuel Neves, 2013-2015,
and under CC0 License.

Official web site and repository:
https://password-hashing.net
https://github.com/P-H-C/phc-winner-argon2
