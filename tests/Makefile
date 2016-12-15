
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
EXEC_MIA_CMD = cd ..; $(MIAEXE) 

GOLDENFILES = $(GOLDENDIR)/sharpen35.png $(GOLDENDIR)/sharpen75.png $(GOLDENDIR)/edge.png $(GOLDENDIR)/thresholdpoint3.png $(GOLDENDIR)/thresholdpoint6.png $(GOLDENDIR)/quantize2.png $(GOLDENDIR)/quantize6.png $(GOLDENDIR)/blur8point5.png $(GOLDENDIR)/blur16point5.png $(GOLDENDIR)/saturate.png $(GOLDENDIR)/quantize4edge.png $(GOLDENDIR)/blursaturatesharpen.png

COMPAREFILES = $(COMPAREDIR)/sharpen35.png $(COMPAREDIR)/sharpen75.png $(COMPAREDIR)/edge.png $(COMPAREDIR)/thresholdpoint3.png $(COMPAREDIR)/thresholdpoint6.png $(COMPAREDIR)/quantize2.png $(COMPAREDIR)/quantize6.png $(COMPAREDIR)/blur8point5.png $(COMPAREDIR)/blur16point5.png $(COMPAREDIR)/saturate.png $(COMPAREDIR)/quantize4edge.png $(COMPAREDIR)/blursaturatesharpen.png

RESULTFILE = testresults.txt 
REPORTFILE = testreport.txt
USAGEFILE = usagefile.txt

###############################################################################
# Filter commands
###############################################################################

.PHONY: all golden comparison tests results badinput clean veryclean

all:
	@cd ..
	@if [ ! -d "./goldendir" ]; then echo "Golden images do not exist. Run 'make golden' first."; else $(MAKE) tests; fi 

tests: badinput comparison $(COMPAREFILES) results | $(COMPAREDIR)

badinput:
	@$(EXEC_MIA_CMD) -h > tests/$(USAGEFILE) || true
	@echo "Testing for bad input handling: missing input file..."
	@$(EXEC_MIA_CMD) -sharpen 25.0 ./tests/badoutput.png > tests/$(RESULTFILE) || true
	@diff --brief $(USAGEFILE) $(RESULTFILE) ; if [ $$? -eq 0 ] ; then echo "Test PASSED\n"; else echo "TEST FAILED\n" ; fi 
	@echo "Testing for bad input handling: nonexistent input file..."
	@$(EXEC_MIA_CMD) badinput.png -sharpen 25.0 ./tests/badoutput.png > tests/$(RESULTFILE) || true 
	@diff --brief $(USAGEFILE) $(RESULTFILE) ; if [ $$? -eq 0 ] ; then echo "Test PASSED\n"; else echo "TEST FAILED\n" ; fi 
	@echo "Testing for bad input handling: missing filter..."
	@$(EXEC_MIA_CMD) $(TESTIMG) 25.0 ./tests/badoutput.png > tests/$(RESULTFILE) || true
	@diff --brief $(USAGEFILE) $(RESULTFILE) ; if [ $$? -eq 0 ] ; then echo "Test PASSED\n"; else echo "TEST FAILED\n" ; fi  
	@echo "Testing for bad input handling: missing filter amount..."
	@$(EXEC_MIA_CMD) $(TESTIMG) -sharpen ./tests/badoutput.png > tests/$(RESULTFILE) || true
	@diff --brief $(USAGEFILE) $(RESULTFILE) ; if [ $$? -eq 0 ] ; then echo "Test PASSED\n"; else echo "TEST FAILED\n" ; fi 
	@rm $(USAGEFILE)
	@rm $(RESULTFILE)

results:
	@sed 's/=1/: Test PASSED/g;s/=0/: Test FAILED/g' $(RESULTFILE) > $(REPORTFILE)
	@cat $(REPORTFILE)
	@rm $(REPORTFILE)
	@rm $(RESULTFILE)

$(COMPAREDIR)/%.png:
	@echo "Testing against image standard for $(notdir $@)..." >> $(RESULTFILE)
	@printf "%s=" $(notdir $@) >> $(RESULTFILE)
	@$(EXEC_MIA_CMD) $@ -compare $(GOLDENDIR)/$*.png >> tests/$(RESULTFILE)
	@printf "\n" >> $(RESULTFILE)	

golden: | $(GOLDENDIR)
	@$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 35.0 $(GOLDENDIR)/sharpen35.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 75.0 $(GOLDENDIR)/sharpen75.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -edge $(GOLDENDIR)/edge.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -threshold .3 $(GOLDENDIR)/thresholdpoint3.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -threshold .6 $(GOLDENDIR)/thresholdpoint6.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -quantize 2 $(GOLDENDIR)/quantize2.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -quantize 6 $(GOLDENDIR)/quantize6.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -blur 8.5 $(GOLDENDIR)/blur8point5.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -blur 16.5 $(GOLDENDIR)/blur16point5.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -saturate 0 $(GOLDENDIR)/saturate.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -quantize 4 -edge $(GOLDENDIR)/quantize4edge.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -blur 11.0 -saturate 0 -sharpen 60.0 $(GOLDENDIR)/blursaturatesharpen.png

comparison: | $(COMPAREDIR)
	@$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 35.0 $(COMPAREDIR)/sharpen35.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -sharpen 75.0 $(COMPAREDIR)/sharpen75.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -edge $(COMPAREDIR)/edge.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -threshold .3 $(COMPAREDIR)/thresholdpoint3.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -threshold .6 $(COMPAREDIR)/thresholdpoint6.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -quantize 2 $(COMPAREDIR)/quantize2.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -quantize 6 $(COMPAREDIR)/quantize6.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -blur 8.5 $(COMPAREDIR)/blur8point5.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -blur 16.5 $(COMPAREDIR)/blur16point5.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -saturate 0 $(COMPAREDIR)/saturate.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -quantize 4 -edge $(COMPAREDIR)/quantize4edge.png
	@$(EXEC_MIA_CMD) $(TESTIMG) -blur 11.0 -saturate 0 -sharpen 60.0 $(COMPAREDIR)/blursaturatesharpen.png
	
clean:
	@rm -rf ./comparedir

veryclean: clean
	@rm -rf ./goldendir

$(GOLDENDIR) $(COMPAREDIR):
	@cd .. && mkdir -p $@

