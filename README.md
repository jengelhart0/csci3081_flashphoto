# FlashPhoto

## Coding guidelines
It is assumed that all submitted code will conform to the Google C++ style
guide. Read it. The following is a list of SOME of the things we will be
checking the code for. They are others--RTFM.
 - Usage of C++, not C-style casts
 - Not using of C-style memory allocation/copy operations
 - Usage of namespaces, including proper naming
 - Initialization of variables when they are declared
 - All 1 parameter constructors are marked explicit
 - All inheritance passes the 'is-a' test
 - All data members are private in each class
 - Proper ordering of declarations within a class (functions->data;
   public->protected->private)
 - All references passed to functions are labelled const.
 - Usage of nullptr, rather than NULL
 - Proper file naming
 - Proper function naming (use your discretion for "cheap")
 - Proper data member naming
 - Minimization of work performed in constructors
 - Not using exceptions
 - Proper commenting throughout the header files and source files

## Configuration steps
Configuration (via auto tools) is how a large project bootstraps itself; that
is, figures out how to build itself on a given platform. For us, this means
figuring out how to build the external libraries on your machine.

Configuration only happens once, after you checkout something from git.

To configure the project you will need to do the following:

    cd config
    autoconf configure.ac > configure
    chmod +x configure
    ./configure --enabled-shared=no --prefix=$(realpath ..)

Those lines do the following:
1. Configure your project to build (this is just a simple Makefile generation)
2. Configure the PNG and JPEG libraries so that they can be built and installed
   to the proper location (we recommend ./lib, though it can be anywhere, so
   long as your Makefile knows it).

You should not have to modify anything in the config/ directory. If you think
you do, you are probably doing something wrong.

### Running the linter
It is assumed that prior to handing in any iteration of the project, you will
run the following command on all source files in your repository:

    python ext/cpplint/cpplint.py --linelength=81 <source files>

And that this command will report 0 errors found. You will be evaluated on an
all-or-nothing basis for this part of the project, so take care to do this. This
will NOT catch everything that is needed for Google C++ style, so reference to
the manual and the list above. Other tools are available that can check more
than cpplint--see John for details.

## Makefile guidelines
When compiling, we suggest you use the following set of compile flags:

    -W -Wall -Wextra -Weffc++

We will not enforce this, but compiling with all compiler warnings enabled as
above will help reduce the amount of headaches you have to endure for
overlooking something simple in the code (especially the -effc++ one). If you
want to be hardcore, add the following flag:

    -pedantic

For building the external libraries, we recommend you have a line like this:

    $(JPEGDIR)/lib/libjpeg.a:
        @$(MAKE) -C$(JPEGDIR) install

Note that you are building AND installing the JPEG library. Remember in the
configuration step when you passed the prefix? That told the external libraries
to copy the libraries they built to ./lib when they are built (it also copies a
bunch of other files, which you can add to your clean target if you wish to
remove them).

If you don't want to do this, you will just have to add the directory where the
libraries live to the linker search path.

## Makefile rules
All submitted makefiles must build the main target when invoked exactly as
follows:

    make

The main target must be named exactly "FlashPhoto" and be built in a "bin/"
directory within your project root

## Invocation rules
Your FlashPhoto executable must not take any arguments, and be invoked exactly as
follows:

    bin/FlashPhoto

## git commit messages

- There should only ever be ONE scope/module affected per commit message.
- If you have an 'and' in a commit subject, consider breaking it into 2 commits.

These are examples of the quality of the commit messages we will be expecting.

* feat(onUrlChange): Added new event to $browser
  - forward popstate event if available
  - forward hashchange event if popstate not available
  - do polling when neither popstate nor hashchange available
  Breaks $browser.onHashChange, which was removed (use onUrlChange instead)

* docs(project): Updated fixed docs from Google Docs
  Couple of typos fixed:
  - indentation
  - batchLogbatchLog -> batchLog
  - start periodic checking
  - missing brace

## Documenting your project
Students, you do not need to worry about documenting the code with doxygen style
comments until iteration 3. However, you certainly can if you want.

This is more so I don't forget how to do it. The following command can be used
to generate html documentation for the code (assuming current directory is
project root):

    cd doc && doxygen Doxyfile
