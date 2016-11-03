# FlashPhoto

## Coding guidelines
It is assumed that all submitted code will conform to the Google C++ style
guide. Read it. The following is a list of SOME of the things we will be
checking the code for. There are others--read the style guide!
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

## Documenting your code
Students, you do not need to worry about documenting the code with doxygen style
comments until iteration 3. However, I would encourage you to document as you
go, to avoid having to document EVERYTHING all at once for iteration 3.

This does NOT mean that you can submit code without any comments for iteration 1
and 2. We will be expecting reasonable class, function, variable, and
algorithmic comments. If you have questions on the level we are expecting, look
at the base code. If you still have questions, see John.

## Configuration requirements
Configuration (via autotools) is how a large project bootstraps itself; that
is, figures out how to build itself on a given platform. For us, this means
figuring out how to build the external libraries on your machine.

Configuration only happens once, after you checkout something from git.

In the config folder, we have given you the building blocks for how to create a
configuration process for your project, and integrate it with your build
process. In the example config we provde you, to configure the project you do:

    cd config
    ./configure --enable-shared=no --prefix=`realpath ../ext`

Those lines do the following:
1. Configure your project to build. This does nothing at the moment (stub).
2. Configure the PNG and JPEG libraries so that they can be built.
3. Configure the PNG and JPEG libraries so they can be installed to where your
   Makefile will look for them. (we chose ../ext/lib via the --prefix argument),
   though it can be anywhere.

Your configure process can differ from what is above, but it *MUST BE
DOCUMENTED IN YOUR README*. If we cannot configure your project based on what is
in your README, you will receive a zero for this part of the grade.

*DO NOT PUT THE CONFIGURATION PROCESS IN THE MAKEFILE.*

You should not have to modify anything in the config/ directory in order to have
a successfully working configuration/build process. However, if you would like
to augment the configuration process in some way, take care, as it is MUCH
trickier than using make. So if you have questions, please ask John.

### Running the linter
It is assumed that prior to handing in any iteration of the project, you will
run the following command on all source files in your repository:

    python ext/cpplint/cpplint.py --linelength=81 <source files>

And that this command will report 0 errors found. You will be evaluated on an
all-or-nothing basis for this part of the project, so take care to do this. This
will NOT catch everything that is needed for Google C++ style, so refer to
the manual and the list above. Other tools are available that can check more
than cpplint--see John for details if you would like to incorporate more
automated checking into your workflow.

## Makefile hints

In order be able to compile the .cc files that include header files from the
external libraries, you will need to add the following to your compiler flags
(assuming all libraries live under ./ext):

    -isystem./ext/glui/include -isystem./ext/jpeg-9a -isystem./ext/libpng-1.6.16

Note that the -isystem flag suppresses all compiler warnings from any includes
found in any of the specified directories. This is OK, as these are external
libraries which you will never modify.

When compiling our support/base code, you must pass the following compiler flag:

    -std=c++11

so that certain C++11 definitions are allowed by the compiler. C++11 is
available on g++ 4.9, which is available on all lab computers.

In addition, we suggest you use the following set of compile flags in your
Makefile:

    -W -Wall -Wextra -Weffc++ -std=c++11

Compiling with all compiler warnings enabled as above will help reduce the
amount of headaches you have to endure for overlooking something simple in the
code (especially the -Weffc++ one). If you want to be hardcore, add the
following flags:

    -pedantic -Werror -Wswitch-default -Wfloat-equal -Wold-style-cast

You will need to link with a number of libraries, so add this to the END of your
linker command-line invocation.

    -lglut -lGL -lGLU -lglui -lpng -ljpeg -lz

Note: The order in which the libraries are ordered, in addition to where they
appear on the command line linker invocation MATTERS, so take care when creating
this part of the Makefile.

In addition to passing the libraries to link with, you will need to pass the
external library directory, so the linker knows where to look for libglui.a,
libpng.a and libjpeg.a:

    -L./ext/lib

For this to work, you need to build not only the "all" target for libglui,
libpng, and libjpeg, but also the "install" target, which will copy the
libraries to ./ext/lib (remember that's where we said we wanted things to be
installed in the configuration step). Something like:

    $(MAKE) -C./ext/jpeg-9a all install

will need to be included in the recipe for each external library target.


## Makefile target rules
All submitted makefiles must build the main target when invoked exactly as
follows from the root directory of your project:

    make

The main target must be named exactly "FlashPhoto" and be built in a "bin/"
directory within your project root

## Invocation rules
Your FlashPhoto executable must not take any arguments, and be invoked exactly as
follows:

    bin/FlashPhoto

## git commit message guidelines/rules
- There should only ever be ONE scope/module affected per commit message.
- If you have an 'and' in a commit subject, break it into 2 commits.
- No "In progress coding/debugging" commit messages

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

If you have questions about whether something is appropriate, see John.

Furthermore, if you want to pair/group program, your git commit messages should
reflect this, so that all members receive participation credit for doing it, not
just the one that actually commits the work. To do so, add a line like this to
the bottom of your commit message:

    Contributors: <x500 for student 1> <x500 for student 2> ...

For example, if Seth and I worked on something, we would do

    Contributors: harw006 joh08230

at the end of our commit.
