# ![TUD Logo](images/tud_logo.svg)

## Operating Systems and Security

_An alternative to the OPAL forum with proper support for code highlighting and issues. This repository is meant for computer science students (and others) in their fifth semester studying for INF-B-380._

### Rationale

This repository exists to work around the rather poor support for **code formatting**, **syntax highlighting** and **issue reporting**. It is meant to be accessible to every student who is interested in the topic, want to learn more or discuss issues he or she ran into. Moreover, tutors are welcome to look into this too.

This wil also provide anyone _unfamiliar_ with a shell (the command line) with _some_ experience.

### If you're interested

This repository is set-up to enable everyone to clone and work with it. Every peace of code is free to use and alter under the Apache 2.0 license. if you'd like to contribute, open a PR. If you have a question with regard to code in this repository, open an issue.

### An Example

The first topic of interest added here is about [`fork-exec`][fork-exec::wikipedia]. A few small examples were written to illustrate the process. We will take the first one and discuss what examples should look like and what their educational purpose is.

Each directory has a certain structure so it's _easy_ to work consistently.

``` Bash
fork-exec/
├── introduction/
│   ├── Makefile
│   └── src
│       └── main.c
└── zombies/
    ├── Makefile
    ├── README.md
    └── src
        └── main.c
```

In this example, we will need to navigate to `fork-exec/introduction`. Open a terminal in this repository in your editor of choice. You should now be in the root of this repository. Use `cd fork-exec/introduction` to get to the introductory example.

You can now compile the program yourself with `gcc src/main.c -o main.out`, or use the provided `Makefile`. If you want to use `make`, you can install it - on Ubuntu, that's `sudo apt-get -y install make`. You will then be able to build the program by executing `make build`. Running just `make` will execute the program.

Let's try it without `make` first:

![Introduction without make](images/intro_without_make.png)

Now with make:

![Introcution with make](images/intro_with_make.png)

***That's it***. Now have a look at the source code yourself and see what happens. For some examples, there is a dedicated `README.md` in each directory which explains the case presented in more detail.

[fork-exec::wikipedia]: https://en.wikipedia.org/wiki/Fork%E2%80%93exec

### Currently Present Cases

1. `fork-exec` :: Introduction
2. `fork-exec` :: Zombies
