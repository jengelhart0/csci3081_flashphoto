################################################################################
# Name            : Makefile
# Project         : MIA Regression Testing
# Description     : Application Makefile Template
# Creation Date   : Fri May 16 14:59:49 2014
# Original Author : engel429 (format by jharwell)
#
#
#  Products:
#  Make Target     Product                  Description
#  ===========     =======                  ===================
#  all             build/bin/<dirname>      The main application
#            
#  sharpentest                              Everything clean removes, +
#                                           the external libraries
#  documentation   Various                  Generates documentation for
#                                           project from the doxygen
#                                           comments/markup in the code
################################################################################

###############################################################################
# Directory, Execution, Image Definitions
###############################################################################
TESTROOT = ./tests
GOLDENDIR = $(TESTROOT)/goldendir
COMPAREDIR = $(TESTROOT)/compare
MIAEXE = ./build/MIA/bin/MIA
TESTIMG = $(TESTROOT)/testimages/testimg.png
EXEC_MIA_CMD = cd .. && $(MIAEXE) $(TESTIMG)
###############################################################################
# Filter commands
###############################################################################


golden: | $(GOLDENDIR)
	$(EXEC_MIA_CMD) -sharpen 35.0 $(GOLDENDIR)/sharpen35.png
	$(EXEC_MIA_CMD) -sharpen 75.0 $(GOLDENDIR)/sharpen75.png
	$(EXEC_MIA_CMD) -edge $(GOLDENDIR)/edge.png
	$(EXEC_MIA_CMD) -threshold .3 $(GOLDENDIR)/thresholdpoint3.png
	$(EXEC_MIA_CMD) -threshold .6 $(GOLDENDIR)/thresholdpoint6.png
	$(EXEC_MIA_CMD) -quantize 2 $(GOLDENDIR)/quantize2.png
	$(EXEC_MIA_CMD) -quantize 6 $(GOLDENDIR)/quantize6.png
	$(EXEC_MIA_CMD) -blur 8.5 $(GOLDENDIR)/blur8point5.png
	$(EXEC_MIA_CMD) -blur 16.5 $(GOLDENDIR)/blur16point5.png
	$(EXEC_MIA_CMD) -grayscale $(GOLDENDIR)/grayscale.png

clean:
	@rm -rf $(COMPAREDIR)

veryclean: clean
	@rm -rf $(GOLDENDIR)

$(GOLDENDIR) $(COMPAREDIR):
	@mkdir -p $@
