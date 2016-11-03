# Project-Iterations

## Coding guidelines
In any large software project with multiple people contributing, having a
consistent coding style throughout is vital to minimize miscommunications
between collaborators, making code more readable, etc. For this class, we will
be Google's C++ Style Guide (there are other conventations that are also valid,
but this is the one we will be using). We will be checking that all submitted
code will conform to the Google C++ style.

### Running the linter
To that end, we will provide you with a style checking script that will check
the basic elements of Google style. It is assumed that prior to handing in any
iteration of the project, you will run the following command on all source files
(.cc AND .h) in your repository by doing something like this:

    python ext/cpplint/cpplint.py --linelength=81 <source files>

And that this command will report 0 errors found. You will be evaluated on an
all-or-nothing basis for this part of the project, so take care to do this.

### Additional elements of Google C++ style
Unfortunately, the script will NOT catch everything that is needed for Google
C++ style. We will be spot checking code for things not caught by the script,
for things like:
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

This is not an exhaustive list of what we will be checking for, so please read
the Google C++ style guide!

## Documenting your code
Students, you do not need to worry about documenting the code with doxygen style
comments until iteration 3. However, I would encourage you to document as you
go, to avoid having to document EVERYTHING all at once for iteration 3.

This does NOT mean that you can submit code without any comments for iteration 1
and 2. We will be expecting reasonable class, function, variable, and
algorithmic comments. If you have questions on the level we are expecting, look
at the iteration 1/iteration 2 base code. If you still have questions, see John.


## Makefile hints

In order be able to compile the .cc files that include header files from GLUI,
you will need to add the following to your compiler flags:

    -I./ext/glui/include

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

    -lglut -lGL -lGLU -lglui

Note: The order in which the libraries are ordered, in addition to where they
appear on the command line linker invocation MATTERS, so take care when creating
this part of the Makefile.

In addition to passing the libraries to link with, you will need to pass the
library directory for GLUI so the linker knows where to look for libglui.a:

    -L./ext/glui/lib


## Makefile target rules
All submitted makefiles should build the main target when invoked exactly as
follows from the root directory of your project:

    make

This is what is expected in the wild if you download something from github;
users do not expect to have to go hunting through your Makefile to figure out
how to build your main target. As such, the build process should produce an
executable called BrushWork in the bin/ directory.

## Invocation rules
When run, your program must take 0 agruments and be invoked as follows:

    ./bin/BrushWork

## git commit message guidelines
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

Furthermore, if you want to pair/group program, your git commit messages should
reflect this, so that all members receive participation credit for doing it, not
just the one that actually commits the work. To do so, add a line like this to
the bottom of your commit message:

    Contributors: <x500 for student 1> <x500 for student 2> ...

For example, if Seth and I worked on something, we would do

    Contributors: harw006 joh08230

at the end of our commit.

Usage of our git commit message template is in no way mandatory; it is just
there to help you create detailed, helpful git commit messages. You can use
whatever conventation you like within your group, as long as the messages are
detailed and helpful.


If you have questions about whether something is appropriate, see John.
