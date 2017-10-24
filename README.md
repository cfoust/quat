# QUAT

By Caleb Foust (Code) and David Seitz Jr (Design)

## About

QUAT is a mobile game written in C++ and Cocos2DX that in theory can be run on
both Android and iOS. Back when I was working on it I did the majority of the
development on Linux, which was handy since I didn't have a Macbook at the time
(nor an Android phone, so I wasn't winning too many battles in the "developing
a mobile game" department.)

The concept is simple. QUAT gives you two four-letter words, such as `BANK` and
`PARK`. Your task is to change one letter at a time to change `BANK` into `PARK`,
but all of the words you make have to be real words. For example, you could do
`BANK->BARK->PARK` but not `BANK->PANK->PARK`.

The game is complete, as far as I am concerned. I just decided not to ship it.
I don't have a lot of confidence in the mobile market for premium games without
microtransactions. We have so many other distractions these days that poking
around a decidedly un-fun mobile game didn't appeal to me, nevertheless to
my target market. Add in the "schlep" of buying a new Apple computer and paying
$100 a year to put it on the App Store and I stopped caring.

Make no mistake, though: the game is finished and playable, if not a little
lacking in functionality. Perhaps someday someone will iterate on the idea and
make a bajillion dollars. I just hope they remember the little guy who did
much of the legwork.

## Building

There are two different versions of the game found in the `cpp` and `js`
directories.  The former uses Cocos2DX's C++ bindings and is the game I am
referring to when I say that it is "complete." The latter was mainly as a proof
of concept. It, too, has a lot of functionality, some of which simply didn't
make the cut into the final C++ version. There is probably some way to get it
running, but I remember it being a bit fussy. It's better if you just try to
run the C++ version, if anything.

To do so, you need to [install
Cocos2DX](http://www.cocos2d-x.org/wiki/Linux_Installation_and_Setup).

When that's done, you can do the following:
```
$ cd cpp
$ cocos run -p linux
```

Your mileage may vary on other platforms.

The cocos2dx toolchain was a bit janky at the time, so I did include a full
installation in the `cpp/cocos2d` directory. It made sense at the time and
worked just fine even if it pollutes the git repository. At the very least the
code builds.
