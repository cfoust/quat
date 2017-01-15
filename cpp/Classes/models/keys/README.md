We generate keys here using the command:
```
time dd if=/dev/urandom of=keyname bs=1 count=1024 | xxd -i key > key.h
```

It generates some randomness and puts it into a key header file.

Mind you, there are no include blockers in there so you'll
need to add them before use.
