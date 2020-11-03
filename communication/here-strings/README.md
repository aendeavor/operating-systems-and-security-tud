# Here-Strings and Their Implementation

The Linux `bash` knows a few ways to redirect output or route input. One of them, a less frequently used one, is the `Here-String`. For those knowing what a `here-doc` is, this sounds familiar.

`Here-String`s look like this:

``` BASH
SOME_COMMAND <<< "${SOME_VARIABLE}
```

What does a `Here-String` do? It essentially provides the command with a file to read from, when you only have a variable at hand. You could do this for example:

``` BASH
sha1sum <<< ${FILE_CONTENTS_AS_VARIABLE}
```

which would print the `sha1sum` of the contents of the variable `${FILE_CONTENTS_AS_VARIABLE}`. Normally, `sha1sum` reads from a file, but this way, we don't have to use files.

## Implementation

This is the interesting part. We can look at the systemcalls executed during the `Here-String` execution:

``` BASH
strace -f -e creat,openat,open,read,write,dup2,unlink,execve bash -c 'cat <<< "TEST"'
---
execve("/bin/bash", ["bash", "-c", "cat <<< \"TEST\""], 0x7ffe0519b6a8 /* 50 vars */) = 0

{{ ... SHORTENED ... }}

strace: Process 12208 attached
[pid 12208] openat(AT_FDCWD, "/tmp/sh-thd.tXb1bk", O_RDWR|O_CREAT|O_EXCL, 0600) = 3
[pid 12208] write(3, "TEST", 4)         = 4
[pid 12208] write(3, "\n", 1)           = 1
[pid 12208] openat(AT_FDCWD, "/tmp/sh-thd.tXb1bk", O_RDONLY) = 4
[pid 12208] unlink("/tmp/sh-thd.tXb1bk") = 0
[pid 12208] dup2(4, 0)                  = 0
[pid 12208] execve("/bin/cat", ["cat"], 0x555fa15eedd0 /* 50 vars */) = 0
[pid 12208] openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
[pid 12208] openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
[pid 12208] read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\360q\2\0\0\0\0\0"..., 832) = 832
[pid 12208] openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
[pid 12208] read(0, "TEST\n", 131072)   = 5
[pid 12208] write(1, "TEST\n", 5TEST
)       = 5
[pid 12208] read(0, "", 131072)         = 0
[pid 12208] +++ exited with 0 +++

{{ ... SHORTENED ... }}
```

The shell will create a temporary file, in this case under `/tmp/sh-thd.tXb1bk`, then write to it. It will then open the file again with `O_RDONLY` and unlink it. This is known from the lecture to be a common way of "hiding" files. The file is still there (i.e. the file descriptor), but no fs-entry.

Then, `stdin` is pointed to the file descriptor (in this case) `4` with `dup2(4, 0)`. Now, `cat` sees the location of the file (which is where `stdin` now points to) and reads the contents of `/tmp/sh-thd.tXb1bk`, which prints `TEST`:

``` BASH
$ cat <<< 'TEST'
TEST
```

## Sources

I didn't come up with this. This [StackOverflow post](https://askubuntu.com/questions/678915/whats-the-difference-between-and-in-bash) explains this as well as some other redirection methods very well.
