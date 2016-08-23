# This makefile compiles the evtunpacker program

# Change these definitions to (0)1 to (un)set the default unpackers
UNPACKERS=$(shell echo -D__UNPACK_SWEEPER=1 -D__UNPACK_MONA=1 -D__UNPACK_CAESAR=0)

# location of header files | n.b.: the -I flag is included in the variable!!
INCLUDE=$(shell echo -I ../include)

# libraries
LIBFLAGS=$(shell echo -lgsl -lgslcblas -lm)

# ROOT specific flags
ROOTFLAGS=$(shell echo `root-config --cflags --libs`)

#installation directory - architecture specific
ARCH:=$(shell getconf LONG_BIT)
#INSTALLATION_32:=$(shell echo ~/bin/bin32)
#INSTALLATION_64:=$(shell echo ~/bin/bin64)
INSTALLATION_32:=$(shell echo /projects/e15118/bin/bin32)
INSTALLATION_64:=$(shell echo /projects/e15118/bin/bin64)
INSTALLATION:= $(INSTALLATION_$(ARCH))

# how much optimization you want
# (O2 is generally good, O3 may be better for final production
# compile, use O0 when developing/debugging)
# OPTIMIZATION=$(shell echo -O0)
# OPTIMIZATION=$(shell echo -O1)
  OPTIMIZATION=$(shell echo -O2)
# OPTIMIZATION=$(shell echo -O3)

#switches to be used with g++
CXXFLAGS=-g -Wall $(OPTIMIZATION) $(INCLUDE) $(LIBFLAGS) $(ROOTFLAGS) $(UNPACKERS)

#object files
OBJECTS=sweeper.o mona.o caesar.o unpacker.o unpacker_main.o 

#Ring Buffer
OBJECTS_RB=sweeper.o mona.o caesar.o unpacker_rb.o unpacker_main_rb.o

#makefile targets
#n.b. the $(CXX) command runs the compiler g++

evtunpacker: $(OBJECTS)
	$(CXX) -o $(INSTALLATION)/evtunpacker $(OBJECTS) $(ROOTFLAGS) $(CXXFLAGS)

evtunpacker_rb: $(OBJECTS_RB)
	$(CXX) -o $(INSTALLATION)/evtunpacker_rb $(OBJECTS_RB) $(ROOTFLAGS) $(CXXFLAGS)

clean:
	rm -f $(OBJECTS) $(INSTALLATION)/evtunpacker
	rm -f $(OBJECTS_RB) $(INSTALLATION)/evtunpacker_rb

depend:
	makedepend  $(INCLUDE) *.cc *.cpp *.cxx *.C *.c++ *.c

help:
	echo "make evtunpacker     - Build evtunpacker";
	echo "make evtunpacker_rb  - Build evtunpacker for ringbuffers.";
	echo "make clean           - Remove objects from previous builds";
	echo "make depend          - Add dependencies to the Makefile.";

#dependencies found by make depend
#n.b. it will automatically use files in the current directory over
#"installed" ones (in [...]/include, etc) if they have the same name
# DO NOT DELETE

caesar.o: caesar.hh ../include/caesar_definitions.hh detector.hh sweeper.hh
caesar.o: ../include/sweeper_definitions.hh ../include/sweeper_packets.hh
caesar.o: cosy_map.hh /usr/include/stdlib.h /usr/include/features.h
caesar.o: /usr/include/alloca.h utils.cc ../include/sweeper_variables.hh
#caesar.o: ../include/crdc1_ped_values.txt ../include/crdc2_ped_values.txt
#caesar.o: ../include/ic_gainmatch_slopes.txt ../include/caesar_map.hh
#caesar.o: ../include/caesar_variables.hh ../include/caesar_offsets.txt
caesar.o: ../include/caesar_map.hh ../include/caesar_variables.hh
caesar.o: ../include/utils.hh ../include/caesar_setters_getters.hh
mona.o: mona.hh ../include/mona_packets.hh ../include/mona_definitions.hh
mona.o: detector.hh ../include/mona_variables.hh
mona.o: ../include/MoNA_QDCfittedSLOOFF.txt
mona.o: ../include/LISA_QDCfittedSLOOFF.txt ../include/MoNA_QDCfittedTHRE.txt
mona.o: ../include/LISA_QDCfittedTHRE.txt ../include/tcal_mona_output.txt
mona.o: ../include/tcal_lisa_output.txt ../include/mona_locations.hh
mona.o: ../include/lisa_locations.hh ../include/xpos_mona_output.txt
mona.o: ../include/xpos_lisa_output.txt ../include/tmean_offsets.h
mona.o: ../include/utils.hh
sweeper.o: sweeper.hh ../include/sweeper_definitions.hh
sweeper.o: ../include/sweeper_packets.hh detector.hh cosy_map.hh
sweeper.o: /usr/include/stdlib.h /usr/include/features.h
sweeper.o: /usr/include/alloca.h utils.cc ../include/sweeper_variables.hh
#sweeper.o: ../include/crdc1_ped_values.txt ../include/crdc2_ped_values.txt
#sweeper.o: ../include/ic_gainmatch_slopes.txt
sweeper.o: ../include/utils.hh /usr/include/time.h /usr/include/xlocale.h
sweeper.o: gsl_gaus_fit.h /usr/include/gsl/gsl_vector.h
sweeper.o: /usr/include/gsl/gsl_vector_complex_long_double.h
sweeper.o: /usr/include/gsl/gsl_types.h /usr/include/gsl/gsl_errno.h
sweeper.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
sweeper.o: /usr/include/wchar.h /usr/include/errno.h
sweeper.o: /usr/include/gsl/gsl_complex.h /usr/include/gsl/gsl_check_range.h
sweeper.o: /usr/include/gsl/gsl_vector_long_double.h
sweeper.o: /usr/include/gsl/gsl_inline.h
sweeper.o: /usr/include/gsl/gsl_block_long_double.h
sweeper.o: /usr/include/gsl/gsl_vector_complex.h
sweeper.o: /usr/include/gsl/gsl_block_complex_long_double.h
sweeper.o: /usr/include/gsl/gsl_vector_complex_double.h
sweeper.o: /usr/include/gsl/gsl_vector_double.h
sweeper.o: /usr/include/gsl/gsl_block_double.h
sweeper.o: /usr/include/gsl/gsl_block_complex_double.h
sweeper.o: /usr/include/gsl/gsl_vector_complex_float.h
sweeper.o: /usr/include/gsl/gsl_vector_float.h
sweeper.o: /usr/include/gsl/gsl_block_float.h
sweeper.o: /usr/include/gsl/gsl_block_complex_float.h
sweeper.o: /usr/include/gsl/gsl_vector_ulong.h
sweeper.o: /usr/include/gsl/gsl_block_ulong.h
sweeper.o: /usr/include/gsl/gsl_vector_long.h
sweeper.o: /usr/include/gsl/gsl_block_long.h
sweeper.o: /usr/include/gsl/gsl_vector_uint.h
sweeper.o: /usr/include/gsl/gsl_block_uint.h
sweeper.o: /usr/include/gsl/gsl_vector_int.h /usr/include/gsl/gsl_block_int.h
sweeper.o: /usr/include/gsl/gsl_vector_ushort.h
sweeper.o: /usr/include/gsl/gsl_block_ushort.h
sweeper.o: /usr/include/gsl/gsl_vector_short.h
sweeper.o: /usr/include/gsl/gsl_block_short.h
sweeper.o: /usr/include/gsl/gsl_vector_uchar.h
sweeper.o: /usr/include/gsl/gsl_block_uchar.h
sweeper.o: /usr/include/gsl/gsl_vector_char.h
sweeper.o: /usr/include/gsl/gsl_block_char.h /usr/include/gsl/gsl_blas.h
sweeper.o: /usr/include/gsl/gsl_matrix.h
sweeper.o: /usr/include/gsl/gsl_matrix_complex_long_double.h
sweeper.o: /usr/include/gsl/gsl_matrix_complex_double.h
sweeper.o: /usr/include/gsl/gsl_matrix_complex_float.h
sweeper.o: /usr/include/gsl/gsl_matrix_long_double.h
sweeper.o: /usr/include/gsl/gsl_matrix_double.h
sweeper.o: /usr/include/gsl/gsl_matrix_float.h
sweeper.o: /usr/include/gsl/gsl_matrix_ulong.h
sweeper.o: /usr/include/gsl/gsl_matrix_long.h
sweeper.o: /usr/include/gsl/gsl_matrix_uint.h
sweeper.o: /usr/include/gsl/gsl_matrix_int.h
sweeper.o: /usr/include/gsl/gsl_matrix_ushort.h
sweeper.o: /usr/include/gsl/gsl_matrix_short.h
sweeper.o: /usr/include/gsl/gsl_matrix_uchar.h
sweeper.o: /usr/include/gsl/gsl_matrix_char.h
sweeper.o: /usr/include/gsl/gsl_blas_types.h /usr/include/gsl/gsl_cblas.h
sweeper.o: /usr/include/gsl/gsl_multifit_nlin.h /usr/include/gsl/gsl_math.h
sweeper.o: /usr/include/math.h /usr/include/gsl/gsl_sys.h
sweeper.o: /usr/include/gsl/gsl_machine.h /usr/include/limits.h
sweeper.o: /usr/include/gsl/gsl_precision.h /usr/include/gsl/gsl_nan.h
sweeper.o: /usr/include/gsl/gsl_pow_int.h /usr/include/gsl/gsl_minmax.h
sweeper.o: /usr/include/gsl/gsl_rng.h /usr/include/gsl/gsl_randist.h
sweeper.o: /usr/include/gsl/gsl_poly.h
tandem.o: tandem.hh sweeper.hh ../include/sweeper_definitions.hh
tandem.o: ../include/sweeper_packets.hh detector.hh cosy_map.hh
tandem.o: /usr/include/stdlib.h /usr/include/features.h /usr/include/alloca.h
tandem.o: utils.cc ../include/sweeper_variables.hh
tandem.o: ../include/crdc1_ped_values.txt ../include/crdc2_ped_values.txt
tandem.o: ../include/ic_gainmatch_slopes.txt
tandem.o: mona.hh ../include/mona_packets.hh ../include/mona_definitions.hh
tandem.o: ../include/mona_variables.hh ../include/MoNA_QDCfittedSLOOFF.txt
tandem.o: ../include/LISA_QDCfittedSLOOFF.txt
tandem.o: ../include/MoNA_QDCfittedTHRE.txt ../include/LISA_QDCfittedTHRE.txt
tandem.o: ../include/tcal_mona_output.txt ../include/tcal_lisa_output.txt
tandem.o: ../include/mona_locations.hh ../include/lisa_locations.hh
tandem.o: ../include/xpos_mona_output.txt ../include/xpos_lisa_output.txt
tandem.o: ../include/tmean_offsets.h ../include/utils.hh
unpacker.o: unpacker.hh detector.hh
unpacker_main.o: sweeper.hh ../include/sweeper_definitions.hh
unpacker_main.o: ../include/sweeper_packets.hh detector.hh cosy_map.hh
unpacker_main.o: /usr/include/stdlib.h /usr/include/features.h
unpacker_main.o: /usr/include/alloca.h utils.cc
unpacker_main.o: ../include/sweeper_variables.hh
#unpacker_main.o: ../include/crdc1_ped_values.txt
#unpacker_main.o: ../include/crdc2_ped_values.txt
#unpacker_main.o: ../include/ic_gainmatch_slopes.txt mona.hh
unpacker_main.o: ../include/mona_packets.hh ../include/mona_definitions.hh
unpacker_main.o: ../include/mona_variables.hh
unpacker_main.o: ../include/MoNA_QDCfittedSLOOFF.txt
unpacker_main.o: ../include/LISA_QDCfittedSLOOFF.txt
unpacker_main.o: ../include/MoNA_QDCfittedTHRE.txt
unpacker_main.o: ../include/LISA_QDCfittedTHRE.txt
unpacker_main.o: ../include/tcal_mona_output.txt
unpacker_main.o: ../include/tcal_lisa_output.txt ../include/mona_locations.hh
unpacker_main.o: ../include/lisa_locations.hh ../include/xpos_mona_output.txt
unpacker_main.o: ../include/xpos_lisa_output.txt ../include/tmean_offsets.h
unpacker_main.o: caesar.hh ../include/caesar_definitions.hh
unpacker_main.o: ../include/caesar_map.hh ../include/caesar_variables.hh
unpacker_main.o: unpacker.hh
unpacker_main_rb.o: sweeper.hh ../include/sweeper_definitions.hh
unpacker_main_rb.o: ../include/sweeper_packets.hh detector.hh cosy_map.hh
unpacker_main_rb.o: /usr/include/stdlib.h /usr/include/features.h
unpacker_main_rb.o: /usr/include/alloca.h utils.cc
unpacker_main_rb.o: ../include/sweeper_variables.hh
#unpacker_main_rb.o: ../include/crdc1_ped_values.txt
#unpacker_main_rb.o: ../include/crdc2_ped_values.txt
#unpacker_main_rb.o: ../include/ic_gainmatch_slopes.txt mona.hh
unpacker_main_rb.o: ../include/mona_packets.hh ../include/mona_definitions.hh
unpacker_main_rb.o: ../include/mona_variables.hh
unpacker_main_rb.o: ../include/MoNA_QDCfittedSLOOFF.txt
unpacker_main_rb.o: ../include/LISA_QDCfittedSLOOFF.txt
unpacker_main_rb.o: ../include/MoNA_QDCfittedTHRE.txt
unpacker_main_rb.o: ../include/LISA_QDCfittedTHRE.txt
unpacker_main_rb.o: ../include/tcal_mona_output.txt
unpacker_main_rb.o: ../include/tcal_lisa_output.txt
unpacker_main_rb.o: ../include/mona_locations.hh ../include/lisa_locations.hh
unpacker_main_rb.o: ../include/xpos_mona_output.txt
unpacker_main_rb.o: ../include/xpos_lisa_output.txt
unpacker_main_rb.o: ../include/tmean_offsets.h caesar.hh
unpacker_main_rb.o: ../include/caesar_definitions.hh ../include/caesar_map.hh
unpacker_main_rb.o: ../include/caesar_variables.hh unpacker_rb.hh
unpacker_rb.o: unpacker_rb.hh detector.hh
