README
---------

Distributed File Repair Utilities v0.2.0 beta
Copyright (C) 2006 Loki TroubleMind <loki1985@users.sourceforge.net>

This set of tools is designed to help people repair a corrupt
file with the help of someone who got the original file.

There is already FileRepair (http://www.robinhill.me.uk/FileRepair/),
which is much more advanced and pretty cool, the only thing:
It works online only, and so not much help for folks without
an internet connection or a very restrictive firewall.

This is the main reason why i developed DFRU.


Usage Example:
User1 got a file called "damaged.zip" in which a few bytes have been changed.
User2 got the original, undamaged file called "original.zip"
User1 will execute "makehashes damaged.zip".
A file called "hashlist" will be created in current directory.
User1 sends this "hashlist" file to User 2 via e-mail or other ways.
User2 copies "hashlist" to the directory where "original.zip" resides,
then User2 executes "makechunks original.zip", which will create some ".fix"-files
User2 sends these ".fix"-files to User1 via e-mail or other ways.
User1 copies those ".fix"-files to the directory where "damaged.zip" resides,
and executes "insertchunks damaged.zip", which will create "damaged.zip_fixed".
And hopefully this file will be identical with original :)

                      === WARNING!!! ===

This version is beta, since minor tests from my side where
all successful. This means using it should most propably work,
but i expect major INCOMPATIBLE changes, especially in the
hashlist format.

Version 0.2.0 is completely incompatible to version 0.1.5 and vice versa!!!

The current version is intented mainly for testing purposes, and it
is ABSOLUTELY NOT RECOMMENDED to be used with important data.

If you use it anyway, be at least sure the program version used
on both sides and defined CHUNKSIZE (if self-compiled) is identical.
CHUNKSIZE is set to 32KBytes by default, no need to change it in most cases.

As of the current situation, both files MUST have the same size!!!
Maybe this will be changed in the future, but cannot be promised...


KNOWN ISSUES:

- Developed & tested using MinGW in MSW2K only, should test some more.
  But i have no idea why it shouldn't work on other platforms.

- There is no makefile, i made some little sh script instead.
  Just run ./compile... ugly, but works.

$loki 2006-01-21
