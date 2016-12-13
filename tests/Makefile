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
COMPAREDIR = $(TESTROOT)/comparedir
MIAEXE = ./build/MIA/bin/MIA
TESTIMG = $(TESTROOT)/testimages/testimg.png
EXEC_MIA_CMD = cd .. && $(MIAEXE) 

GOLDENFILES = $(GOLDENDIR)/sharpen35.png $(GOLDENDIR)/sharpen75.png $(GOLDENDIR)/edge.png $(GOLDENDIR)/thresholdpoint3.png $(GOLDENDIR)/thresholdpoint6.png $(GOLDENDIR)/quantize2.png $(GOLDENDIR)/quantize6.png $(GOLDENDIR)/blur8point5.png $(GOLDENDIR)/blur16point5.png $(GOLDENDIR)/saturate.png

COMPAREFILES = $(COMPAREDIR)/sharpen35.png $(COMPAREDIR)/sharpen75.png $(COMPAREDIR)/edge.png $(COMPAREDIR)/thresholdpoint3.png $(COMPAREDIR)/thresholdpoint6.png $(COMPAREDIR)/quantize2.png $(COMPAREDIR)/quantize6.png $(COMPAREDIR)/blur8point5.png $(COMPAREDIR)/blur16point5.png $(COMPAREDIR)/saturate.png

 

###############################################################################
# Filter commands
###############################################################################

.PHONY: all golden comparison clean veryclean

all:
	cd ..
	echo "GOLDENFILES: "$(GOLDENFILES)
	echo "COMPAREFILES: " $(COMPAREFILES)
	if [ ! -d "./goldendir" ]; then echo "Golden images do not exist. Run 'make golden' first."; else $(MAKE) tests; fi 

tests: comparison $(COMPAREFILES) | $(COMPAREDIR)
	
$(COMPAREDIR)/%.png:
	pwd
	@echo "Testing " $(COMPAREDIR)/$*.png " against " $(GOLDENDIR)/$*.png
ifeq ($(shell $(EXEC_MIA_CMD) $@ -compare $(GOLDENDIR)/$*.png), 0)	
	@echo "Test PASSED."
else
	@echo "Test FAILED."
endif

golden: | $(GOLDENDIR)
	$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 35.0 $(GOLDENDIR)/sharpen35.png
	$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 75.0 $(GOLDENDIR)/sharpen75.png
	$(EXEC_MIA_CMD) $(TESTIMG) -edge $(GOLDENDIR)/edge.png
	$(EXEC_MIA_CMD) $(TESTIMG) -threshold .3 $(GOLDENDIR)/thresholdpoint3.png
	$(EXEC_MIA_CMD) $(TESTIMG) -threshold .6 $(GOLDENDIR)/thresholdpoint6.png
	$(EXEC_MIA_CMD) $(TESTIMG) -quantize 2 $(GOLDENDIR)/quantize2.png
	$(EXEC_MIA_CMD) $(TESTIMG) -quantize 6 $(GOLDENDIR)/quantize6.png
	$(EXEC_MIA_CMD) $(TESTIMG) -blur 8.5 $(GOLDENDIR)/blur8point5.png
	$(EXEC_MIA_CMD) $(TESTIMG) -blur 16.5 $(GOLDENDIR)/blur16point5.png
	$(EXEC_MIA_CMD) $(TESTIMG) -saturate 0 $(GOLDENDIR)/saturate.png
#	$(EXEC_MIA_CMD) $(TESTIMG) -saturate $(GOLDENDIR)/saturate.png

comparison: | $(COMPAREDIR)
	$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 35.0 $(COMPAREDIR)/sharpen35.png
	$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 75.0 $(COMPAREDIR)/sharpen75.png
	$(EXEC_MIA_CMD) $(TESTIMG) -edge $(COMPAREDIR)/edge.png
	$(EXEC_MIA_CMD) $(TESTIMG) -threshold .3 $(COMPAREDIR)/thresholdpoint3.png
	$(EXEC_MIA_CMD) $(TESTIMG) -threshold .6 $(COMPAREDIR)/thresholdpoint6.png
	$(EXEC_MIA_CMD) $(TESTIMG) -quantize 2 $(COMPAREDIR)/quantize2.png
	$(EXEC_MIA_CMD) $(TESTIMG) -quantize 6 $(COMPAREDIR)/quantize6.png
	$(EXEC_MIA_CMD) $(TESTIMG) -blur 8.5 $(COMPAREDIR)/blur8point5.png
	$(EXEC_MIA_CMD) $(TESTIMG) -blur 16.5 $(COMPAREDIR)/blur16point5.png
	$(EXEC_MIA_CMD) $(TESTIMG) -saturate 0 $(COMPAREDIR)/saturate.png
#	$(EXEC_MIA_CMD) $(TESTIMG) -saturate $(GOLDENDIR)/saturate.png
	
clean:
	@rm -rf ./comparedir

veryclean: clean
	@rm -rf ./goldendir

$(GOLDENDIR) $(COMPAREDIR):
	@cd .. && mkdir -p $@
