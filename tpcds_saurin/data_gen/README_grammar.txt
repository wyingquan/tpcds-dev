The following information applies to the Windows development environment.

The migration to the latest development environment (Visual Studio 2005) 
resulted in a number of changes to the build process. Most changes are 
transparent to the user of the toolkit. One is not.

The toolkit sources include a separate project ("grammar") that uses lex
and YACC to produce a simple compiler for the query template files. The
output from lex and YACC are included in the sources compiled as part of the 
QGEN project within the toolkit, so that most people will not need to install
anything other than a standard Windows development IDE. If you need to regenerate
any of the following files, You will need to follow the step below:
   y.tab.c
   y.tab.h
   qgen.lexer.c

To rebuild the grammar project:


1. Install cygwin (www.redhat.com/cygwin), including lex and yacc
2. Enable the cygwin build rules for the grammar project
  a. Right click on the grammar project within the SOluation View of the IDE
  b. Select 'Custom Build Rules...'
  c. Select 'Find Existing...'
  d. Navigate to C:\cygwin
  e. Accept the changes
  f. Build the grammar project
3. Build the remaining projects as usual